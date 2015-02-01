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

std::shared_ptr<Renderable> RenderableComponent::getRenderable() {
	return this->renderable;
}

void RenderableComponent::refreshFromRenderable(){
	this->indexBufferId = renderable->indexBufferID;
	this->vertexBufferID = renderable->vertexBufferID;
	this->normalbufferID = renderable->normalbufferID;
	this->uvBufferID = renderable->uvBufferID;
	this->textureBufferID = renderable->textureBufferID;
	this->normalMapID = renderable->normalMapID;
	this->materialBufferID = renderable->materialBufferID;
	this->programID = renderable->programID;
	this->vertexCount = renderable->vertexCount;
	this->indexCount = renderable->indexCount;
	this->indexed = renderable->indexed;
	this->tangentBufferID = renderable->tangentBufferID;
	this->bitangentBufferID = renderable->bitangentBufferID;
}
void RenderableComponent::initRenderable(){
	if (!renderable->modelLoaded){
		// try to load binary file first
		// (much fastaah)
		ModelLoader loader;
		try {
			loader.loadBinary(renderable->modelName, *renderable);
		}
		catch (std::string err){
			std::stringstream warn;
			warn << "Could not load .bin file for " << renderable->modelName << ", reason: " << err << ", reading .obj file instead";
			Log::warning(warn.str());
			try {
				loader.loadObjFile(renderable->modelName, *renderable);
				if (renderable->indexed){
					renderable->index();
					this->indexed = true;
				}
				ModelLoader loader;
				loader.saveAsBinary(renderable->modelName, *renderable);
			}
			catch (std::string err2){
				std::stringstream error;
				error << "Could not load .obj file for " << renderable->modelName << ", reason: " << err2 << ", reading default file instead";
				Log::error(error.str());
				try {
					loader.loadObjFile(Config::getStringProperty(DEFAULT_MODEL_FILE_NAME), *renderable);
				}
				catch (std::string err3){
					Logger::error("FATAL: could not load default model file! Check your configuration.");
				}
			}
		}
		if (!renderable->modelLoaded) {
			std::stringstream ss;
			ss << "Cant load model" << renderable->modelName;
			Log::error(ss.str());
			return;
		}
	}
	if (!renderable->textureLoaded){
		TextureLoader textureLoader;
		if (renderable->materialMap.size()<1){
			// if no material names were loaded from file,
			// use default texture
			renderable->materialMap[Config::getStringProperty(DEFAULT_TEXTURE_FILE_NAME)] = 0;
		}
		textureLoader.loadTextures(*renderable);
		if (!renderable->textureLoaded) {
			std::stringstream ss;
			ss << "Cant load textures for " << renderable->modelName;
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
		if (renderable->indexed){
			

			renderDataLoader.loadIndexedData(*renderable);
		}
		else{
			renderDataLoader.loadPlainData(*renderable);
		}
	}
}

RenderableComponent::RenderableComponent(std::string modelName, bool indexed) : Component(){
	indexed = indexed;
	this->renderable = std::make_shared<Renderable>(modelName, Config::getStringProperty(DEFAULT_VERTEX_SHADER_FILE_NAME), Config::getStringProperty(DEFAULT_FRAGMENT_SHADER_FILE_NAME), indexed);
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

std::ostream& operator<<(std::ostream &strm, RenderableComponent &a) {
	std::stringstream texturenames;
	for (auto pair : a.getRenderable()->materialMap){
		texturenames << pair.first << ', ';
	}
	return strm
		<< "RenderableComponent:[" << std::endl
		<< "\tgameObjectId: " << a.getGameObjectId() << std::endl
		<< "\tmodelName: " << a.getRenderable()->modelName << std::endl
		<< "\ttextureNames: " << texturenames.str() << std::endl
		<< "\tvertexShaderName: " << a.getRenderable()->vertexShaderName << std::endl
		<< "\tfragmentShaderName: " << a.getRenderable()->fragmentShaderName << std::endl
		<< "\tmodelLoaded: " << (a.getRenderable()->modelLoaded ? "true" : "false") << std::endl
		<< "\ttextureLoaded: " << (a.getRenderable()->textureLoaded ? "true" : "false") << std::endl
		<< "\tshadersLoaded: " << (a.getRenderable()->shadersLoaded ? "true" : "false") << std::endl
		<< "\tmodelInitialized: " << (a.getRenderable()->modelInitialized ? "true" : "false") << std::endl
		<< "\tindexed: " << (a.indexed ? "true" : "false") << std::endl
		<< "\tvertices: " << a.vertexCount << std::endl
		<< "\tindices: " << a.indexCount << std::endl
		<< "]" << std::endl;
}