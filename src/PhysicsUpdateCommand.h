#pragma once
#include <glm/glm.hpp>
#include "ComponentUpdateCommand.h"

enum PhysicsCommandEnum {
	SET_BODY_POSITION, SET_VELOCITY, SET_ANGULAR_VELOCITY, SET_MASS, APPLY_IMPULSE_FORCE
};

class PhysicsUpdateCommand : public ComponentUpdateCommand {
public:
	PhysicsUpdateCommand(unsigned int gameObjectId, PhysicsCommandEnum type);
	PhysicsUpdateCommand(unsigned int gameObjectId, PhysicsCommandEnum type, glm::vec3 value);
	void setValue(glm::vec3 value);
	glm::vec3 getValue();
	PhysicsCommandEnum getType();
	void setType(PhysicsCommandEnum type);
	unsigned int gameObjectId;
private:
	glm::vec3 _value;
	PhysicsCommandEnum _type;
};