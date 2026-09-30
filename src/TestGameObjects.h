//
//  TestGameObjects.h
//  Game10
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__TestGameObjects__
#define __Game10__TestGameObjects__


#include "Testing.h"

class GameObject;

class TestGameObjects : public Test {
public:
    TestResult doTest(bool stopOnFailure);
	static GameObject* getTestGamaObject();
private:
	static GameObject* testGameObject;
};

#endif /* defined(__Game10__TestGameObjects__) */
