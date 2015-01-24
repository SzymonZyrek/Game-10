


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
	// VAO initialization
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	// Camera initialization
	this->camera = std::make_shared<Camera>(window);
}

void SimpleRenderer::update()
{
	// Log FPS:
	Logger logger({ Aggregate::COUNT }, fpsLogPeriodicKey, DebugKey::RENDERING);
	std::stringstream ss;
	ss << "FPS:" << AggregationParam("");
	logger << ss;
	// Save cursor offset,
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	// update camera "look-at" point,
	camera->updateLookAtPoint(GameLoop::deltaTime, (float)xpos, (float)ypos);
	// and reset cursor at center
	glfwSetCursorPos(window, resolutionX / 2, resolutionY / 2);
	// Temporary lame input handling ;p
	// TODO: yeah, you guessed right- get this code away from here ^^
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
	// And now the ugliest hack, initializing some test game objects in.. the render method :D
	// is he retarded? nnah, its just late
	if (test){
		std::string mdoelFileName = Config::getMainConfig().getProperty(DEFAULT_MODEL_FILE_NAME);
		std::string textureFileName = Config::getMainConfig().getProperty(DEFAULT_TEXTURE_FILE_NAME);
		GameObject* gameObject = new GameObject;
		gameObject->setRenderableComponent(std::make_shared<RenderableComponent>(mdoelFileName,textureFileName, true));
		gameObject->setPhysicalComponent(std::make_shared<PhysicalComponent>());
		scene.registerGameObject(gameObject);
		ModelLoader loader;
		//GameObject* gameObject2 = new GameObject;
		//gameObject2->setRenderableComponent(std::make_shared<RenderableComponent>(std::make_shared<Renderable>("church.obj", "RoughBlockWall-ColorMap_256x256.jpg")));
		//scene.registerGameObject(gameObject2);
		test = false;
	}
	// clear framebuffer
    clear();
	// draw renderables
	for (RenderableComponent &theRenderable : scene._renderables){
		if (theRenderable){
			draw(theRenderable);
		}
		else{
			// end of the line pal, renderables should be sorted,
			// active ones in front, so the one before first inactive
			// was the last to draw
			break;
		}
	}
	// swap buffers and poll glfw events
    flush();
}

void  SimpleRenderer::draw(RenderableComponent &theRenderable) {
	// Shader and uniforms placeholders initialization
	glUseProgram(theRenderable.programID);
	GLuint mpvMatrixID = glGetUniformLocation(theRenderable.programID, "MVP");
	GLuint modelMatrixID = glGetUniformLocation(theRenderable.programID, "M");
	GLuint viewMatrixID = glGetUniformLocation(theRenderable.programID, "V");
	GLuint textureDataID = glGetUniformLocation(theRenderable.programID, "myTextureSampler");
	GLuint lightID = glGetUniformLocation(theRenderable.programID, "LightPosition_worldspace");
	testValueId = glGetUniformLocation(theRenderable.programID, "TestValue");
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
	// Send uniform values:
	// i dont think the below one is used anywhere...
	// TODO: investigate this shit
	// glUniform1i(textureBufferID, 0);
	glUniform3f(lightID, camera->getPosition().x, camera->getPosition().y, camera->getPosition().z); 
	glUniformMatrix4fv(mpvMatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
	// Bind texture to GL_TEXTURE0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, theRenderable.textureBufferID);
	// Bind vertex data to vertexattribarray0
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, theRenderable.vertexBufferID);
	glVertexAttribPointer(
		0,                  // vertexattribarray number
		3,                  // size of 'row' of data
		GL_FLOAT,           // data type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // offset*
		);
	// Bind texel data to vertexattribarray1
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, theRenderable.uvBufferID);
	glVertexAttribPointer(
		1,                                // vertexattribarray number
		2,                                // size of 'row' of data
		GL_FLOAT,                         // data type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // offset*
		);
	// bind normals data to vertexattribarray2
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theRenderable.normalbufferID);
	glVertexAttribPointer(
		2,                                // vertexattribarray number
		3,                                // size of 'row' of data
		GL_FLOAT,                         // data type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // offset*
		);

	if (!theRenderable.indexed)
	{
		glDrawArrays(GL_TRIANGLES, 0, theRenderable.vertexCount);
	} else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theRenderable.indexBufferId);
		glDrawElements(
			GL_TRIANGLES,
			theRenderable.indexCount,
			GL_UNSIGNED_INT,
			(void*)0
			);
	}
	// clean up
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
