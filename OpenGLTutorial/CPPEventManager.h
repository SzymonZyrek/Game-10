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
#include "CPPQueue.h"
#include <memory>
#include <map>
#include "CPPEventHandler.h"
#include "CPPEvent.h"

class CPPEventManager : public CPPIdentifiable{
public:
    
private:
    std::map<unsigned long, std::shared_ptr<CPPEventHandler>> _handlersById;
    CPPQueue<std::shared_ptr<CPPEvent>> _eventQueue;
};
#endif /* defined(__OpenGLTutorial__CPPEventManager__) */
