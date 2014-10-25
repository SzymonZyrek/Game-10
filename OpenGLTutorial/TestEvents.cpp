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
#include <iostream>

TestResult TestEvents::doTest(bool stopOnFailure)
{
    testContext(
        runTest(testCPPEvent)
    )
};
TestResult TestEvents::testCPPEvent(bool stopOnFailure)
{
    testContext(
                CPPEvent e(Events_DEBUG);
                assertEquals(e.getType(), Events_DEBUG, "Event type is not properly assigned")
    )
};