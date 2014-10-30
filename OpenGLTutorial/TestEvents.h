//
//  TestEvents.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__TestEvents__
#define __OpenGLTutorial__TestEvents__

#include "Testing.h"
#include "CPPEventHandler.h"
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

class TestEvents : public Test
{
public:
    TestResult doTest(bool stopOnFailure);
    static int resultPlaceholder;
private:
    TestResult testInitializingWithTypes(bool stopOnFailure);
    TestResult testCPPEvent(bool stopOnFailure);
    TestResult testEventHandlers(bool stopOnFailure);
};
#endif /* defined(__OpenGLTutorial__TestEvents__) */
