#define _CR1T_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "TextureLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "CPPLogger.h"
#include "STBImage.h"
#include <map>
#include "CPPLogger.h"

static std::map<std::string, GLuint> pathToTextureID;

Logger logger(DebugKey::TEXTURES);

TextureLoader::TextureLoader(std::string textureName){
	this->_texturePath = textureName;
}

GLuint TextureLoader::reallyLoadTexture(const char * imagepath){
	int x, y, n;
	std::stringstream ss;
	ss << "../resources/textures/" << imagepath << ".jpg";
	unsigned char *data = stbi_load(ss.str().c_str(), &x, &y, &n, STBI_rgb);

	if (data == nullptr){
		std::stringstream ss;
		ss << "Failed to load texture " << imagepath << std::endl;
		logger << ss;
	}
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (n == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else if (n == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	ss = std::stringstream("");
	ss << "Texture " << imagepath << ": width " << x << ",  height: " << y << ", n: " << n << ", data size: " << (x*y*n) << " loaded successfully" << std::endl;
	logger << ss;
	return textureID;
}
void TextureLoader::loadTexture(Renderable &renderable){
	if (pathToTextureID[_texturePath] == NULL){
		pathToTextureID[_texturePath] = reallyLoadTexture(_texturePath.c_str());
	}
	renderable.textureBufferID = pathToTextureID[_texturePath];
	renderable.textureLoaded = true;
}