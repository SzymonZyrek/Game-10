//
//  CPPEventHandler.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__CPPEventHandler__
#define __OpenGLTutorial__CPPEventHandler__

#include <vector>
#include "CPPEvent.h"
#include "CPPEventType.h"
#include "CPPIdentifiable.h"
#include <memory>

class CPPEventHandler : public CPPIdentifiable {
public:
    CPPEventHandler(int num, ...);
    virtual ~CPPEventHandler();
    std::vector<CPPEventType> getHandledTypes() const;
    virtual void handleEvent(std::shared_ptr<CPPEvent> event) = 0;
private:
    std::vector<CPPEventType> _types;
};
#endif
