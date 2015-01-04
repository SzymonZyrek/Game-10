//
//  CPPEventManager.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__CPPEventManager__
#define __OpenGLTutorial__CPPEventManager__

#include "CPPIdentifiable.h"
#include <memory>
#include <map>
#include <set>
#include <queue>
#include "CPPEventHandler.h"
#include "CPPEvent.h"

class CPPEventManager : public CPPIdentifiable{
public:
    static CPPEventManager GED;
    CPPEventManager();
	~CPPEventManager();
    CPPEventManager(int queueeSize);
    void notify(std::shared_ptr<CPPEvent> event);
    void notifyByID(unsigned long handlerID, std::shared_ptr<CPPEvent> event);
    void notifyByType(CPPEventType type, std::shared_ptr<CPPEvent> event);
    void registerEventHandler(std::shared_ptr<CPPEventHandler> handler);
    void handleEvents();
    void printHandlers();
private:
    std::map<unsigned long, std::shared_ptr<CPPEventHandler>> _handlersById;
    std::map<CPPEventType, std::set<unsigned long>> _handlerIdsByType;
    std::queue<std::shared_ptr<CPPEvent>> _eventQueue;
	int _eventQueueSize;
};
#endif /* defined(__OpenGLTutorial__CPPEventManager__) */
