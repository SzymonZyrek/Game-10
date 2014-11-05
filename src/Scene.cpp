//
//  Scene.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "Scene.h"

Scene::Scene() {
    
}

void Scene::update(double dT)
{
    for (int i = 0; i < _aisCount; i++)
    {
        AIComponent &tais = _ais[i];
        if (_gameObjects[tais.getDaddyId()].isActive()){
            _ais[i].update(dT);
        }else{
            break;
        }
    }
    for (int i = 0; i < _inputsCount; i++)
    {
        InputComponent &ti = _inputs[i];
        if (_gameObjects[ti.getDaddyId()].isActive()){
            _ais[i].update(dT);
        }else{
            break;
        }
    }
    for (int i = 0; i < _aisCount; i++)
    {
        AIComponent &tais = _ais[i];
        if (_gameObjects[tais.getDaddyId()].isActive()){
            _ais[i].update(dT);
        }else{
            break;
        }
    }
    for (int i = 0; i < _aisCount; i++)
    {
        AIComponent &tais = _ais[i];
        if (_gameObjects[tais.getDaddyId()].isActive()){
            _ais[i].update(dT);
        }else{
            break;
        }
    }
}

void Scene::registerGameObject(GameObject* object)
{
    if (_gameObjectsCount >= MAX_GAME_OBJECTS){
        throw "TOO MANY OBJECTS!";
    }
    // register all components
    int daddyId = _gameObjectsCount;
    if (object->hasAIComponent())
    {
        if (_aisCount >= MAX_GAME_OBJECTS){
            throw "TOO MANY AIs!";
        }
        _ais[_aisCount].initWith(*object->getAIComponent());
        _ais[_aisCount].setDaddyId(daddyId);
        _gameObjects[_gameObjectsCount].setAIComponent(_aisCount);
        _aisCount ++;
    }
    if (object->hasInputComponent())
    {
        if (_inputsCount >= MAX_GAME_OBJECTS){
            throw "TOO MANY inputs!";
        }
        _inputs[_inputsCount].initWith(*object->getInputComponent());
        _inputs[_inputsCount].setDaddyId(daddyId);
        _gameObjects[_gameObjectsCount].setInputComponent(_inputsCount);
        _inputsCount ++;
    }
    if (object->hasPhysicalComponent())
    {
        if (_bodiesCount >= MAX_GAME_OBJECTS){
            throw "TOO MANY bodies!";
        }
        _bodies[_bodiesCount].initWith(*object->getPhysicalComponent());
        _bodies[_bodiesCount].setDaddyId(daddyId);
        _gameObjects[_gameObjectsCount].setPhysicalComponent(_bodiesCount);
        _bodiesCount ++;
    }
    if (object->hasRenderableComponent())
    {
        if (_renderablesCount >= MAX_GAME_OBJECTS){
            throw "TOO MANY renderables!";
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