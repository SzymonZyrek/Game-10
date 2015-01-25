#pragma once
#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "CPPLogger.h"
#include <memory>
#include "Renderable.h"

struct FileData {
	std::vector<std::string> vertexdata;
	std::vector<std::string> texeldata;
	std::vector<std::string> normaldata;
	std::vector<std::string> facedata;
	std::map<unsigned int, std::string> materials;
};

class ModelLoader {
public:
	ModelLoader();
	~ModelLoader();
	void loadObjFile(std::string fileName, Renderable &renderable);
	int getVertexCount();
	void saveAsBinary(std::string fileName, Renderable &renderable);
	void loadBinary(std::string fileName, Renderable &renderable);
	bool initialized = false; // this flag indicates wheter this ModelLoader instance successfully lodaded a model
private:
	std::shared_ptr<FileData> readObjFileIntoMemory(std::string path);
	static Logger ModelLoader::modellogger;
	//------------------------------------------
	// Vertices, uvs and normals, as read from 
	// .obj file
	//------------------------------------------
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> normals;
	//------------------------------------------
	// Indices, mapped from "faces" lines of
	// .obj file input
	//------------------------------------------
	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> uvIndices;
	std::vector<unsigned int> normalIndices;
	// Vertices, uvs and normals, indexed
	// with use of above indices
	//------------------------------------------
	void parse(std::shared_ptr<FileData> data);
};