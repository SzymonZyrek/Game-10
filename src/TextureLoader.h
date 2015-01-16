#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Renderable.h"
class TextureLoader {
public:
	TextureLoader(std::string textureName);
	void loadTexture(Renderable &renderable);
private:
	GLuint reallyLoadTexture(const char * imagepath);
	std::string _texturePath;
};