﻿#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Airport.h"
#include "General.h"

#define SEP_CHAR '_'

int	isSameAirport(const Airport* pPort1, const Airport* pPort2)
{
	if (!pPort1 || !pPort2)
		return 0;
	if (strcmp(pPort1->code, pPort2->code) == 0)
		return 1;

	return 0;
}

int	isAirportCode(const Airport* pPort1, const char* code)
{
	if (!pPort1)
		return 0;
	if (strcmp(pPort1->code, code) == 0)
		return 1;
	return 0;
}

int AirportCompareCode(const void* pPort1, const void* pPort2) {
	if (!pPort1 || !pPort2) {
		return -1;
	}


	const Airport* port1 = (const Airport*)pPort1;
	const Airport* port2 = (const Airport*)pPort2;
	return (strcmp(port1->code, port2->code));
}


int	initAirportNoCode(Airport* pPort)
{
	if (!getAirportName(pPort))
		return 0;
	pPort->country = getStrExactName("Enter airport country");
	if (!pPort->country)
		return 0;
	return 1;
}

void	printAirport(const void* pPort)
{
	if (!pPort)
	{
		printf("Error airport is NULL\n");
		return;
	}
	const Airport* pAirport = (const Airport*)pPort;

	printf("Airport name:%-20s\t", pAirport->name);
	printf("Country: %-20s\t Code:%s\n", pAirport->country, pAirport->code);

}


int	getAirportName(Airport* pPort)
{
	char temp[255];
	char** wordsArray = NULL;
	int totalLength = 0;
	int count = 0;

	while (count == 0)
	{
		printf("Enter airport name\n");
		myGets(temp, MAX_STR_LEN);
		wordsArray = splitCharsToWords(temp, &count, &totalLength);
	}
	pPort->name = allocateRightLength(wordsArray, count, totalLength);
	if (!pPort->name)
		return 0;

	if (count == 1)
		changeNameOneWord(pPort->name, wordsArray[0]);
	else
		changeName(pPort->name, count, wordsArray);

	//clean temp data
	for (int i = 0; i < count; i++)
		free(wordsArray[i]);
	free(wordsArray);
	return 1;
}

char* allocateRightLength(char** wordsArray, int count, int totalLength)
{
	if (count == 1)
		totalLength += (int)strlen(wordsArray[0]);
	else {
		if (count % 2 == 0)
			totalLength += (count - 1) * 2 + 1;
		else
			totalLength += count;
	}

	char* name = (char*)calloc(totalLength, sizeof(char));
	if (!name)
	{
		for (int i = 0; i < count; i++)
			free(wordsArray[i]);
		free(wordsArray);
		return NULL;
	}

	return name;
}

void changeNameOneWord(char* name, const char* word)
{
	int len = (int)strlen(word);
	int index = 0;
	for (int i = 0; i < len - 1; i++)
	{
		name[index++] = toupper(word[i]);
		name[index++] = SEP_CHAR;
	}

	name[index] = toupper(word[len - 1]);

}

void changeName(char* name, int count, char** wordsArray)
{
	for (int i = 0; i < count; i++)
	{
		wordsArray[i][0] = toupper(wordsArray[i][0]);
		strcat(name, wordsArray[i]);
		if (i != count - 1) //not last
		{
			strcat(name, " ");
			if (count % 2 == 0)
				strcat(name, " ");
		}
	}

}

void getAirportCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter airport code  - %d UPPER CASE letters\t", IATA_LENGTH);
		myGets(temp, MAX_STR_LEN);
		if (strlen(temp) != IATA_LENGTH)
		{
			printf("code should be %d letters\n", IATA_LENGTH);
			ok = 0;
		}
		else {
			for (int i = 0; i < IATA_LENGTH; i++)
			{
				if (isupper(temp[i]) == 0)
				{
					printf("Need to be upper case letter\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);

	strcpy(code, temp);
}

void	freeAirport(void* pPort)
{
	Airport* pAirport = (Airport*)pPort;
	if (!pPort)
		return;
	free(pAirport->name);
	free(pAirport->country);
	free(pPort);
}


void writeAirportToFile(FILE* file, const Airport* pPort) {
	fprintf(file, "%s\n", pPort->name);
	fprintf(file, "%s\n", pPort->country);
	fprintf(file, "%s\n", pPort->code);
}


int readAirportFromFile(FILE* file, Airport* pPort) {
	char temp[MAX_STR_LEN];
	if (!pPort)
		return 0;
	// read name
	do {
		readStringFromTextFile(file, temp, MAX_STR_LEN);
	} while (strlen(temp) < 2);
	pPort->name = getDynStr(temp);
	if (!pPort->name) {
		return 0;
	}
	// read country
	do {
		readStringFromTextFile(file, temp, MAX_STR_LEN);
	} while (strlen(temp) < 2);
	pPort->country = getDynStr(temp);
	if (!pPort->country) {
		free(pPort->name);
		return 0;
	}
	// read code
	fscanf(file, "%s", pPort->code);
	return 1;

}
