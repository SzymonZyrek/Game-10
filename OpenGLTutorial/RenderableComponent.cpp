//
//  RenderableComponent.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "RenderableComponent.h"
#include "GameObjectIds.h"


void RenderableComponent::initWith(RenderableComponent &component)
{
    
}

void RenderableComponent::update(double dT)
{
     std::cout << "updating renderable of " << this->_daddyId <<std::endl;
}