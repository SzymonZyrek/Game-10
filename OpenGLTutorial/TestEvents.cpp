//
//  TestEvents.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "TestEvents.h"
#include "TestResult.h"
#include "Testing.h"
#include "CPPEvent.h"
#include "CPPEventType.h"
#include "CPPEventHandler.h"
#include <iostream>
#define TEST_PAYLOAD 66

int TestEvents::resultPlaceholder = -1;

TestResult TestEvents::doTest(bool stopOnFailure)
{
    testContext(
                runTest(testCPPEvent)
                runTest(testEventHandlers)
    )
};

TestResult TestEvents::testEventHandlers(bool stopOnFailure)
{
    testContext(
                TestHandler handler;
                handler.handleEvent(std::make_shared<TestEvent>(TEST_PAYLOAD));
                assert((TestEvents::resultPlaceholder==TEST_PAYLOAD), "Test event has wrong payload")
                )
}


TestEvent::TestEvent(int load) : CPPEvent(Events_TEST)
{
    this->payload = load;
}

TestHandler::TestHandler() : CPPEventHandler(Events_TEST, Events_ERROR){}

void TestHandler::handleEvent(std::shared_ptr<CPPEvent> event)
{
    std::shared_ptr<TestEvent> derived =
    std::dynamic_pointer_cast<TestEvent> (event);
    if (derived){
        TestEvents::resultPlaceholder = derived->payload;
    }else{
        TestEvents::resultPlaceholder = -1;
    }
}


TestResult TestEvents::testCPPEvent(bool stopOnFailure)
{
    testContext(
                CPPEvent e(Events_DEBUG);
                assertEquals(e.getType(), Events_DEBUG, "Event type is not properly assigned")
    )
};