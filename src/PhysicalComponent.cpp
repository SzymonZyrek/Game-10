//
//  PhysicalComponent.cpp
//  Game10
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "PhysicalComponent.h"
#include "GameObjectIds.h"
#include <sstream>
#include "CPPLogger.h"
#include "PhysicsUpdateCommand.h"

PhysicalComponent::PhysicalComponent()
{
	Log::debug("PhysicalComponent default contructor\n", DebugKey::OBJECT_CREATION);
}

PhysicalComponent::PhysicalComponent(PhysicalComponent& other)
{
	this->gameObjectId = other.gameObjectId;
	Log::debug("PhysicalComponent copy contructor\n", DebugKey::OBJECT_CREATION);
}


void PhysicalComponent::initWith(PhysicalComponent &component)
{
	this->gameObjectId = component.gameObjectId;
	this->_active = component._active;
}


std::vector<RenderableUpdateCommand> PhysicalComponent::update(double dT)
{
	std::vector<RenderableUpdateCommand> result;
	RenderableUpdateCommand command(gameObjectId, RenderableCommandEnum::TEST_ROTATE);
	result.push_back(command);
	std::stringstream ss;
	ss << "updating input of " << this->gameObjectId << std::endl;
	Log::periodic(ss.str(), this->_logPeriodicKey);
	return result;
}