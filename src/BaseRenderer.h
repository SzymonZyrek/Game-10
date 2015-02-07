
#pragma  once

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "CPPLogger.h"
#include "Scene.h"
#define assert(__EXPR__,__ERR__) if (!__EXPR__){result += TestResult(__ERR__); if (stopOnFailure) return result;}
#define doGL(__CONTENT__) __CONTENT__; checkGLError();

class BaseRenderer
{
public:
    virtual void init() = 0;
    virtual void render(Scene &scene) = 0;
    virtual void update() = 0;
	BaseRenderer();
	BaseRenderer::BaseRenderer(GLFWwindow* window);
	bool initialised = false;
	GLFWwindow* getWindow();
	void flush();
protected:
	GLFWwindow *window;
	static GLFWwindow *defaultWindow;
    void clear(float r=0,
               float g=0,
               float b=0,
               float a=0,
               bool depth=true);
	unsigned int resolutionX;
	unsigned int resolutionY;
	void initGlfw();
	static bool glfwInitialized;
	void initGlew();
	static bool glewInitialized;
	void createWindow();
};
