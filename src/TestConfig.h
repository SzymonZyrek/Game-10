//
//  TestEvents.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#pragma once
#include "Testing.h"
#include "Config.h"
class TestResult;

class TestConfig: public Test
{
public:
    TestResult doTest(bool stopOnFailure);
	static int resultPlaceholder;
private:
	TestResult testMainConfig(bool stopOnFailure);
};