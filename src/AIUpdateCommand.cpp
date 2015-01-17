#include "AIUpdateCommand.h"

AIUpdateCommand::AIUpdateCommand(unsigned int gameObjectId, AICommandEnum type) : ComponentUpdateCommand(gameObjectId){
	this->_type = type;
}
AIUpdateCommand::AIUpdateCommand(unsigned int gameObjectId, AICommandEnum type, int intValue, glm::vec3 vec3Value) : ComponentUpdateCommand(gameObjectId){
	this->_intValue;
	this->_vec3Value;
}
void AIUpdateCommand::setIntValue(unsigned int value){
	this->_intValue = value;
}
void AIUpdateCommand::setVec3Value(glm::vec3 value){
	this->_vec3Value = value;
}
int AIUpdateCommand::getIntValue(){
	return this->_intValue;
}
glm::vec3 AIUpdateCommand::getVec3Value(){
	return this->_vec3Value;
}
AICommandEnum AIUpdateCommand::getType(){
	return this->_type;
}
void AIUpdateCommand::setType(AICommandEnum type){
	this-> _type = type;
}