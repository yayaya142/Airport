#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "General.h"


void	initFlight(Flight* pFlight, Plane* thePlane, const AirportManager* pManager)
{
	Airport* pPortOr = setAirportToFlight(pManager, "Enter code of origin airport:");
	strcpy(pFlight->sourceCode, pPortOr->code);
	int same;
	Airport* pPortDes;
	do {
		pPortDes = setAirportToFlight(pManager, "Enter code of destination airport:");
		same = isSameAirport(pPortOr, pPortDes);
		if (same)
			printf("Same origin and destination airport\n");
	} while (same);
	strcpy(pFlight->destCode, pPortDes->code);
	pFlight->flightPlane = *thePlane;
	getCorrectDate(&pFlight->date);
}

int		isFlightFromSourceAirport(const Flight* pFlight, const char* code)
{
	if (strcmp(pFlight->sourceCode, code) == 0)
		return 1;

	return 0;
}


int		isFlightToDestAirport(const Flight* pFlight, const char* code)
{
	if (strcmp(pFlight->destCode, code) == 0)
		return 1;

	return 0;


}

int		isPlaneTypeInFlight(const Flight* pFlight, ePlaneType type)
{
	return (pFlight->flightPlane.type == type);
}


void	printFlight(const Flight* pFlight)
{
	printf("Flight From %s To %s\t", pFlight->sourceCode, pFlight->destCode);
	printDate(&pFlight->date);
	printf("\t");
	printPlane(&pFlight->flightPlane);
}

void printFlightWrapper(const void* flight) {
	const Flight* pFlight = *(const Flight**)flight;
	printFlight(pFlight);
}


Airport* setAirportToFlight(const AirportManager* pManager, const char* msg)
{
	char code[MAX_STR_LEN];
	Airport* port;
	do
	{
		printf("%s\t", msg);
		getAirportCode(code);
		port = findAirportByCode(pManager, code);
		if (port == NULL)
			printf("No airport with this code - try again\n");
	} while (port == NULL);

	return port;
}


int compareFlightByDate(const void* pFlight1, const void* pFlight2) {
	if (!pFlight1 || !pFlight2) {
		return -1;
	}

	Flight* flight1 = *(Flight**)pFlight1;
	Flight* flight2 = *(Flight**)pFlight2;

	return compareDates(&flight1->date, &flight2->date);
}


int compareFlightByOriginCode(const void* pFlight1, const void* pFlight2) {
	if (pFlight1 == NULL || pFlight2 == NULL) {
		return -1;
	}

	Flight* flight1 = *(Flight**)pFlight1;
	Flight* flight2 = *(Flight**)pFlight2;

	return strcmp(flight1->sourceCode, flight2->sourceCode);
}


int compareFlightByDestinationCode(const void* pFlight1, const void* pFlight2) {
	if (pFlight1 == NULL || pFlight2 == NULL) {
		return -1;
	}

	Flight* flight1 = *(Flight**)pFlight1;
	Flight* flight2 = *(Flight**)pFlight2;

	return strcmp(flight1->destCode, flight2->destCode);
}


void freeFlight(void* flight) {
	Flight* pFlight = *(Flight**)flight;
	free(pFlight);
}