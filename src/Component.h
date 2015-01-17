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
	void setDaddyId(unsigned int daddy);
	unsigned int getDaddyId();
	bool isActive();
	void setActive(bool active);
	virtual void update(double dT,
		unsigned int gameObjectId,
		std::vector<AIUpdateCommand> &aiCommands,
		std::vector<InputUpdateCommand> &inputCommands,
		std::vector<PhysicsUpdateCommand> &physicCommands,
		std::vector<RenderableUpdateCommand> &renderableCommands) = 0;
	operator bool() const;
protected:
    int _daddyId = -1;
	// TODO(optimalisation): implement gameObjectId in component so that daddyId can be removed
	// and full data locality can be achieved
	//unsigned int gameObjectId;
	bool _active = false;
	bool _isNullComponent;
protected:
	unsigned int _logPeriodicKey;
};

#endif /* defined(__OpenGLTutorial__Component__) */
