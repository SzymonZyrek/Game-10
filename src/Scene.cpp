//
//  Scene.cpp
//  Game10
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "Scene.h"
#include "GameObjectIds.h"
#include <sstream>
#include "Errors.h"

Scene::Scene() {
    
}

void Scene::update(double dT)
{
    for (int i = 0; i < _aisCount; i++)
    {
		_ais[i].update(dT);
    }
    for (int i = 0; i < _inputsCount; i++)
    {
		_inputs[i].update(dT);
    }
    for (int i = 0; i < _bodiesCount; i++)
    {
		renderableUpdateCommands[i] = _bodies[i].update(dT);
    }
    for (int i = 0; i < _renderablesCount; i++)
    {
		_renderables[i].update(dT, renderableUpdateCommands[i]);
    }
	aiUpdateCommands.clear();
	physicsUpdateCommands.clear();
	inputUpdateCommands.clear();
	renderableUpdateCommands.clear();
}


unsigned int Scene::registerGameObject(GameObject* object)
{
    if (_gameObjectsCount >= MAX_GAME_OBJECTS){
        throw ErrorCodes::GAMEOBJECTS_OVERFLOW;
    }
	if (object->gameObjectId!=0) {
		throw ErrorCodes::REGISTERING_REGISTERED_OBJECT;
	}
	else{
		_gameObjects[_gameObjectsCount] = GameObjectIds();
		GameObjectIds &gameObject = _gameObjects[_gameObjectsCount];
		object->gameObjectId = gameObject.gameObjectId;
		// register all components
		if (object->hasAIComponent())
		{
			if (_aisCount >= MAX_GAME_OBJECTS){
				throw ErrorCodes::AI_OVERFLOW;
			}
			_ais[_aisCount].initWith(*object->getAIComponent());
			_ais[_aisCount].setGameObjectId(object->gameObjectId);
			gameObject.setAIComponent(_aisCount);
			_aisCount ++;
		}
		if (object->hasInputComponent())
		{
			if (_inputsCount >= MAX_GAME_OBJECTS){
				throw ErrorCodes::INPUTS_OVERFLOW;
			}
			_inputs[_inputsCount].initWith(*object->getInputComponent());
			_inputs[_inputsCount].setGameObjectId(object->gameObjectId);
			gameObject.setInputComponent(_inputsCount);
			_inputsCount ++;
		}
		if (object->hasPhysicalComponent())
		{
			if (_bodiesCount >= MAX_GAME_OBJECTS){
				throw ErrorCodes::BODIES_OVERFLOW;
			}
			_bodies[_bodiesCount].initWith(*object->getPhysicalComponent());
			_bodies[_bodiesCount].setGameObjectId(object->gameObjectId);
			gameObject.setPhysicalComponent(_bodiesCount);
			_bodiesCount ++;
		}
		if (object->hasRenderableComponent())
		{
			if (_renderablesCount >= MAX_GAME_OBJECTS){
				throw ErrorCodes::RENDERABLES_OVERFLOW;
			}
			_renderables[_renderablesCount].initWith(*object->getRenderableComponent());
			_renderables[_renderablesCount].setGameObjectId(object->gameObjectId);
			gameObject.setRenderableComponent(_renderablesCount);
			_renderablesCount ++;
		}
		gameObject.setActive(true);
		_gameObjectsCount++;
	}
	return object->gameObjectId;
}
unsigned int Scene::lookupIndexById(unsigned int id){
	int theId = -1;
	for (int i = 0; i < _gameObjectsCount; i++){
		if (_gameObjects[i].gameObjectId = id){
			theId = i;
		}
	}
	if (theId == -1){
		throw "No such object!";
	}
	return theId;
}
void Scene::destroyGameObjectWithId(unsigned long id)
{
	unsigned int theId = lookupIndexById(id);
	GameObjectIds &gameObject = _gameObjects[theId];
	if (gameObject.hasAIComponent()){
		destroyAIWithId(gameObject.getAIComponent());
	}
	if (gameObject.hasPhysicalComponent()){
		unsigned int bodyId = gameObject.getPhysicalComponent();
	}
	if (gameObject.hasRenderableComponent()){
		unsigned int renderableId = gameObject.getRenderableComponent();
		_renderables[renderableId].initWith(_renderables[_renderablesCount - 1]);
		
	}
	if (gameObject.hasInputComponent()){
		unsigned int inputId = gameObject.getInputComponent();
	}
	// If the object were destroying is not at the "end" of the vector,
	// swap it with the one at the end. This way we always have all active
	// objects in the front of the vector, in the positions 0:(_gameObjectsCount - 2)
	if (theId != (_gameObjectsCount - 1)){
		_gameObjects[theId].initWith(_gameObjects[_gameObjectsCount - 1]);
	}
	_gameObjects[_gameObjectsCount - 1].clear();
	_renderablesCount--;


	

}
void Scene::destroyRenderableWithId(unsigned long theId)
{
	if (theId != (_renderablesCount - 1)){
		_renderables[theId].initWith(_renderables[_renderablesCount - 1]);
	}
	_renderables[_renderablesCount - 1].setActive(false);
	_renderablesCount--;
}
void Scene::destroyAIWithId(unsigned long theId)
{
	if (theId != (_aisCount - 1)){
		_ais[theId].initWith(_ais[_aisCount - 1]);
	}
	_renderables[_renderablesCount - 1].setActive(false);
	_aisCount--;
}
void Scene::destroyInputWithId(unsigned long theId)
{
	if (theId != (_inputsCount - 1)){
		_inputs[theId].initWith(_inputs[_inputsCount - 1]);
	}
	_renderables[_renderablesCount - 1].setActive(false);
	_inputsCount--;
}
void Scene::destroyBodyWithId(unsigned long theId)
{
	if (theId != (_bodiesCount - 1)){
		_bodies[theId].initWith(_bodies[_bodiesCount - 1]);
	}
	_renderables[_renderablesCount - 1].setActive(false);
	_bodiesCount--;
}