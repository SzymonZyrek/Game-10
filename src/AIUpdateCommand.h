#pragma once
#include <glm/glm.hpp>
#include "ComponentUpdateCommand.h"

enum AICommandEnum {
	SOUND_TRIGGER, VISUAL_TRIGGER, MOVE_TO_POSITION
};

class AIUpdateCommand : public ComponentUpdateCommand {
public:
	AIUpdateCommand(unsigned int gameObjectId, AICommandEnum type);
	AIUpdateCommand::AIUpdateCommand(unsigned int gameObjectId, AICommandEnum type, int intValue, glm::vec3 vec3Value);
	void setIntValue(unsigned int value);
	int getIntValue();
	glm::vec3 getVec3Value();
	void setVec3Value(glm::vec3 value);
	AICommandEnum getType();
	void setType(AICommandEnum type);
	unsigned int gameObjectId;
private:
	int _intValue;
	glm::vec3 _vec3Value;
	AICommandEnum _type;
};