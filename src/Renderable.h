#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderable {
public:
	Renderable(std::string modelName, std::string textureName);

	// First step data- filenames
	std::string textureName;
	std::string modelName;

	bool modelLoaded = false;
	bool textureLoaded = false;
	// Second step- data loaded from files
	std::vector<glm::vec3> indexedVertices;
	std::vector<glm::vec3> indexedNormals;
	std::vector<glm::vec2> indexedUv;
	unsigned int vertexCount;

	bool modelInitialized = false;
	// Third step- data initialized into opengl
	GLuint textureBufferID;
	GLuint vertexBufferID;
	GLuint uvBufferID;
	GLuint normalbufferID;

};