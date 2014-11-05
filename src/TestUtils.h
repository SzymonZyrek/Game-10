//
//  TestUtils.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__TestUtils__
#define __OpenGLTutorial__TestUtils__

#include "Testing.h"
class TestResult;

class TestUtils : public Test
{
public:
    TestResult doTest(bool stopOnFailure);
private:
    TestResult testCPPIdentifiable(bool stopOnFailure);
    TestResult testCPPQueue(bool stopOnFailure);
};
#endif /* defined(__OpenGLTutorial__TestUtils__) */
