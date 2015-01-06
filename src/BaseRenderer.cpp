#include "BaseRenderer.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include "CPPLogger.h"


BaseRenderer::BaseRenderer()
{
	glErrorlogPeriodicKey = Log::getInstance()->getLogPeriodicKey(2);
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(1024, 768, "Game10", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window, OpenGL version not supported\n");
		glfwTerminate();
	}
}
void BaseRenderer::clear(float r, float g, float b, float a, bool depth)
{
    glClearColor(r, g, b, a);
    if (depth)
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
void BaseRenderer::checkGLError(){
	int err = glGetError();
	if (err != 0){
		std::stringstream ss;
		ss << glewGetErrorString(glGetError());
		AggregationParam param(ss.str(), AggregationParamType::COUNT);
		std::stringstream ss2;
		ss2 << "GLErrors: " << ss.str();
		Log::periodicAggregate(ss2.str(), { AGGREGATE_SELECT_DISTINCT }, glErrorlogPeriodicKey, DebugKey::GL_ERRORS);
	}
}
void BaseRenderer::flush()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}