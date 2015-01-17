#pragma once
#include <glm/glm.hpp>
#include "ComponentUpdateCommand.h"

enum InputCommandEnum {
	KEY_PRESSED, KEY_RELEASED, KEY_DOWN, SET_MODE
};

class InputUpdateCommand : public ComponentUpdateCommand {
public:
	InputUpdateCommand(unsigned int gameObjectId, InputCommandEnum type);
	InputUpdateCommand(unsigned int gameObjectId, InputCommandEnum type, unsigned int value);
	void setValue(unsigned int value);
	unsigned int getValue();
	InputCommandEnum getType();
	void setType(InputCommandEnum type);
	unsigned int gameObjectId;
private:
	unsigned int _value;
	InputCommandEnum _type;
};