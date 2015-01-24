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

void GameObjectIds::initWith(GameObjectIds &other){
	this->_renderableIndex = other._renderableIndex;
	this->_bodyIndex = other._bodyIndex;
	this->_inputIndex = other._inputIndex;
	this->_aiIndex = other._aiIndex;
	this->_specialComponentIndices = other._specialComponentIndices;
	this->_active = other._active;
}
void GameObjectIds::clear(){
	this->_renderableIndex = -1;
	this->_bodyIndex = -1;
	this->_inputIndex = -1;
	this->_aiIndex = -1;
	this->_specialComponentIndices.clear();
	this->_active = false;
}
void GameObjectIds::setRenderableComponent(unsigned int index){
    this->_renderableIndex = index;
}
void GameObjectIds::setPhysicalComponent(unsigned int index){
    this->_bodyIndex = index;
}
void GameObjectIds::setInputComponent(unsigned int index){
	this->_inputIndex = index;
}
void GameObjectIds::setAIComponent(unsigned index){
	this->_aiIndex = index;
}
void GameObjectIds::addSpecialComponent(unsigned int index){
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

unsigned int GameObjectIds::getRenderableComponent(){
	return this->_renderableIndex;
}
unsigned int GameObjectIds::getPhysicalComponent(){
	return this->_bodyIndex;
}
unsigned int GameObjectIds::getInputComponent(){
	return this->_inputIndex;
}
unsigned int GameObjectIds::getAIComponent(){
	return this->_aiIndex;
}