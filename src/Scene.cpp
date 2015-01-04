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
        AIComponent &tais = _ais[i];
        if (_gameObjects[tais.getDaddyId()].isActive()){
            _ais[i].update(dT);
        }
    }
    for (int i = 0; i < _inputsCount; i++)
    {
        InputComponent &ti = _inputs[i];
        if (_gameObjects[ti.getDaddyId()].isActive()){
			_inputs[i].update(dT);
        }
    }
    for (int i = 0; i < _bodiesCount; i++)
    {
        PhysicalComponent &body = _bodies[i];
		if (_gameObjects[body.getDaddyId()].isActive()){
            _bodies[i].update(dT);
        }
    }
    for (int i = 0; i < _renderablesCount; i++)
    {
        RenderableComponent &renderable = _renderables[i];
        if (_gameObjects[renderable.getDaddyId()].isActive()){
            _renderables[i].update(dT);
        }
    }
}

void Scene::registerGameObject(GameObject* object)
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
    
}
void Scene::destroyGameObjectWithId(unsigned long theId)
{
    
}