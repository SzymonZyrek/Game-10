


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
	std::cout << "GLERROR: "<< description;
}
void SimpleRenderer::init()
{
	// VAO initialization
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	// Camera initialization
	this->camera = std::make_shared<Camera>(window);
	glfwSetErrorCallback(error_callback);
	// The framebuffer
	glGenFramebuffers(1, &fxFrameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, fxFrameBufferID);
	//Target texture
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	TextureLoader loader;
	fxMapID = loader.createTargetTexture(width, height);
	// The depth buffer
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	// Set "targerTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fxMapID, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw "Framebuffer is fucked up m8";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	this->initialised = true;
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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		camera->position += ((glm::normalize(camera->getDirection())*(float)0.04));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		camera->position -= ((glm::normalize(camera->getDirection())*(float)0.04));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		camera->position -= ((glm::normalize(camera->right)*(float)0.04));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		camera->position += ((glm::normalize(camera->right)*(float)0.04));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		camera->position += ((glm::normalize(camera->up)*(float)0.04));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
		camera->position -= ((glm::normalize(camera->up)*(float)0.04));
	}
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS){
		if (testValue < 1)testValue += 0.001; std::cout << "val" << testValue << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS){
		if (testValue > -1)testValue -= 0.001; std::cout << "val" << testValue << std::endl;
	}
}

void SimpleRenderer::renderToFramebuffer(Scene &scene, GLuint frameBufferID, unsigned int width, unsigned int height){
	int originalWidth, originalHeight;
	glfwGetWindowSize(window, &originalWidth, &originalHeight);
	// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	glViewport(0, 0, width, height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
	//clear the framebuffer
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
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, originalWidth, originalHeight);
}

void SimpleRenderer::render(Scene &scene)
{
	int w, h;
	glfwGetWindowSize(window, &w, &h);
	renderToFramebuffer(scene, fxFrameBufferID, w, h);
	//TODO: remove this nasty hack!
	// And now the ugliest hack, initializing some test game objects in.. the render method :D
	// is he retarded? nnah, its just late
	if (test){
		std::string modelFileName = Config::getMainConfig().getProperty(DEFAULT_MODEL_FILE_NAME);
		std::string textureFileName = Config::getMainConfig().getProperty(DEFAULT_TEXTURE_FILE_NAME);
		//
		//GameObject* go = new GameObject;
		//go->setRenderableComponent(std::make_shared<RenderableComponent>(modelFileName, false));
		//go->setPhysicalComponent(std::make_shared<PhysicalComponent>());
		//scene.registerGameObject(go);
		
		GameObject* viking_s = new GameObject;
		viking_s->setRenderableComponent(std::make_shared<RenderableComponent>("viking_flat", "TransformVertexShader", "TextureFragmentShader", true));
		viking_s->getRenderableComponent()->position.z -= 2.5;
		viking_s->getRenderableComponent()->position.y += 0.5;
		viking_s->setPhysicalComponent(std::make_shared<PhysicalComponent>());
		scene.registerGameObject(viking_s);

		GameObject* viking = new GameObject;
		viking->setRenderableComponent(std::make_shared<RenderableComponent>("viking_smooth", "TransformVertexShader", "TextureFragmentShader", true));
		viking->getRenderableComponent()->position.z -= 1.5;
		viking->getRenderableComponent()->position.y += 0.5;
		viking->setPhysicalComponent(std::make_shared<PhysicalComponent>());
		scene.registerGameObject(viking);

		GameObject* gameObject2 = new GameObject;
		gameObject2->setRenderableComponent(std::make_shared<RenderableComponent>("longship", "TransformVertexShader", "TextureFragmentShader", true));
		scene.registerGameObject(gameObject2);

		ModelLoader loader;
		GameObject* sky = new GameObject;
		sky->setRenderableComponent(std::make_shared<RenderableComponent>(std::make_shared<Renderable>("skydome_s", "TransformVertexShader", "SkyboxFragmentShader", true)));
		scene.registerGameObject(sky);
		GameObject* ground = new GameObject;
		ground->setRenderableComponent(std::make_shared<RenderableComponent>(std::make_shared<Renderable>("ground_simplest", "TransformVertexShader", "TextureFragmentShader", true)));
		scene.registerGameObject(ground);
		test = false;
	}
	//END(NASTYHACK)
	// clear framebuffer
    clear();
	// The fullscreen quad's FBO
	GLuint quad_VertexArrayID;
	glGenVertexArrays(1, &quad_VertexArrayID);
	glBindVertexArray(quad_VertexArrayID);

	static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	ShadersLoader shadersLoader;
	shadersLoader.loadVertexShader("PassthroughVertexshader");
	shadersLoader.loadFragmentShader(Config::getStringProperty(DEFAULT_FRAGMENT_SHADER_FILE_NAME));
	GLuint quad_programID = shadersLoader.loadShaderProgram();
	GLuint texID = glGetUniformLocation(quad_programID, "renderedTexture");
	GLuint timeID = glGetUniformLocation(quad_programID, "time");

	glUseProgram(quad_programID);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fxMapID);
	// Set our "renderedTexture" sampler to user Texture Unit 0
	glUniform1i(texID, 0);

	glUniform1f(timeID, (float)(glfwGetTime()*10.0f));

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(0);





	//// draw renderables
	//for (RenderableComponent &theRenderable : scene._renderables){
	//	if (theRenderable){
	//		draw(theRenderable);
	//	}
	//	else{
	//		// end of the line pal, renderables should be sorted,
	//		// active ones in front, so the one before first inactive
	//		// was the last to draw
	//		break;
	//	}
	//}
	//// swap buffers and poll glfw events
}

void  SimpleRenderer::draw(RenderableComponent &theRenderable) {
	//TODO: remove this nasty hack!
	if (theRenderable.getRenderable()->modelName == "skydome"  || theRenderable.getRenderable()->modelName == "skydome_s"){
		theRenderable.position.x = camera->getPosition().x;
		theRenderable.position.z = camera->getPosition().z;
	}


	//END(NASTYHACK)
	// Shader and uniforms placeholders initialization
	glUseProgram(theRenderable.programID);
	GLuint mpvMatrixID = glGetUniformLocation(theRenderable.programID, "MVP");
	GLuint modelMatrixID = glGetUniformLocation(theRenderable.programID, "M");
	GLuint viewMatrixID = glGetUniformLocation(theRenderable.programID, "V");
	GLint myTextureSampler = glGetUniformLocation(theRenderable.programID, "myTextureSampler");
	GLint normalMap = glGetUniformLocation(theRenderable.programID, "normalMap");
	GLint shadowMap = glGetUniformLocation(theRenderable.programID, "shadowMap");
	GLuint MV3x3ID = glGetUniformLocation(theRenderable.programID, "MV3x3");
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
	glm::mat4 MV = viewMatrix * modelMatrix;
	glm::mat3 MV3x3 = glm::mat3(MV);
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
	glUniformMatrix3fv(MV3x3ID, 1, GL_FALSE, &MV3x3[0][0]);
	//glProgramUniform1ui(theRenderable.programID, textureDataID, 0);
	// Bind texture to GL_TEXTURE0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, theRenderable.textureBufferID);
	glUniform1i(myTextureSampler, 0);
	
	//TODO: uncomment 
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D_ARRAY, theRenderable.normalMapID);
	glUniform1i(normalMap, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, fxMapID);
	glUniform1i(shadowMap, 2);

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
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, theRenderable.materialBufferID);
	glVertexAttribIPointer(
		3,                                // vertexattribarray number
		1,                                // size of 'row' of data
		GL_INT,                         // data type
		//GL_TRUE,                         // normalized?
		0,                                // stride
		(void*)0                          // offset*
		);

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, theRenderable.tangentBufferID);
	glVertexAttribPointer(
		4,                                // vertexattribarray number
		3,                                // size of 'row' of data
		GL_FLOAT,                         // data type
		GL_FALSE,
		//GL_TRUE,                         // normalized?
		0,                                // stride
		(void*)0                          // offset*
		);

	glEnableVertexAttribArray(5);
	glBindBuffer(GL_ARRAY_BUFFER, theRenderable.bitangentBufferID);
	glVertexAttribPointer(
		5,                                // vertexattribarray number
		3,                                // size of 'row' of data
		GL_FLOAT,                         // data type
		GL_FALSE,
		//GL_TRUE,                         // normalized?
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
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
}
