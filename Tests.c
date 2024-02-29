#include <stdio.h>
#include "Tests.h"
#include "Airline.h"
#include "AirportManager.h"
#include "General.h"


void runAllTests() {


	airportManagerTests();





	printf("\n\nall tests passed\n");
}



void airportManagerTests() {
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
	}
	else
	{
		printf("Test 2 passed\n");
	}
	printAirports(&manager);
	//if (!addAirport(&manager)) {
	//	printf("Error adding airport\n");
	//}
	//else
	//{
	//	printf("Test 3 passed\n");
	//}
	//printAirports(&manager);
	//if (!addAirport(&manager)) {
	//	printf("Error adding airport\n");
	//}
	//else
	//{
	//	printf("Test 4 passed\n");
	//}
	//printAirports(&manager);
	freeManager(&manager);
	if (manager.airportList.head.next != NULL) {
		printf("Error free manger\n");
	}
	else {
		printf("Test 5 passed\n");
	}
	printAirports(&manager);




}