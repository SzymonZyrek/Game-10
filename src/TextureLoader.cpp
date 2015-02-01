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
static std::map<std::string, GLuint> pathToNormalMapID;

Logger logger(DebugKey::TEXTURES);

TextureLoader::TextureLoader(){
}

GLuint TextureLoader::reallyLoadTextures(std::vector<std::string> imagePaths){
	int x, y, n;
	std::stringstream ss;
	ss << "../resources/textures/" << imagePaths[0] << ".jpg";
	std::vector<unsigned char *> datas;
	for (std::string imagePath:imagePaths){
		std::stringstream ss;
		ss << "../resources/textures/" << imagePath << ".jpg";
		unsigned char *data = stbi_load(ss.str().c_str(), &x, &y, &n, STBI_rgb);
		if (data == nullptr){
			std::stringstream s2;
			s2 << "Failed to load texture " << ss.str() << std::endl;
			logger << s2;
		}
		datas.push_back(data);
	}
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
	//glGenerateMipmap(GL_TEXTURE_2D_ARRAY);		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, x, y, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
	if (n == 3){
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, x, y, datas.size(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		for (int i = 0; i < datas.size(); i++){
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, x, y, 1, GL_RGB, GL_UNSIGNED_BYTE, datas[i]);
		}
	}
	else if (n == 4){
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, x, y, datas.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		for (int i = 0; i < datas.size(); i++){
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, x, y, 1, GL_RGBA, GL_UNSIGNED_BYTE, datas[i]);
		}
	}

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	for (int i = 0; i < datas.size(); i++){
		stbi_image_free(datas[i]);
	}

	ss = std::stringstream("");
	ss << "Textures: ";
	for (int i = 0; i++; i < datas.size()){
		ss << imagePaths[i] << ", ";
	}
	ss << ": width " << x << ",  height: " << y << ", n: " << n << ", data size: " << (x*y*n) << " loaded successfully" << std::endl;
	logger << ss;
	return textureID;
}
void TextureLoader::loadTextures(Renderable &renderable){
	std::stringstream key;
	std::vector<std::string> orderedPaths(renderable.materialMap.size());
	std::vector<std::string> normalMapPaths(0);
	for (std::map<std::string, int>::iterator iter = renderable.materialMap.begin(); iter != renderable.materialMap.end(); ++iter)
	{
		std::string keyPart = iter->first;
		orderedPaths[iter->second] = keyPart;
	}
	for (std::string textureName : orderedPaths){
		key << textureName;
	}
	if (pathToTextureID[key.str()] == NULL){
		pathToTextureID[key.str()] = reallyLoadTextures(orderedPaths);
		for (std::string textureName : orderedPaths){
			std::stringstream ss;
			ss << textureName << "_nm";
			normalMapPaths.push_back(ss.str());
		}
		pathToNormalMapID[key.str()] = reallyLoadTextures(normalMapPaths);

	}
	renderable.textureBufferID = pathToTextureID[key.str()];
	renderable.normalMapID = pathToNormalMapID[key.str()];
	renderable.textureLoaded = true;
}

void TextureLoader::loadTextures(Renderable &renderable, std::vector<std::string> imagePaths){
	std::stringstream key;
	std::sort(imagePaths.begin(), imagePaths.end());
	for (std::string path:imagePaths){
		key << path;
	}
	if (pathToTextureID[key.str()] == NULL){
		pathToTextureID[key.str()] = reallyLoadTextures(imagePaths);
	}
	renderable.textureBufferID = pathToTextureID[key.str()];
	renderable.normalMapID = pathToTextureID[key.str()];
	renderable.textureLoaded = true;
}