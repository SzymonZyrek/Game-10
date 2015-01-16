//
//  RenderableComponent.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "RenderableComponent.h"
#include "GameObjectIds.h"
#include "CPPLogger.h"
#include <sstream>
#include "ModelLoader.h"
RenderableComponent::RenderableComponent(){
	this->_isNullComponent = true;
}
RenderableComponent::RenderableComponent(std::shared_ptr <Renderable> renderable)
{
	if (!renderable->modelInitialized){
		ModelLoader loader("globe.obj");
		loader.loadObjFile(*renderable);
		if (!renderable->modelInitialized) throw "Shit, can't load this :(";
	}
	if (!renderable->modelLoaded){
		
	}
	this->normalbufferID = renderable->normalbufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->uvBufferID = renderable->normalbufferID;
	this->textureDataID = renderable->textureDataID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->renderable = renderable;
	Log::debug("RenderableComponent default contructor\n", DebugKey::OBJECT_CREATION);
}

RenderableComponent::operator bool() const
{
	return !this->_isNullComponent;
}

void RenderableComponent::setRenderable(std::shared_ptr <Renderable> renderable){
	if (!renderable->modelInitialized){
		ModelLoader loader("globe.obj");
		loader.loadObjFile(*renderable);
	}
	if (!renderable->modelLoaded){

	}
	this->normalbufferID = renderable->normalbufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->uvBufferID = renderable->normalbufferID;
	this->textureDataID = renderable->textureDataID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->_isNullComponent = false;
}

RenderableComponent::RenderableComponent(RenderableComponent& other)
{
	Log::debug("RenderableComponent copy contructor\n", DebugKey::OBJECT_CREATION);
	initWith(other);
}

void RenderableComponent::initWith(RenderableComponent &component)
{
	this->_daddyId = component.getDaddyId();
	this->_active = component._active;
	this->_isNullComponent = component._isNullComponent;

	this->position = component.position;
	this->rotation = component.rotation;
	this->scale = component.scale;

	this->renderable = component.renderable;
	if (!renderable->modelInitialized){
		ModelLoader loader("globe.obj");
		loader.loadObjFile(*renderable);
	}
	if (!renderable->modelLoaded){

	}
	this->normalbufferID = component.normalbufferID;
	this->vertexBufferID = component.vertexBufferID;
	this->uvBufferID = component.normalbufferID;
	this->textureBufferID = component.textureBufferID;
	this->textureDataID = component.textureDataID;
}

void RenderableComponent::update(double dT)
{
	this->render();
}
void RenderableComponent::render()
{
	std::stringstream ss;
	ss << "rendering" << this->_daddyId << std::endl;
	Log::periodic(ss.str(), this->_logPeriodicKey);
}