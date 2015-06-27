//
//  CPPEventManager.cpp
//  Game10
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "CPPEventManager.h"
#include <iostream>
#include "CPPEventType.h"
#define BASE_EVENT_QUEUEE_SIZE 10
CPPEventManager CPPEventManager::GED;

void CPPEventManager::printHandlers()
{
    std::cout << "Handlers: \n";
    for(auto it = _handlerIdsByType.begin(); it != _handlerIdsByType.end(); ++it) {
        std::cout << CPPEventUtil::eventTypeAsString(it->first) << ": [";
        for (unsigned long handlerID: it->second)
        {
            std::cout << handlerID << ",";
        }
        std::cout << "]\n";
    }
}

CPPEventManager::CPPEventManager() : _eventQueueSize(BASE_EVENT_QUEUEE_SIZE)
{
    
}

CPPEventManager::~CPPEventManager()
{
}

CPPEventManager::CPPEventManager(int queueeSize) : _eventQueueSize(queueeSize)
{
    
}
void CPPEventManager::registerEventHandler(std::shared_ptr<CPPEventHandler> handler)
{
    _handlersById[handler->getId()] = handler;
    for (CPPEventType type : handler->getHandledTypes()){
        _handlerIdsByType[type].insert(handler->getId());
    }
}

void CPPEventManager::notify(std::shared_ptr<CPPEvent> event)
{
	if (_eventQueue.size() >= _eventQueueSize)
	{
		throw std::runtime_error("Event queue is full! Cant add more elements");
	}
    _eventQueue.push(event);
}
void CPPEventManager::notifyByID(unsigned long handlerID, std::shared_ptr<CPPEvent> event)
{
    
}
void CPPEventManager::notifyByType(CPPEventType type, std::shared_ptr<CPPEvent> event)
{
    
}
void CPPEventManager::handleEvents()
{
    bool handled = false;
    while (!_eventQueue.empty())
    {
		std::shared_ptr<CPPEvent> theEvent = _eventQueue.front();
        for (unsigned long handlerID: _handlerIdsByType[theEvent->getType()])
        {
            _handlersById[handlerID]->handleEvent(theEvent);
            handled = true;
        }
        if (!handled)
        {
            //std::cout << "Event " << theEvent << " gone unnoticed!\n";
        }
		_eventQueue.pop();
    }
}