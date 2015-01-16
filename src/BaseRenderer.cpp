#include "BaseRenderer.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include "CPPLogger.h"

void errorCallback(int error, const char* description)
{
	std::cout << "GLError: " << description << std::endl;
}

BaseRenderer::BaseRenderer()
{
	if (!glfwInit())
	{
		Logger::error("Failed to initialize GLFW\n");
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(1024, 768, "Game10", NULL, NULL);
	if (window == NULL){
		Logger::error("Failed to open GLFW window, OpenGL version not supported\n");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		Logger::error("Failed to initialize GLEW\n");
	}
	glfwSetErrorCallback(errorCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}
void BaseRenderer::clear(float r, float g, float b, float a, bool depth)
{
    glClearColor(r, g, b, a);
    if (depth)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void BaseRenderer::flush()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}