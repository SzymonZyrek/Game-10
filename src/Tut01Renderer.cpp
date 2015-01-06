


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

unsigned int logPeriodicKey = Log::getInstance()->getLogPeriodicKey(3.0);

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
	AggregationParam param("Update", AggregationParamType::COUNT);
	std::stringstream ss;
	ss << param << " updates";
	Log::periodicAggregate(ss.str(), { AGGREGATE_COUNT }, logPeriodicKey, DebugKey::RENDERING);
}

void Tut01Renderer::render()
{
    clear();
    drawTriangles();
    flush();
}

void Tut01Renderer::drawTriangles()
{
	float vertices[] = {
		0.0f, 0.5f, // Vertex 1 (X, Y)
		0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	GLuint vbo;
	doGL(glGenBuffers(1, &vbo)); // Generate 1 buffer
	doGL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	doGL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    
	std::stringstream vertexSource;
	vertexSource << "in vec2 position;" << std::endl
		<< "void main()" << std::endl
		<< "{" << std::endl
		<< "gl_Position = vec4(position, 0.0, 1.0);" << std::endl;
	std::stringstream fragmentSource;
	fragmentSource << "out vec4 outColor;<< std::endl"
		<< "void main()<< std::endl"
		<< "{"
		<< "outColor = vec4(1.0, 1.0, 1.0, 1.0);";
	doGL(
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *vSrc = vertexSource.str().c_str();
	glShaderSource(vertexShader, 1, &vSrc, NULL);
	glCompileShader(vertexShader);
	)
	doGL(
	GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *fSrc = fragmentSource.str().c_str();
	glShaderSource(fragmentShader, 1, &fSrc, NULL);
	glCompileShader(fragmentShader);
	)
	doGL(
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	)
	doGL(
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);
	)
	doGL(
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	)
		doGL(glDrawArrays(GL_TRIANGLES, 0, 3);)

	glBeginVideoCaptureNV(8);
	checkGLError();
}

void Tut01Renderer::resetShift()
{
    this->shitf = 0.0;
}