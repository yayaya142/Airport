
#include "Tests.h"

void runAllTests() {
	airportCompareCodeTestsAUTO();
	L_insertSortedTestsAUTO();


	//airportManagerTests();
	//compareDateTests();
	compareFlightTests();
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
	initManager(&manager);
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
	AirportManager manager;
	initManager(&manager);
	Airline airline;
	initAirline(&airline);
	for (int i = 0; i < 2; i++)
	{
		printf("Add airport %d\n", i + 1);
		addAirport(&manager);
	}
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

	// more sort
	for (int i = 0; i < 4; i++)
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

	generalArrayFunction(flightArr, 3, sizeof(Flight*), printFlight);



}
