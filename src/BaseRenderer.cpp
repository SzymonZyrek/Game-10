#include "BaseRenderer.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include "CPPLogger.h"
#include "Config.h"


bool BaseRenderer::glfwInitialized = false;
bool BaseRenderer::glewInitialized = false;
GLFWwindow *BaseRenderer::defaultWindow;

void errorCallback(int error, const char* description)
{
	std::cout << "GLError: " << description << std::endl;
}

void BaseRenderer::initGlfw(){
	if (!glfwInit())
	{
		Logger::error("Failed to initialize GLFW\n");
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	resolutionX = mode->width;
	resolutionY = mode->height;
}

void BaseRenderer::initGlew(){
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		Logger::error("Failed to initialize GLEW\n");
	}
	glfwSetErrorCallback(errorCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, resolutionX / 2, resolutionY / 2);
}

void BaseRenderer::createWindow(){
	if (Config::getStringProperty(FULLSCREEN) == "YES")
	{
		this->window = glfwCreateWindow(resolutionX, resolutionY, "Game10", glfwGetPrimaryMonitor(), NULL);
	}
	else {
		this->window = glfwCreateWindow(resolutionX, resolutionY, "Game10", NULL, NULL);
	}
	if (window == NULL){
		glfwTerminate();
		throw "Failed to open GLFW window, OpenGL version not supported\n";
	}
}
GLFWwindow* BaseRenderer::getWindow()
{
	return this->window;
}
BaseRenderer::BaseRenderer(GLFWwindow* window)
{
	if (!BaseRenderer::glfwInitialized)
	{
		initGlfw();
	}
	if (!BaseRenderer::glewInitialized)
	{
		initGlew();
	}
	this->window = window;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

BaseRenderer::BaseRenderer()
{
	if (!BaseRenderer::glfwInitialized)
	{
		initGlfw();
	}
	if (defaultWindow == nullptr){
		createWindow();
		defaultWindow = window;
	}
	else{
		window = defaultWindow;
	}
	if (!BaseRenderer::glewInitialized)
	{
		initGlew();
	}

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