//
//  GameObjectIds.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "GameObjectIds.h"
GameObjectIds::GameObjectIds() : _renderableIndex(-1), _bodyIndex(-1), _inputIndex(-1), _aiIndex(-1), _active(false)
{
}
void GameObjectIds::setRenderableComponent(int index){
    this->_renderableIndex = index;
}
void GameObjectIds::setPhysicalComponent(int index){
    this->_bodyIndex = index;
}
void GameObjectIds::setInputComponent(int index){
	this->_inputIndex = index;
}
void GameObjectIds::setAIComponent(int index){
	this->_aiIndex = index;
}
void GameObjectIds::addSpecialComponent(int index){
	this->_specialComponentIndices.push_back(index);
}

bool GameObjectIds::hasRenderableComponent(){
	return (_renderableIndex != -1);
}
bool GameObjectIds::hasPhysicalComponent(){
	return (_bodyIndex != -1);
}
bool GameObjectIds::hasInputComponent(){
	return (_inputIndex != -1);
}
bool GameObjectIds::hasAIComponent(){
	return (_aiIndex != -1);
}
bool GameObjectIds::hasSpecialComponents(){
	return (_specialComponentIndices.size() > 0);
}
bool GameObjectIds::isActive()
{
	return _active;
}
void GameObjectIds::setActive(bool value)
{
	this->_active = value;
}
