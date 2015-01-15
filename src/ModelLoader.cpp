
#include <string>
#include "ModelLoader.h"
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <algorithm>
#include <regex>
#include "GameLoop.h"
#include <ctime>
#include <iostream>

enum Mode {
	VERTEX_MODE, TEXEL_MODE, NORMAL_MODE, FACE_MODE, NONE
};

Logger modellogger(DebugKey::MODEL_LOADING);


std::shared_ptr<FileData> readFileIntoMemory(std::string path){
	char* buffer;
	char linearray[250];
	int lineposition = 0;
	std::shared_ptr<FileData> data(new FileData);

	FILE *inputfile;
	inputfile = fopen(path.c_str(), "r");

	fseek(inputfile, 0, SEEK_END);          //find the filesize
	long filesize = ftell(inputfile);
	rewind(inputfile);

	buffer = (char*)malloc(sizeof(char)*filesize);      //allocate mem
	fread(buffer, filesize, 1, inputfile);         //read the file to the memory

	Mode mode = NONE;

	char* mempointer = buffer;
	std::string linedata;

	while (*mempointer)          //loop thru the buffer
	{
		if (mempointer != 0)
		{
			if (*mempointer != '/'){
				linedata.push_back(*mempointer);             //push character into string
			}
			else{
				linedata.push_back(' ');
			}
			if (*mempointer == 13 || *mempointer == 10)      //until we hit newline
			{
				switch (mode){
				case NONE: break;
				case VERTEX_MODE:
					data->vertexdata.push_back(linedata);
					mode = NONE;
					break;
				case NORMAL_MODE: 
					data->normaldata.push_back(linedata);
					mode = NONE;
					break;
				case TEXEL_MODE: 
					data->texeldata.push_back(linedata);
					mode = NONE;
					break;
				case FACE_MODE: 
					data->facedata.push_back(linedata);
					mode = NONE;
					break;
				default: break;
				}
				mempointer++;
				if (*mempointer == 'v'&&*(mempointer + 1) == 't'){
					mode = TEXEL_MODE;
					mempointer++;
				}
				else if (*mempointer == 'v'&&*(mempointer + 1) == 'n'){
					mode = NORMAL_MODE;
					mempointer++;
				}else if (*mempointer == 'v'){
					mode = VERTEX_MODE;
				}else if (*mempointer == 'f'){
					mode = FACE_MODE;
				}
				linedata.clear();                         // Clear "temporary string"
			}
			mempointer++;                      // advance pointer
		}
	}
	free(buffer);
	return data;
}



//string linedata;
//
//while (*mempointer)          //loop thru the buffer
//{
//	if (*mempointer != 0)
//	{
//		linedata.push_back(*mempointer);             //push character into string
//
//		if (*mempointer == 13 || *mempointer == 10)      //until we hit newline
//		{
//			data.push_back(linedata);              // Push string to vector
//			linedata.clear();                         // Clear "temporary string"
//		}
//		*mempointer++;                      // advance pointer
//	}
//}
//
//free(buffer);
//




bool isSlash(char c)
{
	switch (c)
	{
	case '/':
		return true;
	default:
		return false;
	}
}

void ModelLoader::parse(std::shared_ptr<FileData> data){
	std::istringstream iss;
	for (std::string line: data->vertexdata) {
		iss = std::istringstream(line);
		float x, y, z;
		if (!(iss >> x >> y >> z)){
			std::stringstream ss;
			ss << "Could not parse vertex: " << line;
			modellogger << ss;
			return;
		}
		vertices.push_back(glm::vec3(x,y,z));
	}
	for (std::string line : data->normaldata) {
		iss = std::istringstream(line);
		float x, y, z;
		if (!(iss >> x >> y >> z)){
			std::stringstream ss;
			ss << "Could not parse normal: " << line;
			modellogger << ss;
			return;
		}
		normals.push_back(glm::vec3(x, y, z));
	}
	for (std::string line : data->texeldata) {
		iss = std::istringstream(line);
		float x, y;
		if (!(iss >> x >> y)){
			std::stringstream ss;
			ss << "Could not parse texel: " << line;
			modellogger << ss;
			return;
		}
		uv.push_back(glm::vec2(x, y));
	}
	for (std::string line : data->facedata) {
		iss = std::istringstream(line);
		unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
		if ((iss >> vertexIndex[0] >> uvIndex[0] >> normalIndex[0]
			>> vertexIndex[1] >> uvIndex[1] >> normalIndex[1]
			>> vertexIndex[2] >> uvIndex[2] >> normalIndex[2]
			)){
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else{

		}
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++){
		indexedVertices.push_back(vertices[vertexIndices[i] - 1]);
		indexedNormals.push_back(normals[normalIndices[i] - 1]);
		indexedUv.push_back(uv[uvIndices[i] - 1]);
	}
}

std::string cleanLine(std::string line)
{
	std::tr1::regex rx("/");
	std::string replacement = " ";
	return std::regex_replace(line, rx, replacement);
}
#define VERTEX_DELIM ','
void ModelLoader::saveAsBinary(std::string fileName)
{
	std::stringstream filePath;
	filePath << "../resources/meshes/" << fileName << ".obj";
	std::ofstream myFile(filePath.str(), std::ios::out | std::ios::binary);
	for (glm::vec3 vertex: indexedVertices){
		std::stringstream ss;
		ss << vertex.x << VERTEX_DELIM << vertex.y << VERTEX_DELIM << vertex.z << std::endl;
		myFile.write(ss.str().c_str(),ss.str().size());
	}
	myFile.close();
}

void ModelLoader::loadObjFile(std::string fileName)
{
	std::stringstream ss;
	ss << "../resources/meshes/" << fileName;

	clock_t begin = clock();
	std::shared_ptr<FileData> data = readFileIntoMemory(ss.str());
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Loading to memory: " << elapsed_secs << "s";
	begin = clock();
	parse(data);
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Parsing in memory: " << elapsed_secs << "s";
	/*begin = clock();
	std::ifstream defaultFile(ss.str());
	if (!defaultFile.good()) {
		std::stringstream ss2;
		ss2 << "Could not load file: " << ss.str();
		modellogger << ss2;
		return;
	}
	else {
		ss = std::stringstream("");
		ss << "Loading file " << fileName;
		modellogger << ss;
		std::string line;
		while (std::getline(defaultFile, line)){
			if (line.at(0) == 'v'&& line.at(1)=='n'){
				std::istringstream iss(line);
				float x, y, z;
				std::string s;
				if (!(iss >> s >> x >> y >> z)){
					std::stringstream ss;
					ss << "Could not parse normal: " << line;
					modellogger << ss;
					return;
				}
				glm::vec3 normal(x, y, z);
				normals.push_back(normal);
			}
			else if (line.at(0) == 'v'&& line.at(1) == 't'){
				std::istringstream iss(line);
				std::string s;
				float x, y;
				if (!(iss >> s >> x >> y)){
					std::stringstream ss;
					ss << "Could not parse texel: " << line;
					modellogger << ss;
					return;
				}
				glm::vec2 texel(x, y);
				uv.push_back(texel);
			}
			else if (line.at(0) == 'v'){
				std::istringstream iss(line);
				float x, y, z;
				std::string s;
				if (!(iss >> s >> x >> y >> z)){
					std::stringstream ss;
					ss << "Could not parse vertex: " << line;
					modellogger << ss;
					return;
				}
				glm::vec3 normal(x, y, z);
				vertices.push_back(normal);
			}
			else if (line.at(0)=='f'){
				line = cleanLine(line);
				std::string vertex1, vertex2, vertex3;
				std::istringstream iss(line);
				std::istringstream iss2(line);
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				std::string s;
				if ((iss
					>> s
					>> vertexIndex[0]
					>> uvIndex[0]
					>> normalIndex[0]
					>> vertexIndex[1]
					>> uvIndex[1]
					>> normalIndex[1]
					>> vertexIndex[2]
					>> uvIndex[2]
					>> normalIndex[2]
					)){
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					uvIndices.push_back(uvIndex[0]);
					uvIndices.push_back(uvIndex[1]);
					uvIndices.push_back(uvIndex[2]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);
				}
				else if ((iss2
					>> s
					>> vertexIndex[0]
					>> normalIndex[0]
					>> vertexIndex[1]
					>> normalIndex[1]
					>> vertexIndex[2]
					>> normalIndex[2]
					)){
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);
					std::stringstream ss;
					ss << "FACE: No texture coords!";
					modellogger << ss;
				}
				else{
					std::stringstream ss;
					ss << "Could not parse face: " << line;
					Log::error(ss.str());
					initialized = false;
					return;
				}
			}
		}
		for (unsigned int i = 0; i < vertexIndices.size(); i++){
			indexedVertices.push_back(vertices[vertexIndices[i] - 1]);
			indexedNormals.push_back(normals[normalIndices[i] - 1]);
			indexedUv.push_back(uv[uvIndices[i] - 1]);
		}
		defaultFile.close();
		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Loading by line: " << elapsed_secs << "s";
		begin = clock();
		printRenderData();
		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Printing to logs: " << elapsed_secs << "s";
		begin = clock();
		saveAsBinary(fileName);
		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Saving as binary: " << elapsed_secs << "s";
	}*/
	initialized = true;
	return;
}

void ModelLoader::printRenderData() {
	std::stringstream ss("File loaded:\n");
	ss << "------------------------------------" << std::endl << "Vertices: " << std::endl << "------------------------------------" << std::endl;
	for (unsigned int i = 0; i < vertices.size(); i++){
		glm::vec3 vertex = vertices[i];
		ss << "[" << vertex.x << "," << vertex.y << "," << vertex.z << "], " << std::endl;
	}
	ss << std::endl;
	ss << "------------------------------------" << std::endl << "Normals: " << std::endl << "------------------------------------" << std::endl;
	for (unsigned int i = 0; i < normals.size(); i++){
		glm::vec3 normal = normals[i];
		ss << "[" << normal.x << "," << normal.y << "," << normal.z << "], " << std::endl;
	}
	ss << std::endl;
	ss << "------------------------------------" << std::endl << "UVs: " << std::endl << "------------------------------------" << std::endl;
	for (unsigned int i = 0; i < uv.size(); i++){
		glm::vec2 texel = uv[i];
		ss << "[" << texel.x << "," << texel.y << "], " << std::endl;
	}
	ss << std::endl;
	ss << "------------------------------------" << std::endl << "vertexIndices: " << std::endl << "------------------------------------" << std::endl;
	for (unsigned int i = 0; i < vertexIndices.size(); i++){
		unsigned int index = vertexIndices[i];
		ss << index << ", ";
	}
	ss << std::endl;
	ss << "------------------------------------" << std::endl << "uvIndices: " << std::endl << "------------------------------------" << std::endl;
	for (unsigned int i = 0; i < uvIndices.size(); i++){
		unsigned int index = uvIndices[i];
		ss << index << ", ";
	}
	ss << std::endl;
	ss << "------------------------------------" << std::endl << "normalIndices: " << std::endl << "------------------------------------" << std::endl;
	for (unsigned int i = 0; i < normalIndices.size(); i++){
		unsigned int index = normalIndices[i];
		ss << index << ", ";
	}
	ss << "------------------------------------" << std::endl << "Indexed vertices: " << std::endl << "------------------------------------" << std::endl;
	for (unsigned int i = 0; i < indexedVertices.size(); i++){
		glm::vec3 vertex = indexedVertices[i];
		ss << "[" << vertex.x << "," << vertex.y << "," << vertex.z << "], " << std::endl;
	}
	ss << std::endl;
	ss << "------------------------------------" << std::endl << "Indexed normals: " << std::endl << "------------------------------------" << std::endl;
	for (unsigned int i = 0; i < indexedNormals.size(); i++){
		glm::vec3 normal = indexedNormals[i];
		ss << "[" << normal.x << "," << normal.y << "," << normal.z << "], " << std::endl;
	}
	ss << std::endl;
	ss << "------------------------------------" << std::endl << " Indexed UVs: " << std::endl << "------------------------------------" << std::endl;
	for (unsigned int i = 0; i <indexedUv.size(); i++){
		glm::vec2 texel = indexedUv[i];
		ss << "[" << texel.x << "," << texel.y << "], " << std::endl;
	}
	ss << std::endl;

	modellogger << ss;
}

ModelLoader::ModelLoader(){

}
ModelLoader::~ModelLoader(){}
int ModelLoader::getVertexCount()
{
	return vertexIndices.size();
}