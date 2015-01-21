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
#include "TextureLoader.h"
#include "RenderDataLoader.h"

RenderableComponent::RenderableComponent() : Component() {

}

RenderableComponent::RenderableComponent(std::string modelName, std::string textureName){
	this->renderable = std::make_shared<Renderable>(modelName, textureName);
	if (!renderable->modelLoaded){
		ModelLoader loader(renderable->modelName);
		loader.loadObjFile(*renderable);
		if (!renderable->modelLoaded) throw "Shit, can't load this :(";
		}
	if (!renderable->modelInitialized){
		TextureLoader textureLoader(renderable->textureName);
		textureLoader.loadTexture(*renderable);
		RenderDataLoader renderDataLoader;
		renderDataLoader.loadIndexedData(*renderable);
	}
	this->renderable = renderable;
	this->normalbufferID = renderable->normalbufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->textureBufferID = renderable->textureBufferID;
	this->uvBufferID = renderable->uvBufferID;
	this->vertexCount = renderable->vertexCount;
	this->indexBufferId = renderable->indexBufferID;
	this->indexCount = renderable->indexCount;
	this->_isNullComponent = false;
}

RenderableComponent::RenderableComponent(std::shared_ptr <Renderable> renderable)
{
	if (!renderable->modelLoaded){
		ModelLoader loader(renderable->modelName);
		loader.loadObjFile(*renderable);
		if (!renderable->modelLoaded) throw "Shit, can't load this :(";
	}
	if (!renderable->modelInitialized){
		TextureLoader textureLoader(renderable->textureName);
		textureLoader.loadTexture(*renderable);
		RenderDataLoader renderDataLoader;
		renderDataLoader.loadIndexedData(*renderable);
	}
	this->renderable = renderable;
	this->normalbufferID = renderable->normalbufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->textureBufferID = renderable->textureBufferID;
	this->uvBufferID = renderable->uvBufferID;
	this->indexBufferId = renderable->indexBufferID;
	this->indexCount = renderable->indexCount;
	this->vertexCount = renderable->vertexCount;
	this->_isNullComponent = false;
	Log::debug("RenderableComponent default contructor\n", DebugKey::OBJECT_CREATION);
}


void RenderableComponent::setRenderable(std::shared_ptr <Renderable> renderable){
	if (!renderable->modelLoaded){
		ModelLoader loader(renderable->modelName);
		loader.loadObjFile(*renderable);
		if (!renderable->modelLoaded) throw "Shit, can't load this :(";
	}
	if (!renderable->modelInitialized){
		TextureLoader textureLoader(renderable->textureName);
		textureLoader.loadTexture(*renderable);
		RenderDataLoader renderDataLoader;
		renderDataLoader.loadIndexedData(*renderable);
	}
	this->normalbufferID = renderable->normalbufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->uvBufferID = renderable->uvBufferID;
	this->vertexCount = renderable->vertexCount;
	this->indexBufferId = renderable->indexBufferID;
	this->indexCount = renderable->indexCount;
	this->textureBufferID = renderable->textureBufferID;
	this->_isNullComponent = false;
}

RenderableComponent::RenderableComponent(RenderableComponent& other)
{
	Log::debug("RenderableComponent copy contructor\n", DebugKey::OBJECT_CREATION);
	initWith(other);
}

void RenderableComponent::initWith(RenderableComponent &component)
{
	this->gameObjectId = component.gameObjectId;
	this->_active = component._active;
	this->_isNullComponent = component._isNullComponent;

	this->position = component.position;
	this->rotation = component.rotation;
	this->scale = component.scale;
	
	if (_isNullComponent){
		return;
	}

	this->renderable = component.renderable;
	if (!renderable->modelLoaded){
		ModelLoader loader(renderable->modelName);
		loader.loadObjFile(*renderable);
		if (!renderable->modelLoaded) throw "Shit, can't load this :(";
	}
	if (!renderable->modelInitialized){
		TextureLoader textureLoader(renderable->textureName);
		textureLoader.loadTexture(*renderable);
		RenderDataLoader renderDataLoader;
		renderDataLoader.loadIndexedData(*renderable);
	}
	this->normalbufferID = renderable->normalbufferID;
	this->uvBufferID = renderable->uvBufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->indexBufferId = renderable->indexBufferID;
	this->indexCount = renderable->indexCount;
	this->textureBufferID = renderable->textureBufferID;
	this->vertexCount = renderable->vertexCount;
	this->_isNullComponent = false;
}

void RenderableComponent::update(double dT, std::vector<RenderableUpdateCommand> &commands)
{
	for (RenderableUpdateCommand& cmd : commands) {
		if (cmd.getType()==RenderableCommandEnum::TEST_ROTATE) {
			this->rotation.y += 0.01;
		}
	}
	if (_isNullComponent){
		return;
	}
	this->render();
}



void RenderableComponent::render()
{
	std::stringstream ss;
	ss << "rendering" << this->gameObjectId << std::endl;
	Log::periodic(ss.str(), this->_logPeriodicKey);
}