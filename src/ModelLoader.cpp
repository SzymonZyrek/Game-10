
#include <string>
#include "ModelLoader.h"
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

Logger modellogger(DebugKey::MODEL_LOADING);
void ModelLoader::loadObjFile(std::string fileName)
{
	std::stringstream ss;
	ss << "../resources/meshes/" << fileName;
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
			if (line.find("vn") == 0){
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
			else if (line.find("vt") == 0){
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
			else if (line.find("v") == 0){
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
			else if (line.find("f") == 0){
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
				else if (!(iss2
					>> s
					>> vertexIndex[0]
					>> normalIndex[0]
					>> vertexIndex[1]
					>> normalIndex[1]
					>> vertexIndex[2]
					>> normalIndex[2]
					)){
					std::stringstream ss;
					ss << "Could not parse face: " << line;
					modellogger << ss;
					return;
				}
				else{
					std::stringstream ss;
					ss << "FACE: No texture coords!";
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
		printRenderData();
	}
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