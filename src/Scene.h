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
#include <map>
#include "GameObject.h"
#include "GameObjectIds.h"
#include "RenderableComponent.h"
#include "PhysicalComponent.h"
#include "InputComponent.h"
#include "AIComponent.h"
#include "AIUpdateCommand.h"
#include "PhysicsUpdateCommand.h"
#include "InputUpdateCommand.h"
#include "RenderableUpdateCommand.h"

class Component;

class Scene {
public:
    Scene();
    void update(double dT);
	unsigned int registerGameObject(GameObject* object);
    void destroyGameObjectWithId(unsigned long theId);
    GameObjectIds _gameObjects[MAX_GAME_OBJECTS];
    unsigned int _gameObjectsCount = 0;
    RenderableComponent _renderables[MAX_GAME_OBJECTS];
	unsigned int _renderablesCount = 0;
	void destroyRenderableWithId(unsigned long theId);
	PhysicalComponent _bodies[MAX_GAME_OBJECTS];
	unsigned int _bodiesCount = 0;
	void destroyBodyWithId(unsigned long theId);
    InputComponent _inputs[MAX_GAME_OBJECTS];
	unsigned int _inputsCount = 0;
	void destroyInputWithId(unsigned long theId);
    AIComponent _ais[MAX_GAME_OBJECTS];
	unsigned int _aisCount = 0;
	void destroyAIWithId(unsigned long theId);
    std::vector<Component*> customComponents;
	std::map<unsigned int, std::vector<AIUpdateCommand>> aiUpdateCommands;
	std::map<unsigned int, std::vector<InputUpdateCommand>> inputUpdateCommands;
	std::map<unsigned int, std::vector<PhysicsUpdateCommand>> physicsUpdateCommands;
	std::map<unsigned int, std::vector<RenderableUpdateCommand>> renderableUpdateCommands;
private:
};

#endif /* defined(__OpenGLTutorial__Scene__) */
