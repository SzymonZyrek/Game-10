#include "RenderableUpdateCommand.h"

RenderableUpdateCommand::RenderableUpdateCommand(unsigned int gameObjectId, RenderableCommandEnum type) : ComponentUpdateCommand(gameObjectId){
	this->_type = type;
}
RenderableUpdateCommand::RenderableUpdateCommand(unsigned int gameObjectId, RenderableCommandEnum type, glm::vec3 value) : ComponentUpdateCommand(gameObjectId){
	this->_type = type;
	this->_value = value;
}
void RenderableUpdateCommand::setValue(glm::vec3 value){
	this->_value = value;
}
glm::vec3 RenderableUpdateCommand::getValue(){
	return this->_value;
}
void RenderableUpdateCommand::setType(RenderableCommandEnum type){
	this->_type = type;
}
RenderableCommandEnum RenderableUpdateCommand::getType(){
	return this->_type;
}