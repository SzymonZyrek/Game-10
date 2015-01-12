#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class TextureLoader {
public:
	GLuint loadTexture(const char * imagepath);
private:
	GLuint reallyLoadTexture(const char * imagepath);
};