#pragma once
#include <glm/glm.hpp>
#include "ComponentUpdateCommand.h"


enum GameObjectCommandEnum {
	SET_AI, SET_BODY, SET_RENDERABLE, SET_INPUT
};

class GameObjectCommand : public ComponentUpdateCommand {
public:
	GameObjectCommand(unsigned int gameObjectId, GameObjectCommandEnum type);
	GameObjectCommand(unsigned int gameObjectId, GameObjectCommandEnum type, unsigned int value);
	void setValue(unsigned int value);
	unsigned int getValue();
	GameObjectCommandEnum getType();
	void setType(GameObjectCommandEnum type);
	unsigned int gameObjectId;
private:
	unsigned int _value;
	GameObjectCommandEnum _type;
};
