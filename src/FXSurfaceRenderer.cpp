#include "FXSurfaceRenderer.h"
#include "TextureLoader.h"
#include "ShadersLoader.h"

FXSurfaceRenderer::FXSurfaceRenderer(std::shared_ptr<BaseRenderer> renderer)
{
	this->_renderer = renderer;
	this->window = renderer->getWindow();
}
void FXSurfaceRenderer::init()
{
	if (!this->_renderer->initialised){
		this->_renderer->init();
	}
	// The framebuffer
	glGenFramebuffers(1, &fxSurfaceFrameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, fxSurfaceFrameBufferID);
	//Target texture
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	TextureLoader loader;
	fxSurfaceTextureID = loader.createTargetTexture(width, height);
	// The depth buffer
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	// Set "targerTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fxSurfaceTextureID, 0);

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
void FXSurfaceRenderer::update(){
	this->_renderer->update();
}

void FXSurfaceRenderer::render(Scene &scene)
{
	renderToFramebuffer(scene, fxSurfaceFrameBufferID, resolutionX, resolutionY);
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
	glBindTexture(GL_TEXTURE_2D, fxSurfaceTextureID);
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
	//this->_renderer->render(scene);
}
void FXSurfaceRenderer::renderToFramebuffer(Scene &scene, GLuint frameBufferID, unsigned int width, unsigned int height){
	int originalWidth, originalHeight;
	glfwGetWindowSize(window, &originalWidth, &originalHeight);
	// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	// set viewport (dependant on size of target framebuffer, passed in args)
	glViewport(0, 0, width, height);
	// render scene with using underlying renderer- but
	// to the framebuffer (instead of screen)
	_renderer->render(scene);
	// reset active framebuffer, restore viewport to original size
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, originalWidth, originalHeight);
}