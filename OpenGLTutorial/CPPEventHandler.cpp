//
//  CPPEventHandler.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "CPPEventHandler.h"
#include "CPPEventType.h"

CPPEventHandler::CPPEventHandler(int num, ...)
{
    va_list arguments;
    va_start(arguments, num);
    for (int j = 0; j < num; j++) {
        CPPEventType type = (CPPEventType)va_arg(arguments, int);
        this->_types.push_back(type);
    }
    va_end(arguments);
}
CPPEventHandler::~CPPEventHandler()
{
    
}
std::vector<CPPEventType> CPPEventHandler::getHandledTypes() const
{
    return _types;
}