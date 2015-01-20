//
//  InputComponent.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__InputComponent__
#define __OpenGLTutorial__InputComponent__

#include "Component.h"
#include "PhysicsUpdateCommand.h"

class GameObjectIds;

class InputComponent : public Component{
public:
	virtual std::vector<PhysicsUpdateCommand> update(double dT);
	InputComponent();
	InputComponent(InputComponent& other);
	void initWith(InputComponent &component);
};

#endif /* defined(__OpenGLTutorial__InputComponent__) */
