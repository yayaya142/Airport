
#include "Tests.h"

void runAllTests() {
	airportCompareCodeTestsAUTO();
	L_insertSortedTestsAUTO();
	testTextFilesAUTO();
	testL_CountAUTO();
	fileHelperTestsAUTO();
	saveAndLoadPlaneArrBinAUTO();

	airlineSaveAndLoadAUTO();
	//airportManagerTests();
	//compareDateTests();
	//compareFlightTests();
	//generalArrayTests();

	printf("\n\nall tests passed\n");
}


void airportManagerTests() {
	// Airport tests
	// test 1: init airport
	// test 2: add airport
	// test 3: add airport
	// test 4: add airport
	// test 5: free airport

	printf("--airport Manager Tests--\n");
	AirportManager manager;
	initManager(&manager, NULL);
	if (manager.airportList.head.next != NULL) {
		printf("Error init manger\n");
	}
	else {
		printf("Test 1 passed\n");
	}
	if (!addAirport(&manager)) {
		printf("Error adding airport\n");
		system("pause");
	}
	else
	{
		printf("Test 2 passed\n");
	}
	printAirports(&manager);
	if (!addAirport(&manager)) {
		printf("Error adding airport\n");
	}
	else
	{
		printf("Test 3 passed\n");
	}
	printAirports(&manager);
	if (!addAirport(&manager)) {
		printf("Error adding airport\n");
	}
	else
	{
		printf("Test 4 passed\n");
	}
	printAirports(&manager);
	if (!addAirport(&manager)) {
		printf("Error adding airport\n");
	}
	else
	{
		printf("Test 5 passed\n");
	}
	printAirports(&manager);
	if (!addAirport(&manager)) {
		printf("Error adding airport\n");
	}
	else
	{
		printf("Test 6 passed\n");
	}
	printAirports(&manager);

	freeManager(&manager);
	if (manager.airportList.head.next != NULL) {
		printf("Error free manger\n");
		system("pause");
	}
	else {
		printf("Test 7 passed\n");
	}
	printAirports(&manager);




}

void airportCompareCodeTestsAUTO() {
	// Test 1: Null airports
	assert(AirportCompareCode(NULL, NULL) == -1);

	// Test 2: One null airport
	Airport airport1;
	strcpy(airport1.code, "ABC");
	assert(AirportCompareCode(&airport1, NULL) == -1);

	// Test 3: Codes match
	Airport airport2;
	strcpy(airport2.code, "ABC");
	assert(AirportCompareCode(&airport1, &airport2) == 0);

	// Test 4: Codes do not match
	strcpy(airport2.code, "DEF");
	assert(AirportCompareCode(&airport1, &airport2) != 0);


	// Test 5: Codes do not match
	strcpy(airport2.code, "DEF");
	assert(AirportCompareCode(&airport1, &airport2) != 0);

	strcpy(airport1.code, "");
	strcpy(airport2.code, "");
	assert(AirportCompareCode(&airport1, &airport2) == 0);

	// Test 2: First code is empty
	strcpy(airport1.code, "");
	strcpy(airport2.code, "DEF");
	assert(AirportCompareCode(&airport1, &airport2) < 0);

	// Test 3: Second code is empty
	strcpy(airport1.code, "ABC");
	strcpy(airport2.code, "");
	assert(AirportCompareCode(&airport1, &airport2) > 0);

	// Test 4: First code comes before second
	strcpy(airport1.code, "ABC");
	strcpy(airport2.code, "DEF");
	assert(AirportCompareCode(&airport1, &airport2) < 0);

	// Test 5: Second code comes before first
	strcpy(airport1.code, "DEF");
	strcpy(airport2.code, "ABC");
	assert(AirportCompareCode(&airport1, &airport2) > 0);

	// Test 6: First code comes before second
	strcpy(airport1.code, "AAA");
	strcpy(airport2.code, "ABC");
	assert(AirportCompareCode(&airport1, &airport2) < 0);

	// Test 7: Second code comes before first
	strcpy(airport1.code, "ABC");
	strcpy(airport2.code, "AAA");
	assert(AirportCompareCode(&airport1, &airport2) > 0);

	// Test 8: First code comes before second
	strcpy(airport1.code, "ABC");
	strcpy(airport2.code, "ACB");
	assert(AirportCompareCode(&airport1, &airport2) < 0);
}



int compareInts(const void* a, const void* b) {
	int intA = *(int*)a;
	int intB = *(int*)b;
	return intA - intB;
}

void printInts(void* val) {
	printf("%d ", *(int*)val);
}
void L_insertSortedTestsAUTO() {
	// test the compare function
	int x = 5;
	int y = 7;
	assert(compareInts(&x, &y) < 0);
	assert(compareInts(&y, &x) > 0);
	assert(compareInts(&x, &x) == 0);

	// Test 1: Insert into empty list
	LIST list;
	L_init(&list);

	// Test 1: Insert into empty list
	int value1 = 5;
	NODE* node1 = L_insertSorted(&list, &value1, compareInts);
	assert(node1 != NULL && *(int*)node1->key == value1);
	//// Test 2: Insert smaller value
	int value2 = 3;
	NODE* node2 = L_insertSorted(&list, &value2, compareInts);

	assert(node2 != NULL && *(int*)node2->key == value2 && node2->next == node1);

	//// Test 3: Insert larger value
	int value3 = 7;
	NODE* node3 = L_insertSorted(&list, &value3, compareInts);
	assert(node3 != NULL && *(int*)node3->key == value3 && node1->next == node3);

	// Test 4: Insert value in the middle
	int value4 = 4;
	NODE* node4 = L_insertSorted(&list, &value4, compareInts);
	assert(node4 != NULL && *(int*)node4->key == value4 && node2->next == node4 && node4->next == node1);

	L_free(&list, NULL);
}


void compareDateTests() {
	Date date1;
	getCorrectDate(&date1);
	Date date2;
	getCorrectDate(&date2);
	printDate(&date1);
	printf("\n");
	printDate(&date2);
	printf("\n");
	int x = compareDates(&date1, &date2);
	printf("compareDates result: %d\n", x);
	if (x == 0)
		printf("Dates are equal\n");
	else if (x < 0)
		printf("First date is before second\n");
	else
		printf("First date is after second\n");
}

void compareFlightTests() {
	char* fileName = "testTextFileAUTO_tameplate.txt";
	AirportManager manager;
	initManager(&manager, fileName);
	Airline airline;
	initAirline(&airline);

	printf("add plane\n");
	for (int i = 0; i < 2; i++)
	{
		printf("Add plane %d\n", i + 1);
		addPlane(&airline);
	}
	for (int i = 0; i < 2; i++)
	{
		printf("Add flight %d\n", i + 1);
		printf("\nAirline sort type: %s\n", sortTypeStr[airline.sortType]);
		addFlight(&airline, &manager);
	}

	printf("\n\n\n---------before sort---------\n");
	printCompany(&airline);
	printf("\nAirline sort type: %s\n", sortTypeStr[airline.sortType]);
	//
	//
	printf("\n\n\n---------after sort by date---------\n");
	sortFlightsByDate(&airline);
	printCompany(&airline);
	printf("\nAirline sort type: %s\n", sortTypeStr[airline.sortType]);

	//
	//
	printf("\n\n\n---------after sort by dest---------\n");
	sortFlightsByDest(&airline);
	printCompany(&airline);
	printf("\nAirline sort type: %s\n", sortTypeStr[airline.sortType]);

	//
	//
	printf("\n\n\n---------after sort by origin---------\n");
	sortFlightsByOrigin(&airline);
	printCompany(&airline);
	printf("\nAirline sort type: %s\n", sortTypeStr[airline.sortType]);

	// more sort and binary search tests
	for (int i = 0; i < 5; i++)
	{
		sortFlight(&airline);
		printCompany(&airline);
		printf("\nAirline sort type: %s\n", sortTypeStr[airline.sortType]);
		printf("--------------- find flight ---------------\n");
		Flight* pFlight = findFlight(&airline);
		if (pFlight != NULL)
		{
			printFlight(pFlight);
		}
		else
		{
			printf("Flight not found\n");
		}
	}

	// free all
	freeCompany(&airline);
	freeManager(&manager);

}


void generalArrayTests() {
	// tests 1
	printf("-------general Array Tests------\n");
	int arr1[] = { 1, 2, 3, 4, 5 };
	printf("arr1: ");
	generalArrayFunction(arr1, 5, sizeof(int), printInts);
	printf("\n");
	printf("Plane test\n");
	Plane p1;
	p1.serialNum = 1;
	p1.type = 1;
	Plane p2;
	p2.serialNum = 2;
	p2.type = 2;
	Plane p3;
	p3.serialNum = 3;
	p3.type = 0;
	Plane planeArr[] = { p1, p2, p3 };
	printf("planeArr: \n");
	generalArrayFunction(planeArr, 3, sizeof(Plane), printPlane);

	printf("\n");
	// tests 2
	printf("Flight Test\n");

	Flight* f1 = (Flight*)malloc(sizeof(Flight));
	Flight* f2 = (Flight*)malloc(sizeof(Flight));
	Flight* f3 = (Flight*)malloc(sizeof(Flight));

	f1->date.day = 1;
	f1->date.month = 1;
	f1->date.year = 2020;
	char* source = "AAA";
	char* dest = "BBB";
	f1->flightPlane = p1;
	strcpy(f1->sourceCode, source);
	strcpy(f1->destCode, dest);
	printf("f1: \n");
	printFlight(f1);
	f2->date.day = 2;
	f2->date.month = 2;
	f2->date.year = 2020;
	f2->flightPlane = p2;
	strcpy(f2->sourceCode, source);
	strcpy(f2->destCode, dest);
	printf("f2: \n");
	printFlight(f2);
	f3->date.day = 3;
	f3->date.month = 3;
	f3->date.year = 2020;
	f3->flightPlane = p3;

	strcpy(f3->sourceCode, source);
	strcpy(f3->destCode, dest);
	printf("f3: \n");
	printFlight(f3);
	printf("\nflightArr: \n");
	Flight** flightArr = (Flight**)malloc(sizeof(Flight*) * 3);
	flightArr[0] = f1;
	flightArr[1] = f2;
	flightArr[2] = f3;

	generalArrayFunction(flightArr, 3, sizeof(Flight*), printFlightWrapper);

	// free all
	generalArrayFunction(flightArr, 3, sizeof(Flight*), freeFlight);


	free(flightArr);

}


void testL_CountAUTO() {
	// test 1: count empty list
	LIST list;
	L_init(&list);
	assert(L_count(&list) == 0);

	// test 2: count list with 1 element
	int value1 = 5;
	L_insert(&list, &value1);
	assert(L_count(&list) == 1);

	// test 3: count list with 2 elements
	int value2 = 3;
	L_insert(&list, &value2);
	assert(L_count(&list) == 2);

	// test 4: count list with 3 elements
	int value3 = 7;
	L_insert(&list, &value3);
	assert(L_count(&list) == 3);

	// test 5: count list with 4 elements
	int value4 = 4;
	L_insert(&list, &value4);
	assert(L_count(&list) == 4);

	// test 6: count list with 20 elements
	for (int i = 0; i < 16; i++)
	{
		L_insert(&list, &value4);
	}
	assert(L_count(&list) == 20);

	L_free(&list, NULL);

}


void testTextFilesAUTO() {
	const char* testFile = "testTextFileAUTO.txt";
	AirportManager manager;

	initManager(&manager, testFile);
	//loadManagerFromFile(&manager, testFile);
	//printAirports(&manager);

	// Check the number of airports
	int count = L_count(&manager.airportList);
	assert(count == 4);
	//
	// Check the airport codes

	// first airport
	Airport* pAirport = (Airport*)(manager.airportList.head.next->key);
	assert(strcmp(pAirport->name, "L_O_G_E_N") == 0);
	assert(strcmp(pAirport->country, "USA") == 0);
	assert(strcmp(pAirport->code, "ABC") == 0);
	//// second airport
	pAirport = (Airport*)(manager.airportList.head.next->next->key);
	assert(strcmp(pAirport->name, "Best Airport Ever") == 0);
	assert(strcmp(pAirport->country, "Greece") == 0);
	assert(strcmp(pAirport->code, "ASD") == 0);
	//// third airport
	pAirport = (Airport*)(manager.airportList.head.next->next->next->key);
	assert(strcmp(pAirport->name, "Best  Airport") == 0);
	assert(strcmp(pAirport->country, "India") == 0);
	assert(strcmp(pAirport->code, "WER") == 0);
	//// fourth airport
	pAirport = (Airport*)(manager.airportList.head.next->next->next->next->key);
	assert(strcmp(pAirport->name, "Ben  Gurion") == 0);
	assert(strcmp(pAirport->country, "Israel") == 0);
	assert(strcmp(pAirport->code, "YLV") == 0);


	saveManagerToFile(&manager, testFile);


	freeManager(&manager);
}

void fileHelperTestsAUTO() {
	char* firstStr = "Hello world this a test for the binary file and for the text file";
	char* textFileName = "file_Helper_Text_Auto_Test.txt";
	char* binFileName = "file_Helper_Bin_Auto_Test.bin";
	// ------- text file test -------
	// write to file test
	FILE* textFileWrite = fopen(textFileName, "w");
	if (textFileWrite == NULL) {
		printf("Error opening file!\n");
		return;
	}

	writeStringToFile(textFileWrite, firstStr);
	fclose(textFileWrite);
	// read from file test
	FILE* textFileRead = fopen(textFileName, "r");
	char* readText = readStringFromTextFile(textFileRead);
	//printf("readText: %s\n", readText);
	assert(strcmp(readText, firstStr) == 0);
	free(readText);



	//------ binary file test -------
	//write string to bin file test
	FILE* binFileWrite = fopen(binFileName, "wb");
	if (binFileWrite == NULL) {
		printf("Error opening file!\n");
		return;
	}
	writeStringTobinFile(binFileWrite, firstStr);
	fclose(binFileWrite);
	// read string from bin file test
	FILE* binFileRead = fopen(binFileName, "rb");
	readText = readStringFromBinFile(binFileRead);
	assert(strcmp(readText, firstStr) == 0);
	free(readText);

	// write int to bin file test
	int x = 5;
	binFileWrite = fopen(binFileName, "wb");
	if (binFileWrite == NULL) {
		printf("Error opening file!\n");
		return;
	}
	writeGeneralToBinFile(binFileWrite, &x, sizeof(int));
	fclose(binFileWrite);
	// read int from bin file test
	binFileRead = fopen(binFileName, "rb");
	int restoreInt;
	readGeneralFromBinFile(binFileRead, &restoreInt, sizeof(int));
	fclose(binFileRead);
	assert(restoreInt == x);


	// write Plane to bin file test
	Plane p1;
	p1.serialNum = 1554;
	p1.type = 1;

	binFileWrite = fopen(binFileName, "wb");
	if (binFileWrite == NULL) {
		printf("Error opening file!\n");
		return;
	}
	writeGeneralToBinFile(binFileWrite, &p1, sizeof(Plane));
	fclose(binFileWrite);
	// read Plane from bin file test
	binFileRead = fopen(binFileName, "rb");
	Plane restorePlane;
	readGeneralFromBinFile(binFileRead, &restorePlane, sizeof(Plane));
	assert(restorePlane.serialNum == p1.serialNum);
	assert(restorePlane.type == p1.type);
	fclose(binFileRead);

	// plane 2
	Plane p2;
	p2.serialNum = 1234;
	p2.type = 2;
	// write Plane to bin file test
	binFileWrite = fopen(binFileName, "wb");
	savePlaneToBinFile(binFileWrite, &p2);
	fclose(binFileWrite);
	// read Plane from bin file test
	binFileRead = fopen(binFileName, "rb");
	restorePlane = readPlaneFromBinFile(binFileRead);
	assert(restorePlane.serialNum == p2.serialNum);

	// write Date to bin file test
	Date d1;
	d1.day = 24;
	d1.month = 8;
	d1.year = 1998;
	binFileWrite = fopen(binFileName, "wb");
	if (binFileWrite == NULL) {
		printf("Error opening file!\n");
		return;
	}
	writeGeneralToBinFile(binFileWrite, &d1, sizeof(Date));
	fclose(binFileWrite);
	// read Date from bin file test
	binFileRead = fopen(binFileName, "rb");
	Date restoreDate;
	readGeneralFromBinFile(binFileRead, &restoreDate, sizeof(Date));
	assert(restoreDate.day == d1.day);
	assert(restoreDate.month == d1.month);
	assert(restoreDate.year == d1.year);
	fclose(binFileRead);

}

void saveAndLoadPlaneArrBinAUTO() {
	Plane p1;
	p1.serialNum = 1;
	p1.type = 0;
	Plane p2;
	p2.serialNum = 2;
	p2.type = 1;
	Plane p3;
	p3.serialNum = 3;
	p3.type = 2;
	Plane p4;
	p4.serialNum = 4;
	p4.type = 0;
	Plane p5;
	p5.serialNum = 5;
	p5.type = 1;
	Plane p6;
	p6.serialNum = 6;
	p6.type = 2;
	Plane planeArr[] = { p1, p2, p3, p4, p5, p6 };

	char* fileName = "testPlaneArrAUTO.bin";
	FILE* fileWrite = fopen(fileName, "wb");
	if (!savePlaneArrToBinFile(fileWrite, planeArr, 6)) {
		printf("Error saving plane arr to bin file\n");
	}

	fclose(fileWrite);
	// read from file test
	Plane* restoredPlaneArr;
	FILE* fileRead = fopen(fileName, "rb");
	int count = 0;
	restoredPlaneArr = readPlaneArrFromBinFile(fileRead, &count);
	assert(restoredPlaneArr != NULL);
	assert(restoredPlaneArr[0].serialNum == p1.serialNum);
	assert(restoredPlaneArr[0].type == p1.type);
	assert(restoredPlaneArr[1].serialNum == p2.serialNum);
	assert(restoredPlaneArr[1].type == p2.type);
	assert(restoredPlaneArr[2].serialNum == p3.serialNum);
	assert(restoredPlaneArr[2].type == p3.type);
	assert(restoredPlaneArr[3].serialNum == p4.serialNum);
	assert(restoredPlaneArr[3].type == p4.type);
	assert(restoredPlaneArr[4].serialNum == p5.serialNum);
	assert(restoredPlaneArr[4].type == p5.type);
	assert(restoredPlaneArr[5].serialNum == p6.serialNum);
	assert(restoredPlaneArr[5].type == p6.type);

	free(restoredPlaneArr);
	fclose(fileRead);
}



void airlineSaveAndLoadAUTO() {
	printf("airline save and load tests\n");
	char* fileName = "testAirlineAUTO.bin";
	char* airportFileName = "testTextFileAUTO_tameplate.txt";
	Airline airline;
	Airline restoredAirline;
	AirportManager manager;
	initManager(&manager, airportFileName);
	printAirports(&manager);
	initAirline(&airline);
	addPlane(&airline);
	addPlane(&airline);
	saveAirlineToFile(&airline, fileName);


	initAirlineFromFile(&restoredAirline, &manager, fileName);
	printCompany(&restoredAirline);
	freeCompany(&airline);
	freeCompany(&restoredAirline);
	freeManager(&manager);
}

