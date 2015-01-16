//
//  TestGameObjects.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "TestGameObjects.h"
#include "TestResult.h"
#include "GameObject.h"
#include "RenderableComponent.h"
#include "PhysicalComponent.h"
#include "AIComponent.h"
#include "InputComponent.h"

GameObject* TestGameObjects::testGameObject;

TestResult TestGameObjects::doTest(bool stopOnFailure)
{
	TestResult result;
		GameObject *object = getTestGamaObject();
		assert(object->hasAIComponent(), "test GameObject has no AI component");
	/*	GameObject *object2 = new GameObject(*object);
		object2->getAIComponent()->setAttitude(Attitude::HOSTILE);
		assert((object->getAIComponent()->getAttitude() == Attitude::FRIENDLY), "test GameObject has some bad attitude! (should be default- FRIENDLY)");
		assert((object2->getAIComponent()->getAttitude() == Attitude::HOSTILE), "test GameObject2 has some bad attitude! (should be default- HOSTILE)");
		assert(object->hasInputComponent(), "test GameObject has no input component")
		assert(object->hasPhysicalComponent(), "test GameObject has no physical component")
		assert(object->hasRenderableComponent(), "test GameObject has no renderable component")
		assert(object->hasSpecialComponents(), "test GameObject has no special components")*/
	return result;
}
GameObject* TestGameObjects::getTestGamaObject(){
	if (TestGameObjects::testGameObject == nullptr){
		TestGameObjects::testGameObject = new GameObject;
		testGameObject->setAIComponent(new AIComponent(Attitude::FRIENDLY));
		testGameObject->setInputComponent(new InputComponent());
		testGameObject->setPhysicalComponent(new PhysicalComponent());
		Renderable renderable;
		testGameObject->setRenderableComponent(new RenderableComponent(std::make_shared <Renderable>()));
		testGameObject->addSpecialComponent(new AIComponent());
	}
	return TestGameObjects::testGameObject;
}
