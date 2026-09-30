#include "Win32EntryPoint.h"
#define _CRTDBG_MAP_ALLOC
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "CPPLogger.h"
#include "RunPlayground.h"

int main(int argc, char* argv[])
{
	int logKey = Log::getInstance()->getLogPeriodicKey(2.0);
	Log::getInstance()->flush();
	RunPlayground p;
	p.p_main();
	_CrtDumpMemoryLeaks();
	return 0;
}
