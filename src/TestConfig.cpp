//
//  TestEvents.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//
#include "TestConfig.h"
#include "TestResult.h"
#include "Testing.h"
#include <iostream>


TestResult TestConfig::doTest(bool stopOnFailure)
{
	testContext(
		runTest(testMainConfig)
    )
}


TestResult TestConfig::testMainConfig(bool stopOnFailure){
	testContext(
		Config mainCongig = Config::getMainConfig();

		)
}