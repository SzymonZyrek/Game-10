#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderable {
public:
	Renderable(std::string modelName, std::string textureName);

	bool modelLoaded = false;
	bool indexed = false;
	bool textureLoaded = false;
	bool shadersLoaded = false;

	// First (step) data- filenames,
	// these must be provided when instancing a Renderable
	std::string textureName;
	std::string modelName;
	// Second step- data loaded from files
	std::vector<glm::vec3> meshVertices;
	std::vector<glm::vec3> meshNormals;
	std::vector<glm::vec2> meshUvs;

	// Third step- index data back..
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> indexedVertices;
	std::vector<glm::vec3> indexedNormals;
	std::vector<glm::vec2> indexedUvs;

	unsigned int vertexCount;
	unsigned int indexCount;

	bool modelInitialized = false;
	// Third step- data initialized into opengl
	GLuint textureBufferID;
	GLuint indexBufferID;
	GLuint vertexBufferID;
	GLuint uvBufferID;
	GLuint normalbufferID;
	GLuint programID;
	void index();
};