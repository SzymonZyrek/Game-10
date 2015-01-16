#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "CPPLogger.h"
#include <memory>
#include "Renderable.h"

struct FileData {
	std::vector<std::string> vertexdata;
	std::vector<std::string> texeldata;
	std::vector<std::string> normaldata;
	std::vector<std::string> facedata;
};

class ModelLoader {
public:
	ModelLoader(std::string fileName);
	~ModelLoader();
	void loadObjFile(Renderable &renderable);
	int getVertexCount();
private:
	std::string _fileName;
	static Logger logger;
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
	bool initialized = false; // this flag indicates wheter this ModelLoader instance successfully lodaded a model

	void printRenderData(Renderable &renderable);
	void saveAsBinary(std::string fileName, Renderable &renderable);
};