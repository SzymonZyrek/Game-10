


#include "Tut01Renderer.h"
#include <GL/glew.h>
#include "GLFW\glfw3.h"
#include <iostream>
#include "CPPIdentifiable.h"
#include <memory>
#include "Testing.h"
#include "TestResult.h"
#include <glm/glm.hpp>
#include "CPPLogger.h"

void Tut01Renderer::init()
{
	

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	shitfDirection = 1;
	shitf = 0.0f;

	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	//programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

	// Shader data placeholders
	//MatrixID = glGetUniformLocation(programID, "MVP");
	//TextureID = glGetUniformLocation(programID, "myTextureSampler");
	//this->camera = std::make_shared<Camera>(window);
    
}

void Tut01Renderer::update()
{
#define SHIFT_MOVE 0.f
    if (shitfDirection==1)
    {
        shitf += SHIFT_MOVE;
    }
    else
    {
        shitf -= SHIFT_MOVE;
        if (shitf <= 0.0)
        {
            shitfDirection = 1;
        }
    }
	Log::debug("Update",DebugKey::RENDERING);
}

void Tut01Renderer::render()
{
    clear();
    drawTriangles();
    flush();
}

void Tut01Renderer::drawTriangles()
{
    glColor3f(1.0, 0.85, 0.35);
    
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(-1.0+shitf, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    
        glColor3f(1.0f, 0.0f, 0.35f);
    
        glVertex3f(1.0-shitf, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    }
    glEnd();
    
}

void Tut01Renderer::resetShift()
{
    this->shitf = 0.0;
}