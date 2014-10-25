//
//  Testing.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "Testing.h"
#include "TestResult.h"
#include "TestTests.h"
#include "TestUtils.h"
#include "TestEvents.h"
#include "TestEventHandler.h"

TestResult Testing::performTests(bool stopOnFailure)
{
testContext(
    TestTests tt;
    TestUtils tu;
    TestEvents te;
    TestEventHandler teh;
            
    testModule(tt,"TestsModule")
    testModule(tu,"UtilsModule")
    testModule(te,"EventModule:Event")
    testModule(teh,"EventModule:EventHandler")
)
}
