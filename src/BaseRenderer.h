
#pragma  once

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#define assert(__EXPR__,__ERR__) if (!__EXPR__){result += TestResult(__ERR__); if (stopOnFailure) return result;}
#define doGL(__CONTENT__) __CONTENT__; checkGLError();

class BaseRenderer
{
public:
    virtual void init() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
protected:
	void BaseRenderer::checkGLError();
	BaseRenderer();
    void clear(float r=0,
               float g=0,
               float b=0,
               float a=0,
               bool depth=true);
    void flush();
	GLFWwindow *window;
private:
	unsigned int glErrorlogPeriodicKey;

};
