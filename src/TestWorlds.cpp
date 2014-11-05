//
//  TestWorlds.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "TestWorlds.h"
#include "TestResult.h"
#include "GameObject.h"
#include "GameObjectIds.h"
#include "Scene.h"
#include "RenderableComponent.h"
#include "PhysicalComponent.h"
#include "AIComponent.h"
#include "InputComponent.h"

TestResult TestWorlds::doTest(bool stopOnFailure)
{
    testContext(
            runTest(testScene)
                )
}
TestResult TestWorlds::testScene(bool stopOnFailure)
{
    testContext(
                GameObject* object = new GameObject;
                object->setAIComponent(new AIComponent());
                object->setInputComponent(new InputComponent());
                object->setPhysicalComponent(new PhysicalComponent());
                object->setRenderableComponent(new RenderableComponent());
                Scene scene;
                scene.registerGameObject(object);
                
    )
}