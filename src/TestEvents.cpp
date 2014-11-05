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
#include "CPPEventManager.h"
#include <iostream>
#define TEST_PAYLOAD1 66
#define TEST_PAYLOAD2 23
#define TEST_PAYLOAD3 17
#define TEST_PAYLOAD4 53

int TestEvents::resultPlaceholder = -1;
TestEvent tev(TEST_PAYLOAD2);

TestResult TestEvents::doTest(bool stopOnFailure)
{
    testContext(
                runTest(testCPPEvent)
                runTest(testEventHandlers)
                runTest(testEventManager)
                runTest(testGlobalEventManager)
    )
}


TestResult TestEvents::testCPPEvent(bool stopOnFailure)
{
    testContext(
                CPPEvent e(Events_DEBUG);
                assertEquals(e.getType(), Events_DEBUG, "Event type is not properly assigned")
                )
};

TestResult TestEvents::testEventHandlers(bool stopOnFailure)
{
    testContext(
                TestHandler handler;
                TestEvent* e = new TestEvent(TEST_PAYLOAD1);
                handler.handleEvent(std::shared_ptr<TestEvent>(e));
                assert((TestEvents::resultPlaceholder==TEST_PAYLOAD1), "Test event has wrong payload (TEST_PAYLOAD1)")
                )
}

void fireEvent()
{
    TestEvent* eP = &tev;
    CPPEventManager::GED.notify(std::shared_ptr<TestEvent>(eP));
    //CPPEventManager::GED.notify(std::make_shared<TestEvent>(TEST_PAYLOAD2));
}

TestResult TestEvents::testGlobalEventManager(bool stopOnFailure)
{
    testContext(
                CPPEventManager::GED.registerEventHandler(std::make_shared<TestHandler>());
                // simulate event input
                fireEvent();
                // simulate event loop pass
                CPPEventManager::GED.handleEvents();
                assert((TestEvents::resultPlaceholder==TEST_PAYLOAD2), "Test event has wrong payload (TEST_PAYLOAD2)")
                // reset result
                TestEvents::resultPlaceholder = TEST_PAYLOAD3;
                // another pass, there should be no events this time
                CPPEventManager::GED.handleEvents();
                assert((TestEvents::resultPlaceholder==TEST_PAYLOAD3), "Events not cleared after beeing handled")
    )
}

TestResult TestEvents::testEventManager(bool stopOnFailure)
{
    testContext(
                // create small event manager
                CPPEventManager manager(4);
                // spawn some events
                manager.notify(std::make_shared<TestEvent>(1));
                manager.notify(std::make_shared<TestEvent>(2));
                manager.notify(std::make_shared<TestEvent>(3));
                manager.notify(std::make_shared<TestEvent>(4));
                try{
                    manager.notify(std::make_shared<TestEvent>(5));
                    assert(false, "EventManager allowed registering event when queuee was full")
                }catch (std::runtime_error &e){
                    // yeah, this should fail, too much events for now
                }
                // give queuee a break
                manager.handleEvents();
                // enqueuee some more, should work as queuee just got emptied
                manager.notify(std::make_shared<TestEvent>(5));
                manager.notify(std::make_shared<TestEvent>(6));
    )
}


// TestEvent test class- example event with int data
//---------------------------------------------------
TestEvent::TestEvent(int load) : CPPEvent(Events_TEST)
{
    this->payload = load;
}
//---------------------------------------------------

// TestHandler test class- example handler for TestEvent
//---------------------------------------------------
TestHandler::TestHandler() : CPPEventHandler(1, Events_TEST){}
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
//---------------------------------------------------
