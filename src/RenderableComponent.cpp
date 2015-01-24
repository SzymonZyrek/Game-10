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

RenderableComponent::RenderableComponent() :Component() {}
void RenderableComponent::refreshFromRenderable(){
	this->renderable = renderable;
	this->indexBufferId = renderable->indexBufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->normalbufferID = renderable->normalbufferID;
	this->uvBufferID = renderable->uvBufferID;
	this->textureBufferID = renderable->textureBufferID;
	this->programID = renderable->programID;
	this->vertexCount = renderable->vertexCount;
	this->indexCount = renderable->indexCount;
}
void RenderableComponent::initRenderable(){
	if (!renderable->modelLoaded){
		ModelLoader loader(renderable->modelName);
		loader.loadObjFile(*renderable);
		if (!renderable->modelLoaded) {
			std::stringstream ss;
			ss << "Cant load model" << renderable->modelName;
			Log::error(ss.str());
			return;
		}
	}
	if (!renderable->textureLoaded){
		TextureLoader textureLoader(renderable->textureName);
		textureLoader.loadTexture(*renderable);
		if (!renderable->textureLoaded) {
			std::stringstream ss;
			ss << "Cant load texture" << renderable->textureName;
			Log::error(ss.str());
			return;
		}
	}
	if (!renderable->shadersLoaded){
		ShadersLoader shadersLoader;
		shadersLoader.loadFragmentShader(renderable->fragmentShaderName);
		shadersLoader.loadVertexShader(renderable->vertexShaderName);
		shadersLoader.loadShaderProgram(*renderable);
		if (!renderable->shadersLoaded){
			std::stringstream ss;
			ss << "Cant load shaders" << renderable->fragmentShaderName << ", " << renderable->vertexShaderName;
			Log::error(ss.str());
			return;
		}
	}
	if (!renderable->modelInitialized){
		RenderDataLoader renderDataLoader;
		renderDataLoader.loadIndexedData(*renderable);
	}
}

RenderableComponent::RenderableComponent(std::string modelName, std::string textureName) : Component(){
	this->renderable = std::make_shared<Renderable>(modelName, textureName, Config::getStringProperty(DEFAULT_VERTEX_SHADER_FILE_NAME), Config::getStringProperty(DEFAULT_FRAGMENT_SHADER_FILE_NAME));
	initRenderable();
	refreshFromRenderable();
	this->_isNullComponent = false;
	Log::debug("RenderableComponent(std::string modelName, std::string textureName)\n", DebugKey::OBJECT_CREATION);
}

RenderableComponent::RenderableComponent(std::shared_ptr <Renderable> renderable) : Component()
{
	this->renderable = renderable;
	initRenderable();
	refreshFromRenderable();
	this->_isNullComponent = false;
	Log::debug("RenderableComponent(std::shared_ptr <Renderable> renderable)\n", DebugKey::OBJECT_CREATION);
}


RenderableComponent::RenderableComponent(RenderableComponent& other) : Component()
{
	initWith(other);
	Log::debug("RenderableComponent(RenderableComponent& other)\n", DebugKey::OBJECT_CREATION);
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
	initRenderable();
	refreshFromRenderable();
	this->_isNullComponent = false;
}

void RenderableComponent::setRenderable(std::shared_ptr <Renderable> renderable){
	this->renderable = renderable;
	initRenderable();
	refreshFromRenderable();
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