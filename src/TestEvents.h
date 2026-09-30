//
//  TestEvents.h
//  Game10
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__TestEvents__
#define __Game10__TestEvents__

#include "Testing.h"
#include "CPPEventHandler.h"
class TestResult;

class TestEvents : public Test
{
public:
    TestResult doTest(bool stopOnFailure);
    static int resultPlaceholder;
private:
    TestResult testInitializingWithTypes(bool stopOnFailure);
    TestResult testCPPEvent(bool stopOnFailure);
    TestResult testEventHandlers(bool stopOnFailure);
    TestResult testEventManager(bool stopOnFailure);
    TestResult testGlobalEventManager(bool stopOnFailure);
};

// TEST CLASSES: simple test event, and handler for it:
class TestEvent : public CPPEvent {
public:
    int payload;
    TestEvent(int load);
};
class TestHandler : public CPPEventHandler
{
public:
    TestHandler();
    virtual void handleEvent(std::shared_ptr<CPPEvent> event);
};
#endif /* defined(__Game10__TestEvents__) */
