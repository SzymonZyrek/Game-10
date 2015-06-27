#include "BaseRenderer.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include "CPPLogger.h"
#include "Config.h"


bool BaseRenderer::glfwInitialized = false;
bool BaseRenderer::glewInitialized = false;
GLFWwindow*  BaseRenderer::defaultWindow;
void errorCallback(int error, const char* description)
{
	std::cout << "GLError: " << description << std::endl;
}


// This method initialises OpenGL FrameWork, sets OpenGL version, antialiasing, resolution etc.
void BaseRenderer::initGlfw(){
	if (!glfwInit())
	{
		Logger::error("Failed to initialize GLFW\n");
	}
	// antialiasing:   4 samples
	glfwWindowHint(GLFW_SAMPLES, 4);
	// target version: OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// save resolution
	const GLFWvidmode * displayMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	resolutionX = displayMode->width;
	resolutionY = displayMode->height;
}

// This method initialises OpenGL Extension Wrangler, which takes care of loading OpenGL function pointers, extensions, etc.
void BaseRenderer::initGlew(){
	// "bind" glfw context of the window to thread
	glfwMakeContextCurrent(window);
	// we want to expose every extension with valid entry point,
	// not only those reported to be supported
	glewExperimental = true;
	// initialise glew (get function pointers)
	if (glewInit() != GLEW_OK) {
		Logger::error("Failed to initialize GLEW\n");
	}
	// setup function to get errors from OpenGL,
	glfwSetErrorCallback(errorCallback);
	// turn on "sticky keys" 
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// set cursor to center of the screen
	glfwSetCursorPos(window, resolutionX / 2, resolutionY / 2);
}

// This method creates an GLFWWindow, based on FULLSCREEN config paramter
// @Config FULLSCREEN If set to yes, opens full screen window on primary monitor, otherwise- opens a regular window.
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
// This method returns this renderers window
// @Returns Window assigned to this renderer
GLFWwindow* BaseRenderer::getWindow()
{
	return this->window;
}
// This constructor creates a BaseRender object given a GLFW window instance.
// It handles initialising glfw, glew if necessary and sets some OpenGL state.
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
	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

// This constructor creates a BaseRender object and also takes care of creating a window.
// It handles initialising glfw, glew if necessary and sets some OpenGL state.
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
	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

// This method performs a glClear with a given color. It also handles clearing depth
// buffer if given true as the last parameter
void BaseRenderer::clear(float r, float g, float b, float a, bool depth)
{
    glClearColor(r, g, b, a);
    if (depth)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
// This method swaps buffers (to present complete frame to a screen) and polls
// events
void BaseRenderer::flush()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}