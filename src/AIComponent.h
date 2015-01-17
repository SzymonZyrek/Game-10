//
//  AIComponent.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__AIComponent__
#define __OpenGLTutorial__AIComponent__

#include "Component.h"

enum Attitude { SCARED, FRIENDLY, ALLY, INDIFFERENT, ANGRY, HOSTILE };

class GameObjectIds;

class AIComponent : public Component{
public:
	AIComponent();
	AIComponent(AIComponent& other);
	AIComponent(Attitude att);
	virtual void update(double dT,
		unsigned int gameObjectId,
		std::vector<AIUpdateCommand> &aiCommands,
		std::vector<InputUpdateCommand> &inputCommands,
		std::vector<PhysicsUpdateCommand> &physicCommands,
		std::vector<RenderableUpdateCommand> &renderableCommands);
    void initWith(AIComponent &component);
	Attitude getAttitude();
	void setAttitude(Attitude att);
private:
	Attitude _attitude;
};

#endif /* defined(__OpenGLTutorial__AIComponent__) */
