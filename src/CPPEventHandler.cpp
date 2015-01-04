//
//  CPPEventHandler.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "CPPEventHandler.h"
#include "CPPEventType.h"
#include <initializer_list>

CPPEventHandler::CPPEventHandler(std::initializer_list<CPPEventType> &types)
{
	for (auto it = types.begin(); it != types.end(); ++it) {
		CPPEventType type = *it;
        this->_types.push_back(type);
    }
}
CPPEventHandler::~CPPEventHandler()
{
    
}
std::vector<CPPEventType> CPPEventHandler::getHandledTypes() const
{
    return _types;
}
std::ostream& operator<<(std::ostream& os, const CPPEventHandler& e)
{
    const CPPIdentifiable & b(e);
    os << "#" << b.getId()  << "CPPEventHandler for types ";
    for (CPPEventType typ : e.getHandledTypes())
    {
        os << CPPEventUtil::eventTypeAsString(typ) << ",";
    }
    return os;
};