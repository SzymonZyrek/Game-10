//
//  AIComponent.h
//  Game10
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__AIComponent__
#define __Game10__AIComponent__

#include "Component.h"
#include <vector>
#include "InputUpdateCommand.h"

enum Attitude { SCARED, FRIENDLY, ALLY, INDIFFERENT, ANGRY, HOSTILE };

class GameObjectIds;

class AIComponent : public Component{
public:
	AIComponent();
	AIComponent(AIComponent& other);
	AIComponent(Attitude att);
	virtual std::vector<InputUpdateCommand> update(double dT);
    void initWith(AIComponent &component);
	Attitude getAttitude();
	void setAttitude(Attitude att);
private:
	Attitude _attitude;
};

#endif /* defined(__Game10__AIComponent__) */
