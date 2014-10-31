//
//  Scene.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__Scene__
#define __OpenGLTutorial__Scene__
#define MAX_GAME_OBJECTS 20

#include <vector>
#include "GameObject.h"
#include "GameObjectIds.h"
#include "RenderableComponent.h"
#include "PhysicalComponent.h"
#include "InputComponent.h"
#include "AIComponent.h"

class Component;

class Scene {
public:
    Scene();
    void update(double dT);
    void registerGameObject(GameObject* object);
    void destroyGameObjectWithId(unsigned long theId);
private:
    GameObjectIds _gameObjects[MAX_GAME_OBJECTS];
    int _gameObjectsCount = 0;
    RenderableComponent _renderables[MAX_GAME_OBJECTS];
    int _renderablesCount = 0;
    PhysicalComponent _bodies[MAX_GAME_OBJECTS];
    int _bodiesCount = 0;
    InputComponent _inputs[MAX_GAME_OBJECTS];
    int _inputsCount = 0;
    AIComponent _ais[MAX_GAME_OBJECTS];
    int _aisCount = 0;
    std::vector<Component*> customComponents;
};

#endif /* defined(__OpenGLTutorial__Scene__) */
