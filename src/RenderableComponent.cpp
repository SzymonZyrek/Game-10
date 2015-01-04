//
//  RenderableComponent.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "RenderableComponent.h"
#include "GameObjectIds.h"
#include "CPPLogger.h"
#include <sstream>

RenderableComponent::RenderableComponent()
{
	Log::debug("RenderableComponent default contructor\n", DebugKey::OBJECT_CREATION);
}

RenderableComponent::RenderableComponent(RenderableComponent& other)
{
	this->_daddyId = other.getDaddyId();
	Log::debug("RenderableComponent copy contructor\n", DebugKey::OBJECT_CREATION);
}

void RenderableComponent::initWith(RenderableComponent &component)
{
    
}

void RenderableComponent::update(double dT)
{
	this->render();
}
void RenderableComponent::render()
{
	std::stringstream ss;
	ss << "rendering" << this->_daddyId << std::endl;
	Log::periodic(ss.str(), this->_logPeriodicKey);
}