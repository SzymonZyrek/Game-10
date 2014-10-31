//
//  Component.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "Component.h"

Component::Component()
{
    
}
void Component::setDaddyId(int daddy){
    this->_daddyId = daddy;
}
int Component::getDaddyId()
{
    return this->_daddyId;
}