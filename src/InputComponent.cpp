//
//  InputComponent.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "InputComponent.h"
#include "GameObjectIds.h"
#include <sstream>
#include "CPPLogger.h"

InputComponent::InputComponent()
{
	Log::debug("InputComponent default contructor\n", DebugKey::OBJECT_CREATION);
}

InputComponent::InputComponent(InputComponent& other)
{
	this->_daddyId = other.getDaddyId();
	Log::debug("InputComponent copy contructor\n", DebugKey::OBJECT_CREATION);
}

void InputComponent::initWith(InputComponent &component)
{
    
}

void InputComponent::update(double dT)
{
	std::stringstream ss;
	ss << "updating input of " << this->_daddyId << std::endl;
	Log::periodic(ss.str(), this->_logPeriodicKey);
}