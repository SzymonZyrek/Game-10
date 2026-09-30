//
//  InputComponent.h
//  Game10
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__InputComponent__
#define __Game10__InputComponent__

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

#endif /* defined(__Game10__InputComponent__) */
