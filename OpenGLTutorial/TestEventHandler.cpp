//
//  TestEventHandler.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "TestEventHandler.h"
#include "TestResult.h"
#include "Testing.h"
#include "CPPEventHandler.h"
#include "CPPEventType.h"

TestEvent::TestEvent(int load) : CPPEvent(Events_TEST)
{
    this->payload = load;
}

TestHandler::TestHandler() : CPPEventHandler(Events_TEST){}

void TestHandler::handleEvent(std::shared_ptr<CPPEvent> event)
{
    std::shared_ptr<TestEvent> derived =
               std::dynamic_pointer_cast<TestEvent> (event);
    if (derived){
        std::cout << "Payload: "<< derived->payload << std::endl;
    }else{
        std::cout << "No shit" << std::endl;
    }

}

TestResult TestEventHandler::doTest(bool stopOnFailure)
{
    testContext(
        runTest(testInitializingWithTypes)
    )
}

TestResult TestEventHandler::testInitializingWithTypes(bool stopOnFailure){
    testContext(
        std::vector<CPPEventType> types;
        types.push_back(Events_ERROR);
        types.push_back(Events_INFO);
        TestHandler handler;
    )
}