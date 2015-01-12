


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
#include "GameLoop.h"
#include "Config.h"
#define SHIFT_MOVE 0.f

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
	std::string mdoelFileName = Config::getMainConfig().getProperty(DEFAULT_MODEL_FILE_NAME);
	std::string textureFileName = Config::getMainConfig().getProperty(DEFAULT_TEXTURE_FILE_NAME);
	std::string vertexShaderFileName = Config::getMainConfig().getProperty(DEFAULT_VERTEX_SHADER_FILE_NAME);
	std::string fragmentShaderFileName = Config::getMainConfig().getProperty(DEFAULT_FRAGMENT_SHADER_FILE_NAME);

	glfwMakeContextCurrent(window);
	model.loadObjFile(mdoelFileName);
	TextureLoader texture;
	textureDataID = texture.loadTexture(textureFileName.c_str());

	programID = ShadersLoader::loadShaders(
		vertexShaderFileName.c_str(),
		fragmentShaderFileName.c_str()
		);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Shader data placeholders
	matrixID = glGetUniformLocation(programID, "MVP");
	textureBuffer = glGetUniformLocation(programID, "myTextureSampler");

	std::vector<glm::vec3> vertices = model.indexedVertices;
	std::vector<glm::vec2> uvs = model.indexedUv;

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(glm::vec3)), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	this->camera = std::make_shared<Camera>(window);
	renderablePosition = glm::vec3(0, 0, 0);
	renderableRotation = glm::vec3(0, 0, 0);
}

void SimpleRenderer::update()
{
	Logger logger({ Aggregate::COUNT }, fpsLogPeriodicKey, DebugKey::RENDERING);
	std::stringstream ss;
	ss << "FPS:" << AggregationParam("");
	logger << ss;

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	// and reset it for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);
	camera->updateLookAtPoint(GameLoop::deltaTime, (float)xpos, (float)ypos);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){ camera->position += ((glm::normalize(camera->getDirection())*(float)0.04)); }
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){ camera->position -= ((glm::normalize(camera->getDirection())*(float)0.04)); }
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){ camera->position -= ((glm::normalize(camera->right)*(float)0.04)); }
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){ camera->position += ((glm::normalize(camera->right)*(float)0.04)); }
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){ camera->position += ((glm::normalize(camera->up)*(float)0.04)); }
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){ camera->position -= ((glm::normalize(camera->up)*(float)0.04)); }
}

void SimpleRenderer::render()
{
    clear();
	drawModel();
    flush();
}

void  SimpleRenderer::drawModel() {
	glfwMakeContextCurrent(window);
	renderableRotation.y -= 0.1;
	glm::vec3 renderableScale(1, 1, 1);
	
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
	this->camera->applyCameraToMatrices(GameLoop::deltaTime, &viewMatrix, &projectionMatrix);
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
