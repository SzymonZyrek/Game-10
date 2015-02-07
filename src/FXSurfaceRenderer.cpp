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
}
void FXSurfaceRenderer::update(){
	this->_renderer->update();
}

void FXSurfaceRenderer::render(Scene &scene)
{
	this->_renderer->render(scene);
}