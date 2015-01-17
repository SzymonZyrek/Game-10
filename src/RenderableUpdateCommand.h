#pragma once
#include <glm/glm.hpp>
#include "ComponentUpdateCommand.h"

enum RenderableCommandEnum {
	SET_POSITION, SET_ROTATION, SET_SCALE, SET_TEXTURE, SET_MODEL, SET_ANIMATION, SET_ANIMATION_STATE, TEST_ROTATE // lol, yeah, animation
};

class RenderableUpdateCommand : public ComponentUpdateCommand {
public:
	RenderableUpdateCommand(unsigned int gameObjectId, RenderableCommandEnum type);
	RenderableUpdateCommand(unsigned int gameObjectId, RenderableCommandEnum type, glm::vec3 value);
	void setValue(glm::vec3 value);
	glm::vec3 getValue();
	RenderableCommandEnum getType();
	void setType(RenderableCommandEnum type);
	unsigned int gameObjectId;
private:
	glm::vec3 _value;
	RenderableCommandEnum _type;
};