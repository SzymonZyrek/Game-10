#include "InputUpdateCommand.h"

InputUpdateCommand::InputUpdateCommand(unsigned int gameObjectId, InputCommandEnum type) : ComponentUpdateCommand(gameObjectId){
	this->_type = type;
}
InputUpdateCommand::InputUpdateCommand(unsigned int gameObjectId, InputCommandEnum  type, unsigned int value) : ComponentUpdateCommand(gameObjectId){
	this->_type = type;
	this->_value = value;
}
void InputUpdateCommand::setValue(unsigned int value){
	this->_value = value;
}
unsigned int InputUpdateCommand::getValue(){
	return this->_value;
}
void InputUpdateCommand::setType(InputCommandEnum  type){
	this->_type = type;
}
InputCommandEnum  InputUpdateCommand::getType(){
	return this->_type;
}