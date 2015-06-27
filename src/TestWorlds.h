//
//  TestWorlds.h
//  Game10
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__TestWorlds__
#define __Game10__TestWorlds__

#include "Testing.h"

class TestWorlds : public Test {
public:
    TestResult doTest(bool stopOnFailure);
private:
    TestResult testScene(bool stopOnFailure);
};
#endif /* defined(__Game10__TestWorlds__) */
