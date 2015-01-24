//
//  Component.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__Component__
#define __OpenGLTutorial__Component__

#include <iostream>
#include "RenderableUpdateCommand.h"
#include "AIUpdateCommand.h"
#include "PhysicsUpdateCommand.h"
#include "InputUpdateCommand.h"
#include <vector>

class Component {
public:
    Component();
	void Component::setGameObjectId(unsigned int gameObjectId);
	unsigned int getGameObjectId();
	bool isActive();
	void setActive(bool active);
	operator bool() const;
protected:
	// TODO(optimalisation): implement gameObjectId in component so that daddyId can be removed
	// and full data locality can be achieved
	unsigned int gameObjectId = 0;
	bool _active = false;
	bool _isNullComponent;
protected:
	unsigned int _logPeriodicKey;
};

#endif
