#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AirportManager.h"
#include "General.h"

int	initManager(AirportManager* pManager)
{
	L_init(&pManager->airportList);

	return 1;
}

int	addAirport(AirportManager* pManager)
{
	NODE* ptr1 = NULL;
	Airport* pPort = (Airport*)calloc(1, sizeof(Airport));
	if (!pPort)
		return 0;

	if (!initAirport(pPort, pManager))
	{
		freeAirport(pPort);
		return 0;
	}
	// set ptr1 to the head in the list
	ptr1 = &pManager->airportList.head;
	// need to find were to insert the new airport
	ptr1 = L_insertSorted(&pManager->airportList, pPort, AirportCompareCode);
	if (!ptr1)
	{
		// TODO maybe need to free the list
		freeAirport(pPort);
		return 0;
	}
	return 1;
}

int  initAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	return initAirportNoCode(pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	Airport* toSearch = (Airport*)calloc(1, sizeof(Airport));
	if (!toSearch)
		return NULL;
	strcpy(toSearch->code, code);
	NODE* ptr = L_find(pManager->airportList.head.next, toSearch, AirportCompareCode);

	freeAirport(toSearch);

	if (!ptr) {
		return NULL;
	}
	return (Airport*)ptr->key;
}

int checkUniqeCode(const char* code, const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}


void	printAirports(const AirportManager* pManager)
{
	L_print(&pManager->airportList, printAirport);
}

void	freeManager(AirportManager* pManager)
{
	L_free(&pManager->airportList, freeAirport);
}

int hasXorMoreAirports(const AirportManager* pManager, int x) {

	int count = 0;
	NODE* ptr = pManager->airportList.head.next;
	if (!ptr)
		return 0;

	while (ptr && count < x) {
		count++;
		ptr = ptr->next;
	}

	if (count >= x) {
		return 1;
	}
	return 0;
}


int	saveManagerToFile(const AirportManager* pManager, const char* fileName) {
	FILE* file = fopen(fileName, "w");
	int res;
	if (!file) {
		printf("Error open file to write\n");
		return 0;
	}
	int count = L_count(&pManager->airportList);
	NODE* ptr = pManager->airportList.head.next;
	fprintf(file, "%d\n", count);

	while (ptr) {
		Airport* pPort = (Airport*)ptr->key;
		fprintf(file, "%s\n", pPort->name);
		fprintf(file, "%s\n", pPort->country);
		fprintf(file, "%s\n", pPort->code);
		ptr = ptr->next;
	}
	fclose(file);
}