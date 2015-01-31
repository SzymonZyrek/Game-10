
#include <string>
#include "ModelLoader.h"
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <algorithm>
#include <regex>
#include "GameLoop.h"
#include <ctime>
#include "Config.h"
#include <iostream>

enum Mode {
	VERTEX_MODE, TEXEL_MODE, NORMAL_MODE, FACE_MODE, NONE, COMMENT, MATERIAL
};

Logger ModelLoader::modellogger(DebugKey::MODEL_LOADING);

int ModelLoader::getVertexCount()
{
	return vertexIndices.size();
}

ModelLoader::ModelLoader() {}
ModelLoader::~ModelLoader(){

}

inline bool fileExists(const std::string& name) {
	if (FILE *file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
void ModelLoader::saveAsBinary(std::string fileName, Renderable &renderable){
	/*clock_t begin = clock();
	std::ofstream binaryOut;
	std::stringstream ss;
	ss << "../resources/meshes/" << fileName << ".bin";
	binaryOut.open(ss.str(), std::ios::binary | std::ios::out);
	if (renderable.indexed){
		char type = 'i';
		binaryOut.write(&type, sizeof(char));
		unsigned int indices = renderable.indices.size();
		binaryOut.write(reinterpret_cast<const char *>(&indices), sizeof(indices));
		binaryOut.write(reinterpret_cast<const char *>(&renderable.indices[0]), sizeof(renderable.indices[0])*renderable.indices.size());
		unsigned int verts = renderable.indexedVertices.size();
		binaryOut.write(reinterpret_cast<const char *>(&verts), sizeof(verts));
		binaryOut.write(reinterpret_cast<const char *>(&renderable.indexedVertices[0]), sizeof(renderable.indexedVertices[0])*renderable.indexedVertices.size());
		binaryOut.write(reinterpret_cast<const char *>(&renderable.indexedNormals[0]), sizeof(renderable.indexedNormals[0])*renderable.indexedNormals.size());
		binaryOut.write(reinterpret_cast<const char *>(&renderable.indexedUvs[0]), sizeof(renderable.indexedUvs[0])*renderable.indexedUvs.size());
	}else{
		char type = 'p';
		binaryOut.write(&type, sizeof(char));
		unsigned int verts = renderable.meshVertices.size();
		binaryOut.write(reinterpret_cast<const char *>(&verts), sizeof(verts));
		binaryOut.write(reinterpret_cast<const char *>(&renderable.meshVertices[0]), sizeof(renderable.meshVertices[0])*renderable.meshVertices.size());
		binaryOut.write(reinterpret_cast<const char *>(&renderable.meshNormals[0]), sizeof(renderable.meshNormals[0])*renderable.meshNormals.size());
		binaryOut.write(reinterpret_cast<const char *>(&renderable.meshUvs[0]), sizeof(renderable.meshUvs[0])*renderable.meshUvs.size());
	}
	binaryOut.close();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::stringstream log;
	log << "Saved .bin model file: " << fileName << ", elapsed time: " << elapsed_secs << "s" << ", " << renderable << std::endl;
	modellogger << log;*/
}
void ModelLoader::loadBinary(std::string fileName, Renderable &renderable){
	std::ifstream binaryIn;
	std::stringstream ss;
	clock_t begin = clock();

	ss << "../resources/meshes/" << fileName << ".bin";
	if (!fileExists(ss.str().c_str())){
		std::stringstream errorStream;
		errorStream << "File not found: " << ss.str();
		throw errorStream.str();
	}
	binaryIn.open(ss.str(), std::ios::binary | std::ios::out);
	char type;
	binaryIn.read(&type, sizeof(type));
	if (type == 'i'){
		binaryIn.read((char*)&renderable.indexCount, sizeof(renderable.indexCount));
		renderable.indices.resize(renderable.indexCount);
		binaryIn.read((char*)&renderable.indices[0], sizeof(renderable.indices[0])*renderable.indexCount);
		binaryIn.read((char*)&renderable.vertexCount, sizeof(renderable.vertexCount));
		renderable.indexedVertices.resize(renderable.vertexCount);
		binaryIn.read((char*)&renderable.indexedVertices[0], sizeof(renderable.indexedVertices[0])*renderable.vertexCount);
		renderable.indexedNormals.resize(renderable.vertexCount);
		binaryIn.read((char*)&renderable.indexedNormals[0], sizeof(renderable.indexedNormals[0])*renderable.vertexCount);
		renderable.indexedUvs.resize(renderable.vertexCount);
		binaryIn.read((char*)&renderable.indexedUvs[0], sizeof(renderable.indexedUvs[0])*renderable.vertexCount);
		renderable.indexed = true;
	}
	else if (type == 'p'){
		binaryIn.read((char*)&renderable.vertexCount, sizeof(renderable.vertexCount));
		renderable.meshVertices.resize(renderable.vertexCount);
		binaryIn.read((char*)&renderable.meshVertices[0], sizeof(renderable.meshVertices[0])*renderable.vertexCount);
		renderable.meshNormals.resize(renderable.vertexCount);
		binaryIn.read((char*)&renderable.meshNormals[0], sizeof(renderable.meshNormals[0])*renderable.vertexCount);
		renderable.meshUvs.resize(renderable.vertexCount);
		binaryIn.read((char*)&renderable.meshUvs[0], sizeof(renderable.meshUvs[0])*renderable.vertexCount);
		renderable.indexed = false;
		renderable.modelName = fileName;
	}
	else{
		ss = std::stringstream("");
		ss << "Could not load " << fileName << ", unrecognised type: " << type;
		throw ss.str();
	}
	renderable.modelLoaded = true;
	binaryIn.close();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::stringstream log;
	log << "Loaded .bin model file: " << fileName << ", elapsed time: " << elapsed_secs << "s" << ", " << renderable << std::endl;
	modellogger << log;
}
std::shared_ptr<FileData> ModelLoader::readObjFileIntoMemory(std::string path){
	char* buffer;
	char linearray[250];
	int lineposition = 0;
	std::shared_ptr<FileData> data(new FileData);

	FILE *inputfile;
	if (!fileExists(path.c_str())){
		std::stringstream errorStream;
		errorStream << "File not found: " << path;
		throw errorStream.str();
	}
	inputfile = fopen(path.c_str(), "r");

	fseek(inputfile, 0, SEEK_END);          //find the filesize
	long filesize = ftell(inputfile);
	rewind(inputfile);

	buffer = (char*)malloc(sizeof(char)*filesize);      //allocate mem
	fread(buffer, filesize, 1, inputfile);         //read the file to the memory

	Mode mode = NONE;

	char* mempointer = buffer;
	std::string linedata;

	std::string activeMaterial = Config::getStringProperty(DEFAULT_TEXTURE_FILE_NAME);

	while (*mempointer)          //loop thru the buffer
	{
		if (mempointer != 0)
		{
			if (*mempointer != '/'){				//ignore '/'
				linedata.push_back(*mempointer);             
			}
			else{
				linedata.push_back(' ');            //swap it with whitespace
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
					data->materials.push_back(activeMaterial);
					data->facedata.push_back(linedata);
					mode = NONE;
					break;
				case MATERIAL:
					linedata.erase(std::remove(linedata.begin(), linedata.end(), '\n'), linedata.end());
					activeMaterial = linedata;
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
				else if (
					*mempointer     == 'u' &&
					*(mempointer + 1) == 's' &&
					*(mempointer + 2) == 'e' &&
					*(mempointer + 3) == 'm' &&
					*(mempointer + 4) == 't' &&
					*(mempointer + 5) == 'l' &&
					*(mempointer + 6) == ' '
					){
					mode = MATERIAL;
					mempointer += 6;
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
		float u, v;
		if (!(iss >> u >> v)){
			std::stringstream ss;
			ss << "Could not parse texel: " << line;
			modellogger << ss;
			return;
		}
		uv.push_back(glm::vec2(u, 1-v));
	}
	unsigned int faceCounter = 0;
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

void ModelLoader::loadObjFile(std::string fileName, Renderable &renderable)
{
	clock_t begin = clock();
	if (!initialized){
		std::stringstream ss;
		ss << "../resources/meshes/" << fileName << ".obj";
		std::shared_ptr<FileData> data = readObjFileIntoMemory(ss.str());
		parse(data);
		renderable.textureName = data->materials[0];
		renderable.textureNames = data->materials;
		initialized = true;
		GLubyte materialIndex = 0;
		for (std::string materialName : data->materials){
			if (renderable.materialMap.find(materialName) == renderable.materialMap.end()){
				renderable.materialMap[materialName] = materialIndex++;
			}
		}
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++){
		renderable.meshVertices.push_back(vertices[vertexIndices[i] - 1]);
		renderable.meshNormals.push_back(normals[normalIndices[i] - 1]);
		renderable.meshUvs.push_back(uv[uvIndices[i] - 1]);
		renderable.meshMaterialCoords.push_back(renderable.materialMap[renderable.textureNames[i/3]]);
	}
	renderable.vertexCount = vertexIndices.size();
	renderable.modelLoaded = true;
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::stringstream log;
	log << "Loaded .obj model file: " << fileName << ", elapsed time: " << elapsed_secs << "s" << ", " << renderable << std::endl;
	modellogger << log;
}
