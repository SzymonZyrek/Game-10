#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "CPPLogger.h"

class ModelLoader {
public:
	void loadObjFile(std::string fileName);
	~ModelLoader();
	ModelLoader();
	std::vector<glm::vec3> indexedVertices;
	std::vector<glm::vec2> indexedUv;
	std::vector<glm::vec3> indexedNormals;
	int getVertexCount();
private:
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

	bool initialized = false; // this flag indicates wheter this ModelLoader instance successfully lodaded a model

	void printRenderData();
};