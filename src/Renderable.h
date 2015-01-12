#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderable {
public:
	//------------------------------------------
	// Resources initialization data:
	//------------------------------------------
	char * textureName = "brick.jpg";	//texture file path relative to ${INSTALLPATH}/resources dir
	char * objFileName = "bunker.obj";	//obj file path relative to ${INSTALLPATH}/resources dir
	bool modelLoaded = false;
	bool texxtureLoaded = false;
	std::vector<glm::vec3> getVertexBuffer();
	std::vector<glm::vec3> getNormalBuffer();
	std::vector<glm::vec2> getUvBuffer();
private:
	glm::vec3 __renderable_position;					//position of the object relative to center of the scene
	glm::vec3 __renderable_rotation;					//rotation of the object
	GLfloat __renderable_scale = 1.0;
	//------------------------------------------
	// GL identifiers (render loop data):
	//------------------------------------------
	GLuint texture;						//ID of texture for the object
	GLuint vertexBuffer;				//ID of vertex buffer for the object
	GLuint uvBuffer;					//ID of UV buffer for the object
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
	std::vector<glm::vec3> indexedVertices;
	std::vector<glm::vec2> indexedUv;
	std::vector<glm::vec3> indexedNormals;
};