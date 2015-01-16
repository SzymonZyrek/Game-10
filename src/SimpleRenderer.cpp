


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
#include "RenderableComponent.h"

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

	ModelLoader model(mdoelFileName);
	model.loadObjFile(renderable);

	glfwMakeContextCurrent(window);

	TextureLoader texture(textureFileName);
	texture.loadTexture(renderable);

	programID = ShadersLoader::loadShaders(
		vertexShaderFileName.c_str(),
		fragmentShaderFileName.c_str()
		);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Shader data placeholders
	mpvMatrixID = glGetUniformLocation(programID, "MVP");
	modelMatrixID = glGetUniformLocation(programID, "M");
	viewMatrixID = glGetUniformLocation(programID, "V");
	textureBufferID = glGetUniformLocation(programID, "myTextureSampler");

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, (renderable.indexedVertices.size() * sizeof(glm::vec3)), &renderable.indexedVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
	glBufferData(GL_ARRAY_BUFFER, renderable.indexedUv.size() * sizeof(glm::vec2), &renderable.indexedUv[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbufferID);
	glBindBuffer(GL_ARRAY_BUFFER, normalbufferID);
	glBufferData(GL_ARRAY_BUFFER, renderable.indexedNormals.size() * sizeof(glm::vec3), &renderable.indexedNormals[0], GL_STATIC_DRAW);

	this->camera = std::make_shared<Camera>(window);
	renderablePosition = glm::vec3(0, 0, 0);
	renderableRotation = glm::vec3(0, 0, 0);

	lightID = glGetUniformLocation(programID, "LightPosition_worldspace");
	testValueId = glGetUniformLocation(programID, "TestValue");
	glUseProgram(programID);
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
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS){ if (testValue<1)testValue += 0.001; std::cout << "val" << testValue << std::endl; }
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS){ if (testValue>-1)testValue -= 0.001; std::cout << "val" << testValue << std::endl; }
}

void SimpleRenderer::render()
{
    clear();
	draw();
    flush();
}

void  SimpleRenderer::draw() {
	glfwMakeContextCurrent(window);
	//renderableRotation.y -= 0.1;
	glm::vec3 renderableScale(1, 1, 1);

// Calculate matrices:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix = glm::mat4(1.0);
	// Apply camera (its position and direction influences V&P matrices)
	this->camera->applyCameraToMatrices(GameLoop::deltaTime, &viewMatrix, &projectionMatrix);
	// Translate
	modelMatrix = glm::translate(modelMatrix, renderablePosition);
	// Rotate
	modelMatrix = glm::rotate(modelMatrix, renderableRotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, renderableRotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, renderableRotation.z, glm::vec3(0, 0, 1));
	// Scale
	modelMatrix = glm::scale(modelMatrix, glm::vec3(renderableScale.x, renderableScale.y, renderableScale.z));
	// Calculate MdelViewProjaction matrix
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

// Send uniforms:
	glUniform1f(testValueId, testValue);
	//glUniform1i(textureBufferID, 0);
	glUniform3f(lightID, camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	// 
	glUniformMatrix4fv(mpvMatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderable.textureDataID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbufferID);
	glVertexAttribPointer(
		2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);
	glDrawArrays(GL_TRIANGLES, 0, renderable.vertexCount);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
