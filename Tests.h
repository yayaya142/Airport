#ifndef __TESTS__
#define __TESTS__

#include <crtdbg.h> // TODO: remove before release
#include <assert.h>
#include <stdio.h>
#include "Airline.h"
#include "AirportManager.h"
#include "General.h"
#include "fileHelper.h"

void runAllTests();
void airportManagerTests();
void airportCompareCodeTestsAUTO();
void L_insertSortedTestsAUTO();
int compareInts(const void* a, const void* b);
void printInts(void* val);
void compareDateTests();
void compareFlightTests();
void generalArrayTests();
void testTextFilesAUTO();
void testL_CountAUTO();
void airlineSaveAndLoadAUTO();
void fileHelperTestsAUTO();
void saveAndLoadPlaneArrBinAUTO();
void saveAndLoadDateBinAUTO();
void saveAndLoadFlightBinAUTO();
void saveAndLoadPlaneSerialNumberAUTO();
void saveAndLoadFlightArrBinAUTO();

#endif // __TESTS__