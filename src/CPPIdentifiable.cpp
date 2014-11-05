//
//  CPPIdentifiable.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//
#include "CPPIdentifiable.h"
#include <iostream>

static unsigned long _nextId;
static unsigned long getNextId()
{
    return _nextId++;
};

CPPIdentifiable::CPPIdentifiable()
{
    this->_id = getNextId();
    //std::cout << "Created identifiable with id " << this->_id << std::endl;
};
CPPIdentifiable::~CPPIdentifiable()
{
    //std::cout << "Destoryed identifiable with id " << this->_id << std::endl;
};
unsigned long CPPIdentifiable::getId() const
{
    return _id;
};