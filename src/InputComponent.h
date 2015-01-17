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

class GameObjectIds;

class InputComponent : public Component{
public:
	virtual void update(double dT,
		unsigned int gameObjectId,
		std::vector<AIUpdateCommand> &aiCommands,
		std::vector<InputUpdateCommand> &inputCommands,
		std::vector<PhysicsUpdateCommand> &physicCommands,
		std::vector<RenderableUpdateCommand> &renderableCommands);
	InputComponent();
	InputComponent(InputComponent& other);
	void initWith(InputComponent &component);
};

#endif /* defined(__OpenGLTutorial__InputComponent__) */
