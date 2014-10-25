//
//  TestTests.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__TestTests__
#define __OpenGLTutorial__TestTests__

#include "Testing.h"
class TestResult;

class TestTests : public Test
{
public:
    TestResult doTest(bool stopOnFailure);
private:
    TestResult testTestContext(bool stopOnFailure);
    TestResult testAssert(bool stopOnFailure);
    TestResult testAssertFormat(bool stopOnFailure);
    TestResult testAssertEquals(bool stopOnFailure);
    TestResult testAssertNotEquals(bool stopOnFailure);
};
#endif /* defined(__OpenGLTutorial__TestTests__) */
