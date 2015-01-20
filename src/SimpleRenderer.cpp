


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
#include "RenderDataLoader.h"

#define SHIFT_MOVE 0.f

unsigned int fpsLogPeriodicKey = Log::getInstance()->getLogPeriodicKey(1.0);
unsigned int glLogPeriodicKey = Log::getInstance()->getLogPeriodicKey(3.0);
static void error_callback(int error, const char* description)
{
	Logger logger({ Aggregate::SELECT_DISTINCT }, glLogPeriodicKey, DebugKey::GL_ERRORS);
	std::stringstream ss;
	ss << description;
	logger << ss;
}
void SimpleRenderer::init()
{	
	
	std::string vertexShaderFileName = Config::getMainConfig().getProperty(DEFAULT_VERTEX_SHADER_FILE_NAME);
	std::string fragmentShaderFileName = Config::getMainConfig().getProperty(DEFAULT_FRAGMENT_SHADER_FILE_NAME);


	//renderableComponent[0].setRenderable(std::make_shared<Renderable>(mdoelFileName, textureFileName));

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
	textureDataID = glGetUniformLocation(programID, "myTextureSampler");

	this->camera = std::make_shared<Camera>(window);

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
	glfwSetCursorPos(window, resolutionX / 2, resolutionY / 2);
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

void SimpleRenderer::render(Scene &scene)
{
	if (test){
		std::string mdoelFileName = Config::getMainConfig().getProperty(DEFAULT_MODEL_FILE_NAME);
		std::string textureFileName = Config::getMainConfig().getProperty(DEFAULT_TEXTURE_FILE_NAME);
		GameObject* gameObject = new GameObject;
		gameObject->setRenderableComponent(std::make_shared<RenderableComponent>(std::make_shared<Renderable>(mdoelFileName, textureFileName)));
		gameObject->setPhysicalComponent(std::make_shared<PhysicalComponent>());
		scene.registerGameObject(gameObject);
		GameObject* gameObject2 = new GameObject;
		gameObject2->setRenderableComponent(std::make_shared<RenderableComponent>(std::make_shared<Renderable>("church.obj", "brick.jpg")));
		scene.registerGameObject(gameObject2);
		test = false;
	}
    clear();
	for (RenderableComponent &theRenderable : scene._renderables){
		if (theRenderable){
			draw(theRenderable);
			Logger logger({ Aggregate::SELECT_DISTINCT }, glLogPeriodicKey, DebugKey::GL_ERRORS);
			std::stringstream ss;
			ss << "Rendering";
			logger << ss;
		}
		else{
			break;
		}
	}
    flush();
}

void  SimpleRenderer::draw(RenderableComponent &theRenderable) {
	glfwMakeContextCurrent(window);
	
// Calculate matrices:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix = glm::mat4(1.0);
	// Apply camera (its position and direction influences V&P matrices)
	this->camera->applyCameraToMatrices(GameLoop::deltaTime, &viewMatrix, &projectionMatrix);
	// Translate
	modelMatrix = glm::translate(modelMatrix, theRenderable.position);
	// Rotate
	modelMatrix = glm::rotate(modelMatrix, theRenderable.rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, theRenderable.rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, theRenderable.rotation.z, glm::vec3(0, 0, 1));
	// Scale
	modelMatrix = glm::scale(modelMatrix, glm::vec3(theRenderable.scale.x, theRenderable.scale.y, theRenderable.scale.z));
	// Calculate MdelViewProjaction matrix
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

// Send uniforms:
	glUniform1f(testValueId, testValue);
	//glUniform1i(textureBufferID, 0);
	glUniform3f(lightID, camera->getPosition().x, camera->getPosition().y, camera->getPosition().z); 
	glUniformMatrix4fv(mpvMatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, theRenderable.textureBufferID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, theRenderable.vertexBufferID);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, theRenderable.uvBufferID);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theRenderable.normalbufferID);
	glVertexAttribPointer(
		2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);
	glDrawArrays(GL_TRIANGLES, 0, theRenderable.vertexCount);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
