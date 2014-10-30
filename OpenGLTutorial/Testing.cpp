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
#include "Playground.h"

TestResult Testing::performTests(bool stopOnFailure)
{
    Playground::p_main();
testContext(
    TestTests tt;
    TestUtils tu;
    TestEvents te;
            
    testModule(tt,"TestsModule")
    testModule(tu,"UtilsModule")
    testModule(te,"EventModule:Event")
    //testModule(teh,"EventModule:EventHandler")
)
}
