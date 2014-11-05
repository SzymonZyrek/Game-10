//
//  TestWorlds.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__TestWorlds__
#define __OpenGLTutorial__TestWorlds__

#include "Testing.h"

class TestWorlds : public Test {
public:
    TestResult doTest(bool stopOnFailure);
private:
    TestResult testScene(bool stopOnFailure);
};
#endif /* defined(__OpenGLTutorial__TestWorlds__) */
