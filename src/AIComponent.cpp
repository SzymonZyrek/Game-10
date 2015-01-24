//
//  AIComponent.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "AIComponent.h"
#include "GameObjectIds.h"
#include <sstream>
#include "CPPLogger.h"
#include "InputUpdateCommand.h"

AIComponent::AIComponent() : _attitude(INDIFFERENT)
{
	 Log::debug("AIComponent default contructor\n", DebugKey::OBJECT_CREATION);
}
AIComponent::AIComponent(AIComponent& other)
{
	this->_attitude = other.getAttitude();
	this->gameObjectId = other.getGameObjectId();
	Log::debug("AIComponent copy contructor\n", DebugKey::OBJECT_CREATION);
}

AIComponent::AIComponent(Attitude att) : _attitude(att)
{
	Log::debug("AIComponent contructor with attitude\n", DebugKey::OBJECT_CREATION);
}

void AIComponent::setAttitude(Attitude att)
{
	this->_attitude = att;
}

void AIComponent::initWith(AIComponent &component)
{
	this->_attitude = component.getAttitude();
	this->_active = component._active;
}

std::vector<InputUpdateCommand> AIComponent::update(double dT)
{
	std::stringstream ss;
	ss << "updating AI of " << this->gameObjectId << std::endl;
	Log::periodic(ss.str(), this->_logPeriodicKey);
	return std::vector<InputUpdateCommand>();
}
Attitude AIComponent::getAttitude()
{
	return this->_attitude;
}
