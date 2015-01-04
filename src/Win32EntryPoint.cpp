#include "Win32EntryPoint.h"
#include "TestResult.h"
#include "Testing.h"
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "CPPLogger.h"

int main(int argc, char* argv[])
{
	Testing::performTests(false);
	int logKey = Log::getInstance()->getLogPeriodicKey(2.0);
	Log::getInstance()->flush();
	system("pause");
	_CrtDumpMemoryLeaks();
	return 0;
}
