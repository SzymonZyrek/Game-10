#include "GameObjectCommand.h"

GameObjectCommand::GameObjectCommand(unsigned int gameObjectId, GameObjectCommandEnum type) : ComponentUpdateCommand(gameObjectId){
	this->_type = type;
}
GameObjectCommand::GameObjectCommand(unsigned int gameObjectId, GameObjectCommandEnum  type, unsigned int value) : ComponentUpdateCommand(gameObjectId){
	this->_type = type;
	this->_value = value;
}
void GameObjectCommand::setValue(unsigned int value){
	this->_value = value;
}
unsigned int GameObjectCommand::getValue(){
	return this->_value;
}
void GameObjectCommand::setType(GameObjectCommandEnum  type){
	this->_type = type;
}
GameObjectCommandEnum  GameObjectCommand::getType(){
	return this->_type;
}