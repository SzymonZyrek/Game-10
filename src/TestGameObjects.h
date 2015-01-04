//
//  TestGameObjects.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__TestGameObjects__
#define __OpenGLTutorial__TestGameObjects__


#include "Testing.h"

class GameObject;

class TestGameObjects : public Test {
public:
    TestResult doTest(bool stopOnFailure);
	static GameObject* getTestGamaObject();
private:
	static GameObject* testGameObject;
};

#endif /* defined(__OpenGLTutorial__TestGameObjects__) */
