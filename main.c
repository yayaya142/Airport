#include <stdlib.h>
#include <crtdbg.h> // TODO: remove before release

#include "exe.h"
#include "Tests.h"


int main()
{

	//manualTest();




	runAllTests();




	// Debug memory leaks
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
	_CrtDumpMemoryLeaks();
	return 0;
}

