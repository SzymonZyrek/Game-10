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
#include "ShadersLoader.h"
#include "Config.h"

RenderableComponent::RenderableComponent() : Component() {

}

RenderableComponent::RenderableComponent(std::string modelName, std::string textureName){
	this->renderable = std::make_shared<Renderable>(modelName, textureName);
	if (!renderable->modelLoaded){
		ModelLoader loader(renderable->modelName);
		loader.loadObjFile(*renderable);
		if (!renderable->modelLoaded) throw "Shit, can't load this :(";
	}
	if (!renderable->textureLoaded){
		TextureLoader textureLoader(renderable->textureName);
		textureLoader.loadTexture(*renderable);
	}
	if (!renderable->modelInitialized){
		RenderDataLoader renderDataLoader;
		renderDataLoader.loadIndexedData(*renderable);
	}
	if (!renderable->shadersLoaded){
		ShadersLoader shadersLoader;
		shadersLoader.loadFragmentShader(Config::getStringProperty(DEFAULT_FRAGMENT_SHADER_FILE_NAME));
		shadersLoader.loadVertexShader(Config::getStringProperty(DEFAULT_VERTEX_SHADER_FILE_NAME));
		shadersLoader.loadShaderProgram(*renderable);
	}
	this->renderable = renderable;
	this->indexBufferId = renderable->indexBufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->normalbufferID = renderable->normalbufferID;
	this->uvBufferID = renderable->uvBufferID;
	this->textureBufferID = renderable->textureBufferID;
	this->programID = renderable->programID;
	this->vertexCount = renderable->vertexCount;
	this->indexCount = renderable->indexCount;
	this->_isNullComponent = false;
}

RenderableComponent::RenderableComponent(std::shared_ptr <Renderable> renderable)
{
	this->renderable = renderable;
	if (!renderable->modelLoaded){
		ModelLoader loader(renderable->modelName);
		loader.loadObjFile(*renderable);
		if (!renderable->modelLoaded) throw "Shit, can't load this :(";
	}
	if (!renderable->textureLoaded){
		TextureLoader textureLoader(renderable->textureName);
		textureLoader.loadTexture(*renderable);
	}
	if (!renderable->modelInitialized){
		RenderDataLoader renderDataLoader;
		renderDataLoader.loadIndexedData(*renderable);
	}
	if (!renderable->shadersLoaded){
		ShadersLoader shadersLoader;
		shadersLoader.loadFragmentShader(Config::getStringProperty(DEFAULT_FRAGMENT_SHADER_FILE_NAME));
		shadersLoader.loadVertexShader(Config::getStringProperty(DEFAULT_VERTEX_SHADER_FILE_NAME));
		shadersLoader.loadShaderProgram(*renderable);
	}
	this->renderable = renderable;
	this->indexBufferId = renderable->indexBufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->normalbufferID = renderable->normalbufferID;
	this->uvBufferID = renderable->uvBufferID;
	this->textureBufferID = renderable->textureBufferID;
	this->programID = renderable->programID;
	this->vertexCount = renderable->vertexCount;
	this->indexCount = renderable->indexCount;
	this->_isNullComponent = false;
	Log::debug("RenderableComponent default contructor\n", DebugKey::OBJECT_CREATION);
}


void RenderableComponent::setRenderable(std::shared_ptr <Renderable> renderable){
	this->renderable = renderable;
	if (!renderable->modelLoaded){
		ModelLoader loader(renderable->modelName);
		loader.loadObjFile(*renderable);
		if (!renderable->modelLoaded) throw "Shit, can't load this :(";
	}
	if (!renderable->textureLoaded){
		TextureLoader textureLoader(renderable->textureName);
		textureLoader.loadTexture(*renderable);
	}
	if (!renderable->modelInitialized){
		RenderDataLoader renderDataLoader;
		renderDataLoader.loadIndexedData(*renderable);
	}
	if (!renderable->shadersLoaded){
		ShadersLoader shadersLoader;
		shadersLoader.loadFragmentShader(Config::getStringProperty(DEFAULT_FRAGMENT_SHADER_FILE_NAME));
		shadersLoader.loadVertexShader(Config::getStringProperty(DEFAULT_VERTEX_SHADER_FILE_NAME));
		shadersLoader.loadShaderProgram(*renderable);
	}
	this->renderable = renderable;
	this->indexBufferId = renderable->indexBufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->normalbufferID = renderable->normalbufferID;
	this->uvBufferID = renderable->uvBufferID;
	this->textureBufferID = renderable->textureBufferID;
	this->programID = renderable->programID;
	this->vertexCount = renderable->vertexCount;
	this->indexCount = renderable->indexCount;
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
	if (!renderable->textureLoaded){
		TextureLoader textureLoader(renderable->textureName);
		textureLoader.loadTexture(*renderable);
	}
	if (!renderable->modelInitialized){
		RenderDataLoader renderDataLoader;
		renderDataLoader.loadIndexedData(*renderable);
	}
	if (!renderable->shadersLoaded){
		ShadersLoader shadersLoader;
		shadersLoader.loadFragmentShader(Config::getStringProperty(DEFAULT_FRAGMENT_SHADER_FILE_NAME));
		shadersLoader.loadVertexShader(Config::getStringProperty(DEFAULT_VERTEX_SHADER_FILE_NAME));
		shadersLoader.loadShaderProgram(*renderable);
	}
	this->renderable = renderable;
	this->indexBufferId = renderable->indexBufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->normalbufferID = renderable->normalbufferID;
	this->uvBufferID = renderable->uvBufferID;
	this->textureBufferID = renderable->textureBufferID;
	this->programID = renderable->programID;
	this->vertexCount = renderable->vertexCount;
	this->indexCount = renderable->indexCount;
	this->_isNullComponent = false;
}

void RenderableComponent::update(double dT, std::vector<RenderableUpdateCommand> &commands)
{
	if (_isNullComponent){
		return;
	}
	for (RenderableUpdateCommand& cmd : commands) {
		if (cmd.getType()==RenderableCommandEnum::TEST_ROTATE) {
			this->rotation.y += 0.01;
		}
	}
}