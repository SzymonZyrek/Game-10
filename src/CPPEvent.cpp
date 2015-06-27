//
//  CPPEvent.cpp
//  Game10
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "CPPEvent.h"
#include <string>
#include <sstream>
#include <iostream>
#include "CPPIdentifiable.h"
#include "CPPEventType.h"

CPPEvent::CPPEvent(CPPEventType type){
    this->_type = type;
};
CPPEventType CPPEvent::getType()
{
    return _type;
};

std::ostream& operator<<(std::ostream& os, const CPPEvent& e)
{
    const CPPIdentifiable & b(e);
    os << "#" << b.getId()  << "CPPEvent of type " << CPPEventUtil::eventTypeAsString(e._type);
    return os;
};
