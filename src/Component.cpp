//
//  Component.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "Component.h"
#include "CPPLogger.h"

Component::Component()
{
	this->_logPeriodicKey = Log::getInstance()->getLogPeriodicKey(2.0);
	this->_isNullComponent = true;
}
void Component::setDaddyId(unsigned int daddy){
	this->_daddyId = daddy;
	this->_active = true;
}
unsigned int Component::getDaddyId()
{
	return this->_daddyId;
}
bool Component::isActive()
{
	return _active;
}

void Component::setActive(bool active){
	this->_active = active;
}

Component::operator bool() const
{
	return !this->_isNullComponent;
}