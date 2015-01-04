
#pragma  once

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class BaseRenderer
{
public:
    virtual void init() = 0;
    virtual void render() = 0;
    virtual void update() = 0;

protected:
	BaseRenderer();
    void clear(float r=0,
               float g=0,
               float b=0,
               float a=0,
               bool depth=true);
    void flush();
	GLFWwindow *window; //window this renderer is 
private:

	//rendering to

};
