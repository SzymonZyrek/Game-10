//
//  PhysicalComponent.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "PhysicalComponent.h"
#include "GameObjectIds.h"

void PhysicalComponent::initWith(PhysicalComponent &component)
{
    
}

void PhysicalComponent::update(double dT)
{
     std::cout << "updating physics of " << this->_daddyId  <<std::endl;
}