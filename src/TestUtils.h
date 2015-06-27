//
//  TestUtils.h
//  Game10
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__TestUtils__
#define __Game10__TestUtils__

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
#endif /* defined(__Game10__TestUtils__) */
