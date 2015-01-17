//
//  PhysicalComponent.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__PhysicalComponent__
#define __OpenGLTutorial__PhysicalComponent__

#include "Component.h"

class GameObjectIds;

class PhysicalComponent : public Component {
public:
	PhysicalComponent();
	PhysicalComponent(PhysicalComponent& other);
	virtual void update(double dT,
		unsigned int gameObjectId,
		std::vector<AIUpdateCommand> &aiCommands,
		std::vector<InputUpdateCommand> &inputCommands,
		std::vector<PhysicsUpdateCommand> &physicCommands,
		std::vector<RenderableUpdateCommand> &renderableCommands);
    void initWith(PhysicalComponent &component);
};

#endif /* defined(__OpenGLTutorial__PhysicalComponent__) */
