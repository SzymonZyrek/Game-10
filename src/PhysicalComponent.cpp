//
//  PhysicalComponent.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "PhysicalComponent.h"
#include "GameObjectIds.h"
#include <sstream>
#include "CPPLogger.h"

PhysicalComponent::PhysicalComponent()
{
	Log::debug("PhysicalComponent default contructor\n", DebugKey::OBJECT_CREATION);
}

PhysicalComponent::PhysicalComponent(PhysicalComponent& other)
{
	this->_daddyId = other.getDaddyId();
	Log::debug("PhysicalComponent copy contructor\n", DebugKey::OBJECT_CREATION);
}


void PhysicalComponent::initWith(PhysicalComponent &component)
{
	this->_daddyId = component.getDaddyId();
	this->_active = component._active;
}

void PhysicalComponent::update(double dT,
	unsigned int gameObjectId,
	std::vector<AIUpdateCommand> &aiCommands,
	std::vector<InputUpdateCommand> &inputCommands,
	std::vector<PhysicsUpdateCommand> &physicCommands,
	std::vector<RenderableUpdateCommand> &renderableCommands)
{
	std::stringstream ss;
	ss << "updating physics of " << this->_daddyId << std::endl;
	Log::periodic(ss.str(), this->_logPeriodicKey);

	RenderableUpdateCommand command(gameObjectId, RenderableCommandEnum::TEST_ROTATE);
	renderableCommands.push_back(command);
}