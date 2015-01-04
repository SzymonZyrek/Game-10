//
//  TestWorlds.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "TestWorlds.h"
#include "TestResult.h"
#include "Errors.h"
#include "GameObject.h"
#include "GameObjectIds.h"
#include "Scene.h"
#include "TestGameObjects.h"

TestResult TestWorlds::doTest(bool stopOnFailure)
{
    testContext(
            runTest(testScene)
                )
}
TestResult TestWorlds::testScene(bool stopOnFailure)
{
	TestResult result;
                Scene scene;
				GameObject objprt = *TestGameObjects::getTestGamaObject();
				scene.registerGameObject(&objprt);
				try
				{
					scene.registerGameObject(&objprt);
				}
				catch (ErrorCodes err)
				{
					if (err != ErrorCodes::REGISTERING_REGISTERED_OBJECT){
						throw err;
					}
				}
				scene.registerGameObject(new GameObject(objprt));
				for (int i = 0; i < 10000; i++){
					scene.update(0.1);
				}
	return result;
}