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

class GameObjectIds;

class AIComponent : public Component{
public:
    virtual void update(double dT);
    void initWith(AIComponent &component);
};

#endif /* defined(__OpenGLTutorial__AIComponent__) */
