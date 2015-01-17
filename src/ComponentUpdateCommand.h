#pragma once
class ComponentUpdateCommand {
public:
	ComponentUpdateCommand(unsigned int gameObjectId);
	unsigned int gameObjectId;
};