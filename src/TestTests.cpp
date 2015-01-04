//
//  TestTests.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "TestTests.h"
#include "TestResult.h"
#include "Testing.h"
#include<iostream>


TestResult TestTests::doTest(bool stopOnFailure)
{
    testContext(
                runTest(testTestContext)
                runTest(testAssert)
                runTest(testAssertFormat)
                runTest(testAssertEquals)
                runTest(testAssertNotEquals)
                )
};
TestResult TestTests::testTestContext(bool stopOnFailure)
{
    testContext(
        assert(result, "Result does not exist..")
    )
};
TestResult TestTests::testAssert(bool stopOnFailure)
{
    testContext(
        std::string message = "True is false.. thas usually not a good sign ;)";
        assert(true, message)
        assert(!false, message)
    )
};
TestResult TestTests::testAssertFormat(bool stopOnFailure)
{
    testContext(
        if (false){
            char buffer[100];
            int n = sprintf(buffer,"formatted %d string",5);
            result += TestResult(std::string(buffer,n));
            if (stopOnFailure) return result;
        }
        // assertFormat(false, "formatted %d string", 5)
        //assertFormat(false, "", &a, 'y', 3.4)
    )
};
TestResult TestTests::testAssertEquals(bool stopOnFailure)
{
    testContext(
        assertEquals(1, 1, "1 does not equal 1..")
    )
};
TestResult TestTests::testAssertNotEquals(bool stopOnFailure)
{
    testContext(
        assertNotEquals("foo", "bar", "foo equals bar..")
    )
};