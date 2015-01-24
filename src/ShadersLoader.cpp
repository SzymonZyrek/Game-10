#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <GL/glew.h>

#include "ShadersLoader.h"
#include "CPPLogger.h"

Logger ShadersLoader::shadersLogger(DebugKey::SHADERS);

void ShadersLoader::loadVertexShader(std::string shaderName){
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	std::stringstream ss;
	ss << "../resources/shaders/" << shaderName << ".glsl";

	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(ss.str().c_str(), std::ios::in);
	if (VertexShaderStream.is_open()){
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(_vertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(_vertexShaderID);

	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(_vertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(_vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(_vertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);

	ss = std::stringstream("");
	ss << &VertexShaderErrorMessage[0];
	if (ss.str().size() > 2)
	{
		shadersLogger << ss;
	}
	glAttachShader(_programID, _vertexShaderID);
	vertexShaderLoaded = true;
}
void ShadersLoader::loadFragmentShader(std::string shaderName){
	GLuint _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	std::stringstream ss;
	ss = std::stringstream("");
	ss << "../resources/shaders/" << shaderName << ".glsl";
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(ss.str().c_str(), std::ios::in);
	if (FragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	GLint Result = GL_FALSE;
	int InfoLogLength;
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(_fragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(_fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(_fragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(_fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(_fragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	ss = std::stringstream("");
	ss << &FragmentShaderErrorMessage[0];
	if (ss.str().size() > 2)
	{
		ShadersLoader::shadersLogger << ss;
	}
	glAttachShader(_programID, _fragmentShaderID);
	fragmentShaderLoaded = true;
}

ShadersLoader::ShadersLoader(){
	_programID = glCreateProgram();
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void ShadersLoader::loadShaderProgram(Renderable &renderalbe){
	if (!vertexShaderLoaded) {
		throw "VertexShader not loaded! Cannot create program!";
	}
	else if (!fragmentShaderLoaded){
		throw "FragmentShader not loaded! Cannot create program!";
	}
	else{
		glLinkProgram(_programID);

		GLint Result = GL_FALSE;
		int InfoLogLength;
		// Check the program
		glGetProgramiv(_programID, GL_LINK_STATUS, &Result);
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage(max(InfoLogLength, int(1)));
		glGetProgramInfoLog(_programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::stringstream ss;
		ss << &ProgramErrorMessage[0];
		if (ss.str().size() > 2)
		{
			shadersLogger << ss;
		}
		renderalbe.programID = _programID;
		renderalbe.shadersLoaded = true;
	}
}