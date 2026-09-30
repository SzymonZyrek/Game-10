#pragma once
#include <string.h>
#include "Renderable.h"
#include "CPPLogger.h"
#define SHADER_NULLVALUE 999999
class ShadersLoader {
public:
	ShadersLoader();
	bool fragmentShaderLoaded = false;
	bool vertexShaderLoaded = false;
	void loadVertexShader(std::string shaderName);
	void loadShaderProgram(Renderable& renderable);
	GLuint loadShaderProgram();
	void loadFragmentShader(std::string shaderName);
private:
	static Logger shadersLogger;
	//static GLuint loadShaders(const char * vertex_file_path, const char * fragment_file_path);
	GLuint _programID = SHADER_NULLVALUE;
	GLuint _vertexShaderID = SHADER_NULLVALUE;
	GLuint _fragmentShaderID = SHADER_NULLVALUE;
};