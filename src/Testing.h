//
//  TestModule.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

// Yeah this part its kinda ugly but handy:
// the macros aren't rly that complicated
// it's just notation convenience, to be
// able to run simple tests quickly
#ifndef __OpenGLTutorial__TestModule__
#define __OpenGLTutorial__TestModule__
#define assert(__EXPR__,__ERR__) if (!__EXPR__){result += TestResult(__ERR__); if (stopOnFailure) return result;}
#define assertFormat(__EXPR__,__ERR_FRMT__,...) if (!__EXPR__){char buffer[100]; int n = sprintf(buffer,__EXPR__,...); result += TestResult(std::string(buffer,n)); if (stopOnFailure) return result;}
#define assertEquals(__EXPR1__,__EXPR2__,__ERR__) if (__EXPR1__!=__EXPR2__){result += TestResult(__ERR__); if (stopOnFailure) return result;}
#define assertNotEquals(__EXPR1__,__EXPR2__,__ERR__) if (__EXPR1__==__EXPR2__){result += TestResult(__ERR__); if (stopOnFailure) return result;}
#define testContext(__BODY__) TestResult result; __BODY__ return result;
#define runTest(__TEST__) result += __TEST__(stopOnFailure); if (!result && stopOnFailure) return result;
#define testModule(__MODULE__,__DESC__) result+=__MODULE__.doTest(stopOnFailure); result.print(__DESC__); if(stopOnFailure&&(!result)) return result;

#include<string>
#include<sstream>
#include<cstdarg>
#include<iostream>
#include<stdio.h>



class TestResult;
class Testing{
public:

	static TestResult performTests(bool stopOnFailure);
};
class Test {
public:
    virtual TestResult doTest(bool stopOnFailure) = 0;
};
#endif /* defined(__OpenGLTutorial__TestModule__) */
