//
//  CPPEventManager.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "CPPEventManager.h"

CPPEventManager CPPEventManager::GED;

CPPEventManager::CPPEventManager()
{
    
}
void CPPEventManager::registerEventHandler(std::shared_ptr<CPPEventHandler> handler)
{
    
}

void CPPEventManager::registerEvent(std::shared_ptr<CPPEvent> event)
{
    
}
void CPPEventManager::notifyByID(unsigned long handlerID, std::shared_ptr<CPPEvent> event)
{
    
}
void CPPEventManager::notifyByType(CPPEventType type, std::shared_ptr<CPPEvent> event)
{
    
}