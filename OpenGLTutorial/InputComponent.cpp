//
//  InputComponent.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "InputComponent.h"
#include "GameObjectIds.h"

void InputComponent::initWith(InputComponent &component)
{
    
}

void InputComponent::update(double dT)
{
    std::cout << "updating input of " << this->_daddyId  <<std::endl;
}