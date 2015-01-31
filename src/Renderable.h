#pragma once
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Config.h"
#include <GLFW/glfw3.h>
#include <string>

class Renderable {
public:
	Renderable(std::string modelName,
		std::string textureName,
		std::string vertexShaderName,
		std::string fragmentShaderName,
		bool indexed);

	Renderable(std::string modelName,
	std::string textureName, bool indexed);
	std::vector<std::string> textureNames;
	std::map<std::string, int> materialMap;

	// Loading stage status bools
	bool modelLoaded = false;
	bool textureLoaded = false;
	bool shadersLoaded = false;
	bool modelInitialized = false;
	bool indexed = false;

	// Metadata: where is my data, dude?
	std::string modelName = Config::getStringProperty(DEFAULT_MODEL_FILE_NAME);
	std::string textureName = Config::getStringProperty(DEFAULT_TEXTURE_FILE_NAME);
	std::string vertexShaderName = Config::getStringProperty(DEFAULT_VERTEX_SHADER_FILE_NAME);
	std::string fragmentShaderName = Config::getStringProperty(DEFAULT_FRAGMENT_SHADER_FILE_NAME);

	// Plain data- contingous arrays of data
	std::vector<glm::vec3> meshVertices;
	std::vector<glm::vec3> meshNormals;
	std::vector<glm::vec2> meshUvs;
	std::vector<GLint> meshMaterialCoords;

	// This method transforms plain data
	// into indexed data
	void index();

	// Indexed data- arrays of unique vertices,
	// indexed with indices array
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> indexedVertices;
	std::vector<glm::vec3> indexedNormals;
	std::vector<glm::vec2> indexedUvs;
	std::vector<GLint> indexedMaterialCoords;

	// Data counters
	unsigned int vertexCount = 0;
	unsigned int indexCount = 0;

	// Id's of opengl data hook-ups
	GLuint textureBufferID;
	GLuint indexBufferID;
	GLuint vertexBufferID;
	GLuint uvBufferID;
	GLuint normalbufferID;
	GLuint materialBufferID;
	GLuint programID;
};
std::ostream& operator<<(std::ostream &strm, Renderable &a);