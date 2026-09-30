//
//  PhysicalComponent.h
//  Game10
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__PhysicalComponent__
#define __Game10__PhysicalComponent__

#include "Component.h"

class GameObjectIds;

class PhysicalComponent : public Component {
public:
	PhysicalComponent();
	PhysicalComponent(PhysicalComponent& other);
	virtual std::vector<RenderableUpdateCommand> update(double dT);
    void initWith(PhysicalComponent &component);
};

#endif /* defined(__Game10__PhysicalComponent__) */
