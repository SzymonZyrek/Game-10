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

GLuint ShadersLoader::loadShaders(const char * vertex_file_path, const char * fragment_file_path){
	Logger logger(DebugKey::SHADERS);
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::stringstream ss;
	ss << "../resources/shaders/" << vertex_file_path;

	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(ss.str().c_str(), std::ios::in);
	if (VertexShaderStream.is_open()){
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	ss = std::stringstream("");
	ss << "../resources/shaders/" << fragment_file_path;
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


	ss = std::stringstream("");
	// Compile Vertex Shader
	ss << "Compiling shader: " << vertex_file_path;
	logger << (ss << "\n");
	
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	
	ss = std::stringstream("");
	ss << &VertexShaderErrorMessage[0];
	logger << (ss << "\n");


	// Compile Fragment Shader
	ss = std::stringstream("");
	ss << "Compiling shader: " << fragment_file_path;
	logger << (ss << "\n");
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	ss = std::stringstream("");
	ss << &FragmentShaderErrorMessage[0];
	logger << (ss << "\n");




	// Link the program
	ss = std::stringstream("");
	ss << "Linking program";
	logger << (ss << "\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(max(InfoLogLength, int(1)));
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	ss = std::stringstream("");
	ss << &ProgramErrorMessage[0];
	logger << (ss << "\n");


	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
