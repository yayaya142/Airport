#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "exe.h"
#include "Tests.h"


int main()
{
	manualTest();



	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
	_CrtDumpMemoryLeaks();
	//runAllTests();
	return 1;
}

