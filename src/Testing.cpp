//
//  Testing.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "Testing.h"
#include "TestResult.h"
#include "TestTests.h"
#include "TestUtils.h"
#include "TestEvents.h"
#include "TestGameObjects.h"
#include "TestWorlds.h"
#include "TestConfig.h"
#include "CPPLogger.h"

TestResult Testing::performTests(bool stopOnFailure)
{
	try {
			TestResult result;
			TestTests tt;
			TestUtils tu;
			TestEvents te;
			TestGameObjects tgo;
			TestWorlds tw;
			TestConfig tc;

			std::cout << "----------------------\n"
				<< "|  Performing tests  |\n"
				<< "----------------------\n";

			result += tc.doTest(stopOnFailure); result.print("ConfigModule");
			if (stopOnFailure && (!result)) return result;

			result += tt.doTest(stopOnFailure); result.print("TestsModule");
			if (stopOnFailure && (!result)) return result;

			result += tu.doTest(stopOnFailure); result.print("UtilsModule");
			if (stopOnFailure && (!result)) return result;
			
			result += te.doTest(stopOnFailure); result.print("EventModule");
			if (stopOnFailure && (!result)) return result;


			result += tgo.doTest(stopOnFailure); result.print("GameOModule");
			if (stopOnFailure && (!result)) return result;


			result += tw.doTest(stopOnFailure); result.print("WorldModule");
			if (stopOnFailure && (!result)) return result;
	} catch (char* err){
		std::stringstream ss;
		ss << "Exception caught while performing tests: " << std::string(err);
		Log::error(ss.str());
	} catch (std::string err){
		std::stringstream ss;
		ss << "Exception caught while performing tests: " << err;
		Log::error(ss.str());
	}
	std::cout
		<< "------------------\n"
		<< "|  Game10 is up  |\n"
		<< "------------------\n";
	
	return TestResult();
}
