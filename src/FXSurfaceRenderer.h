#pragma once
#include <stdio.h>
#include "BaseRenderer.h"
#include "ModelLoader.h"
#include <memory>
#include "Camera.h"
#include "RenderableComponent.h"
#include "Scene.h"

class FXSurfaceRenderer : public BaseRenderer
{
public:
	FXSurfaceRenderer(std::shared_ptr<BaseRenderer> renderer);
	virtual void init();
	virtual void render(Scene &scene);
	virtual void update();
	void renderToFramebuffer(Scene &scene, GLuint frameBufferID, unsigned int width, unsigned int height);
private:
	std::shared_ptr<BaseRenderer> _renderer;
	GLuint fxSurfaceFrameBufferID = 0;
	GLuint fxSurfaceTextureID = 0;
};