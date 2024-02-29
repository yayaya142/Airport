
#include "Tests.h"

void runAllTests() {
	airportCompareCodeTestsAUTO();
	L_insertSortedTestsAUTO();


	airportManagerTests();





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
