#include "PhysicsUpdateCommand.h"

PhysicsUpdateCommand::PhysicsUpdateCommand(unsigned int gameObjectId, PhysicsCommandEnum type) : ComponentUpdateCommand(gameObjectId){
	this->_type = type;
}
PhysicsUpdateCommand::PhysicsUpdateCommand(unsigned int gameObjectId, PhysicsCommandEnum type, glm::vec3 value) : ComponentUpdateCommand(gameObjectId){
	this->_type = type;
	this->_value = value;
}
void PhysicsUpdateCommand::setValue(glm::vec3 value){
	this->_value = value;
}
glm::vec3 PhysicsUpdateCommand::getValue(){
	return this->_value;
}
void PhysicsUpdateCommand::setType(PhysicsCommandEnum type){
	this->_type = type;
}
PhysicsCommandEnum PhysicsUpdateCommand::getType(){
	return this->_type;
}