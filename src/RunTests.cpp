#include "RunTests.h"
#include "TestResult.h"
#include "Testing.h"

RunTests::RunTests()
{
	Testing::performTests(false);
	system("pause");
}


RunTests::~RunTests()
{
}
