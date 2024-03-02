#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Airline.h"
#include "Airport.h"
#include "General.h"

void	initAirline(Airline* pComp)
{
	//printf("-----------  Init Airline\n");
	pComp->name = getStrExactName("Enter Airline name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	pComp->planeArr = NULL;
	pComp->planeCount = 0;
	pComp->sortType = eNotSorted;
}

int	addFlight(Airline* pComp, const AirportManager* pManager)
{
	if (!hasXorMoreAirports(pManager, 2)) {
		printf("There are not enough airport to set a flight\n");
		return 0;
	}
	if (pComp->planeCount == 0)
	{
		printf("There is no plane in company\n");
		return 0;
	}

	Flight* pFlight = (Flight*)calloc(1, sizeof(Flight));
	if (!pFlight)
		return 0;

	Plane* thePlane = FindAPlane(pComp);
	printAirports(pManager);
	initFlight(pFlight, thePlane, pManager);

	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	if (!pComp->flightArr)
	{
		free(pFlight);
		return 0;
	}
	pComp->flightArr[pComp->flightCount] = pFlight;
	pComp->flightCount++;
	pComp->sortType = eNotSorted;
	return 1;
}

int		addPlane(Airline* pComp)
{
	pComp->planeArr = (Plane*)realloc(pComp->planeArr, (pComp->planeCount + 1) * sizeof(Plane));
	if (!pComp->planeArr)
		return 0;
	initPlane(&pComp->planeArr[pComp->planeCount], pComp->planeArr, pComp->planeCount);
	pComp->planeCount++;
	return 1;
}

Plane* FindAPlane(Airline* pComp)
{
	printf("Choose a plane from list, type its serial Number\n");
	printPlanesArr(pComp->planeArr, pComp->planeCount);
	int sn;
	Plane* temp = NULL;
	do {
		scanf("%d", &sn);
		temp = findPlaneBySN(pComp->planeArr, pComp->planeCount, sn);
		if (!temp)
			printf("No plane with that serial number! Try again!\n");
	} while (temp == NULL);

	return temp;
}

void	doPrintFlightsWithPlaneType(const Airline* pComp)
{
	ePlaneType type = getPlaneType();
	int count = 0;
	printf("Flights with plane type %s:\n", GetPlaneTypeStr(type));
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (isPlaneTypeInFlight(pComp->flightArr[i], type))
		{
			printFlight(pComp->flightArr[i]);
			count++;
		}
	}
	if (count == 0)
		printf("Sorry - could not find a flight with plane type %s:\n", GetPlaneTypeStr(type));
	printf("\n");
}

void printCompany(const Airline* pComp)
{
	printf("Airline %s\n", pComp->name);
	printf("\n -------- Has %d planes\n", pComp->planeCount);
	printPlanesArr(pComp->planeArr, pComp->planeCount);
	printf("\n\n -------- Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);
}

void	printFlightArr(Flight** arr, int size)
{
	//TODO check if needed to cast to void*
	generalArrayFunction((void*)arr, size, sizeof(Flight*), printFlightWrapper);
}

void	printPlanesArr(Plane* arr, int size)
{
	generalArrayFunction((void*)arr, size, sizeof(Plane), printPlane);
}

void	freeFlightArr(Flight** arr, int size)
{
	generalArrayFunction((void*)arr, size, sizeof(Flight*), freeFlight);
}

void	freePlanes(Plane* arr, int size)
{
	for (int i = 0; i < size; i++)
		freePlane(&arr[i]);
}

void	freeCompany(Airline* pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->planeArr);
	free(pComp->name);
}


void sortFlightsByDate(Airline* pComp) {
	if (pComp == NULL || pComp->flightArr == NULL || pComp->flightCount == 0)
		return;

	qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightByDate);
	pComp->sortType = eSortByDate;
}


void sortFlightsByDest(Airline* pComp) {
	if (pComp == NULL || pComp->flightArr == NULL || pComp->flightCount == 0)
		return;

	qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightByDestinationCode);
	pComp->sortType = eSortByDest;
}

void sortFlightsByOrigin(Airline* pComp) {
	if (pComp == NULL || pComp->flightArr == NULL || pComp->flightCount == 0)
		return;

	qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightByOriginCode);
	pComp->sortType = eSortByOrigin;
}


void sortFlight(Airline* pComp) {
	int option = 0;
	printf("Base on what field do you want to sort?\n");
	do
	{
		for (int i = 1; i < eNofSortTypes; i++)
		{
			printf("Enter %d for %s\n", i, sortTypeStr[i]);
		}
		scanf("%d", &option);
	} while (option < 1 || option >= eNofSortTypes);

	switch (option)
	{
	case 1:
		sortFlightsByOrigin(pComp);
		break;
	case 2:
		sortFlightsByDest(pComp);
		break;
	case 3:
		sortFlightsByDate(pComp);
		break;
	}
	return;
}


Flight* findFlight(const Airline* pComp) {
	if (pComp == NULL || pComp->flightArr == NULL || pComp->flightCount == 0)
		return NULL;

	if (pComp->sortType == eNotSorted)
	{
		printf("The search cannot be performed, array not sorted\n");
		return NULL;
	}

	Flight* toSearch = (Flight*)calloc(1, sizeof(Flight));
	Flight** foundPtr = NULL; // the address of the found flight
	Flight* found = NULL; // the found flight

	if (!toSearch)
		return NULL;

	switch (pComp->sortType)
	{
	case eSortByOrigin:
		printf("Origin: ");
		getAirportCode(toSearch->sourceCode);
		foundPtr = (Flight**)bsearch(&toSearch, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightByOriginCode);
		break;
	case eSortByDest:
		printf("Destination: ");
		getAirportCode(toSearch->destCode);
		foundPtr = (Flight**)bsearch(&toSearch, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightByDestinationCode);
		break;
	case eSortByDate:
		getCorrectDate(&toSearch->date);
		foundPtr = (Flight**)bsearch(&toSearch, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightByDate);
		break;
	}

	if (foundPtr) {
		// found is the address of the found flight
		found = *foundPtr;
	}

	free(toSearch);
	return found;
}


int saveAirlineToFile(const Airline* pComp, const char* fileName) {
	FILE* file = fopen(fileName, "wb");
	if (!file) {
		return 0;
	}

	// Write the name
	if (!writeStringTobinFile(file, pComp->name)) {
		fclose(file);
		return 0;
	}
	if (!savePlaneArrToBinFile(file, pComp->planeArr, pComp->planeCount)) {
		fclose(file);
		return 0;
	}


	fclose(file);
	return 1;
}

int initAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName) {
	printf("restore data from file %s\n", fileName);
	FILE* file = fopen(fileName, "rb");
	if (!file) {
		// TDDO : add error message
		return 0;
	}
	// Read the name
	char* name = readStringFromBinFile(file);
	if (!name) {
		fclose(file);
		return 0;
	}
	//
	Plane* tempPlaneArr = NULL;
	int tempPlaneCount = 0;
	tempPlaneArr = readPlaneArrFromBinFile(file, &tempPlaneCount);
	if (!tempPlaneArr) {
		fclose(file);
		return 0;
	}


	pComp->planeCount = tempPlaneCount;
	pComp->planeArr = tempPlaneArr;
	pComp->name = name;
	pComp->sortType = eNotSorted;
	fclose(file);
	printf("name = %s\n", name);


}