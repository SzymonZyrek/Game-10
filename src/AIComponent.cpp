//
//  AIComponent.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "AIComponent.h"
#include "GameObjectIds.h"

void AIComponent::initWith(AIComponent &component)
{
    
}

void AIComponent::update(double dT)
{
     std::cout << "updating AI of " << this->_daddyId  <<std::endl;
}