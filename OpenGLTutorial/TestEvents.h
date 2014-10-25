//
//  TestEvents.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__TestEvents__
#define __OpenGLTutorial__TestEvents__

#include "Testing.h"
class TestResult;

class TestEvents : public Test
{
public:
    TestResult doTest(bool stopOnFailure);
private:
    TestResult testCPPEvent(bool stopOnFailure);
};
#endif /* defined(__OpenGLTutorial__TestEvents__) */
