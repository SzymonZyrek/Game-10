
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
	VERTEX_MODE, TEXEL_MODE, NORMAL_MODE, FACE_MODE, NONE, COMMENT
};

Logger modellogger(DebugKey::MODEL_LOADING);

int ModelLoader::getVertexCount()
{
	return vertexIndices.size();
}

ModelLoader::ModelLoader(std::string fileName) {
	this->_fileName = fileName;
}
ModelLoader::~ModelLoader(){

}

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
				// advance to new line and check line prefix:
				// v is vertex
				// vn is normal
				// vt is textl
				// f is face
				// # is comment
				mempointer++;
				if (*mempointer == 'v'&&*(mempointer + 1) == 't'){
					mode = TEXEL_MODE;
					// two-chars prefix, advance pointer
					mempointer++;
				}
				else if (*mempointer == 'v'&&*(mempointer + 1) == 'n'){
					mode = NORMAL_MODE;
					// two-chars prefix, advance pointer
					mempointer++;
				}else if (*mempointer == 'v'){
					mode = VERTEX_MODE;
				}else if (*mempointer == 'f'){
					mode = FACE_MODE;
				}
				else if (*mempointer == '#'){
					mode = COMMENT;
				}
				linedata.clear(); // cleanup 			
			}
			mempointer++;         // as always, advance pointer ^^
		}
	}
	free(buffer);
	return data;
}

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
}

#define VERTEX_DELIM ','
void ModelLoader::saveAsBinary(std::string fileName, Renderable &renderable)
{
	std::stringstream filePath;
	filePath << "../resources/meshes/" << fileName << ".obj";
	std::ofstream myFile(filePath.str(), std::ios::out | std::ios::binary);
	for (glm::vec3 vertex : renderable.meshVertices){
		std::stringstream ss;
		ss << vertex.x << VERTEX_DELIM << vertex.y << VERTEX_DELIM << vertex.z << std::endl;
		myFile.write(ss.str().c_str(),ss.str().size());
	}
	myFile.close();
}

void ModelLoader::loadBinary(std::string fileName, Renderable &renderable)
{
	std::stringstream filePath;
	filePath << "../resources/meshes/" << fileName << ".obj";
	std::ofstream myFile(filePath.str(), std::ios::out | std::ios::binary);
	for (glm::vec3 vertex : renderable.meshVertices){
		std::stringstream ss;
		ss << vertex.x << VERTEX_DELIM << vertex.y << VERTEX_DELIM << vertex.z << std::endl;
		myFile.write(ss.str().c_str(), ss.str().size());
	}
	myFile.close();
}

void ModelLoader::loadObjFile(Renderable &renderable)
{
	if (!initialized){
		std::stringstream ss;
		ss << "../resources/meshes/" << _fileName;

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

		initialized = true;
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++){
		renderable.meshVertices.push_back(vertices[vertexIndices[i] - 1]);
		renderable.meshNormals.push_back(normals[normalIndices[i] - 1]);
		renderable.meshUvs.push_back(uv[uvIndices[i] - 1]);
	}
	renderable.vertexCount = vertexIndices.size();
	renderable.modelLoaded = true;
	return;
}
