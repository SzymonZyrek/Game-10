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
	//glViewport(0, 0, 1024, 768);
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);


	// Create and compile our GLSL program from the shaders
	//programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

	// Shader data placeholders
	//MatrixID = glGetUniformLocation(programID, "MVP");
	//TextureID = glGetUniformLocation(programID, "myTextureSampler");
	//this->camera = std::make_shared<Camera>(window);


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
		Log::periodicAggregate(ss2.str(), { Aggregate::SELECT_DISTINCT }, glErrorlogPeriodicKey, DebugKey::GL_ERRORS);
	}
}
void BaseRenderer::flush()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}