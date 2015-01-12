


#include "SimpleRenderer.h"
#include <GL/glew.h>
#include "GLFW\glfw3.h"
#include <iostream>
#include "CPPIdentifiable.h"
#include <memory>
#include "Testing.h"
#include "TestResult.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "CPPLogger.h"
#include "ShadersLoader.h"
#include "TextureLoader.h"
#include "ModelLoader.h"

unsigned int fpsLogPeriodicKey = Log::getInstance()->getLogPeriodicKey(1.0);
unsigned int glLogPeriodicKey = Log::getInstance()->getLogPeriodicKey(3.0);
static void error_callback(int error, const char* description)
{
	Logger logger({ Aggregate::COUNT_DISTINCT }, glLogPeriodicKey, DebugKey::GL_ERRORS);
	std::stringstream ss;
	ss << description;
	logger << ss;
}
void SimpleRenderer::init()
{	
	glfwMakeContextCurrent(window);
	model.loadObjFile("ball.obj");
	TextureLoader texture;
	textureDataID = texture.loadTexture("fabric.jpg");

	programID = ShadersLoader::loadShaders("SimplestVertexShader.glsl", "SimplestFragmentShader.glsl");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Shader data placeholders
	matrixID = glGetUniformLocation(programID, "MVP");
	textureBuffer = glGetUniformLocation(programID, "myTextureSampler");

	std::vector<glm::vec3> vertices = model.indexedVertices;
	std::vector<glm::vec2> uvs = model.indexedUv;
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(glm::vec3)), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

}

void SimpleRenderer::update()
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
	Logger logger({ Aggregate::COUNT }, fpsLogPeriodicKey, DebugKey::RENDERING);
	std::stringstream ss;
	ss << "FPS:" << AggregationParam("");
	logger << ss;
}

void SimpleRenderer::render()
{
    clear();
    //drawTraingle();
	drawModel();
    flush();
}

void  SimpleRenderer::drawModel() {
	glfwMakeContextCurrent(window);
	glm::vec3 renderablePosition(0, 0, 0);
	glm::vec3 renderableRotation(0, 0, 0);
	glm::vec3 renderableScale(1.0, 1.0, 1.0);
	
	glUseProgram(programID);
	glActiveTexture(GL_TEXTURE0);

	glm::mat4 ModelMatrix = glm::mat4(1.0);
	// Translate
	ModelMatrix = glm::translate(ModelMatrix, renderablePosition);
	// Rotate
	ModelMatrix = glm::rotate(ModelMatrix, renderableRotation.x, glm::vec3(1, 0, 0));
	ModelMatrix = glm::rotate(ModelMatrix, renderableRotation.y, glm::vec3(0, 1, 0));
	ModelMatrix = glm::rotate(ModelMatrix, renderableRotation.z, glm::vec3(0, 0, 1));
	//Scale
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(renderableScale.x, renderableScale.y, renderableScale.z));

	glm::mat4 MVP = projectionMatrix * viewMatrix * ModelMatrix;
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
	glBindTexture(GL_TEXTURE_2D, textureDataID);

	glUniform1i(textureBuffer, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);
	GLuint indices = model.getVertexCount();
	glDrawArrays(GL_TRIANGLES, 0, indices);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void  SimpleRenderer::draw() {
	glUseProgram(programID);
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
}

void SimpleRenderer::drawTraingle()
{
	glUseProgram(programID);
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
}

void SimpleRenderer::drawTriangles()
{
	glfwMakeContextCurrent(window);
	
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *vSrc = vertexSource.str().c_str();
	glShaderSource(vertexShader, 1, &vSrc, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *fSrc = fragmentSource.str().c_str();
	glShaderSource(fragmentShader, 1, &fSrc, NULL);
	glCompileShader(fragmentShader);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBeginVideoCaptureNV(8);
	checkGLError();
}

void SimpleRenderer::resetShift()
{
    this->shitf = 0.0;
}