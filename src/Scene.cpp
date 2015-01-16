//
//  Scene.cpp
//  OpenGLTutorial
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
        _bodies[i].update(dT);
    }
    for (int i = 0; i < _renderablesCount; i++)
    {
        _renderables[i].update(dT);
    }
}

unsigned int Scene::registerGameObject(GameObject* object)
{
    if (_gameObjectsCount >= MAX_GAME_OBJECTS){
        throw ErrorCodes::GAMEOBJECTS_OVERFLOW;
    }
	if (object->id != nullptr) {
		throw ErrorCodes::REGISTERING_REGISTERED_OBJECT;
	}
	else{
		object->id = &_gameObjects[_gameObjectsCount];
	}
    // register all components
    int daddyId = _gameObjectsCount;
    if (object->hasAIComponent())
    {
        if (_aisCount >= MAX_GAME_OBJECTS){
            throw ErrorCodes::AI_OVERFLOW;
        }
        _ais[_aisCount].initWith(*object->getAIComponent());
        _ais[_aisCount].setDaddyId(daddyId);
        _gameObjects[_gameObjectsCount].setAIComponent(_aisCount);
        _aisCount ++;
    }
    if (object->hasInputComponent())
    {
        if (_inputsCount >= MAX_GAME_OBJECTS){
            throw ErrorCodes::INPUTS_OVERFLOW;
        }
        _inputs[_inputsCount].initWith(*object->getInputComponent());
        _inputs[_inputsCount].setDaddyId(daddyId);
        _gameObjects[_gameObjectsCount].setInputComponent(_inputsCount);
        _inputsCount ++;
    }
    if (object->hasPhysicalComponent())
    {
        if (_bodiesCount >= MAX_GAME_OBJECTS){
            throw ErrorCodes::BODIES_OVERFLOW;
        }
        _bodies[_bodiesCount].initWith(*object->getPhysicalComponent());
        _bodies[_bodiesCount].setDaddyId(daddyId);
        _gameObjects[_gameObjectsCount].setPhysicalComponent(_bodiesCount);
        _bodiesCount ++;
    }
    if (object->hasRenderableComponent())
    {
        if (_renderablesCount >= MAX_GAME_OBJECTS){
			throw ErrorCodes::RENDERABLES_OVERFLOW;
        }
        _renderables[_renderablesCount].initWith(*object->getRenderableComponent());
        _renderables[_renderablesCount].setDaddyId(daddyId);
        _gameObjects[_gameObjectsCount].setRenderableComponent(_renderablesCount);
        _renderablesCount ++;
    }
    _gameObjects[_gameObjectsCount].setActive(true);
    _gameObjectsCount++;
	return _gameObjectsCount - 1;
}
void Scene::destroyGameObjectWithId(unsigned long theId)
{
	destroyAIWithId(_gameObjects[theId].getAIComponent());
	destroyBodyWithId(_gameObjects[theId].getPhysicalComponent());
	destroyRenderableWithId(_gameObjects[theId].getRenderableComponent());
	destroyInputWithId(_gameObjects[theId].getInputComponent());

	if (theId != (_gameObjectsCount - 1)){
		_gameObjects[theId].initWith(_gameObjects[_gameObjectsCount - 1]);
	}
	_gameObjects[_gameObjectsCount - 1].setActive(false);
	_renderablesCount--;
}
void Scene::destroyRenderableWithId(unsigned long theId)
{
	if (theId != (_renderablesCount - 1)){
		_renderables[theId].initWith(_renderables[_renderablesCount - 1]);
		_gameObjects[_renderables[theId].getDaddyId()].setRenderableComponent(theId);
	}
	_renderables[_renderablesCount - 1].setActive(false);
	_renderablesCount--;
}
void Scene::destroyAIWithId(unsigned long theId)
{
	if (theId != (_aisCount - 1)){
		_ais[theId].initWith(_ais[_aisCount - 1]);
		_gameObjects[_ais[theId].getDaddyId()].setAIComponent(theId);
	}
	_renderables[_renderablesCount - 1].setActive(false);
	_aisCount--;
}
void Scene::destroyInputWithId(unsigned long theId)
{
	if (theId != (_inputsCount - 1)){
		_inputs[theId].initWith(_inputs[_inputsCount - 1]);
		_gameObjects[_inputs[theId].getDaddyId()].setInputComponent(theId);
	}
	_renderables[_renderablesCount - 1].setActive(false);
	_inputsCount--;
}
void Scene::destroyBodyWithId(unsigned long theId)
{
	if (theId != (_bodiesCount - 1)){
		_bodies[theId].initWith(_bodies[_bodiesCount - 1]);
		_gameObjects[_bodies[theId].getDaddyId()].setPhysicalComponent(theId);
	}
	_renderables[_renderablesCount - 1].setActive(false);
	_bodiesCount--;
}