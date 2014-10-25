//
//  TestEventHandler.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__TestEventHandler__
#define __OpenGLTutorial__TestEventHandler__
#include "Testing.h"
#include "CPPEventHandler.h"
#include "CPPEvent.h"
class TestResult;

class TestHandler : public CPPEventHandler
{
public:
    TestHandler();
    virtual void handleEvent(std::shared_ptr<CPPEvent> event);
};

class TestEvent : public CPPEvent {
public:
    int payload;
    TestEvent(int load);
};

class TestEventHandler : public Test
{
public:
    TestResult doTest(bool stopOnFailure);
private:
    TestResult testInitializingWithTypes(bool stopOnFailure);
};
#endif /* defined(__OpenGLTutorial__TestEventHandler__) */
