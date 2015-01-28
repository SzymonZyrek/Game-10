#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Renderable.h"
#include <vector>

class TextureLoader {
public:
	TextureLoader();
	void TextureLoader::loadTextures(Renderable &renderable);
private:
	void loadTextures(Renderable &renderable, std::vector<std::string> imagePaths);
	GLuint reallyLoadTextures(std::vector<std::string> imagePaths);
};