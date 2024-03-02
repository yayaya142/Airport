#include "exe.h"


#define MANAGER_FILE_NAME_SRC "airport_authority.txt"
#define AIRLINE_FILE_NAME_SRC "airline.bin"

//#define MANAGER_FILE_NAME_DST "airport_authority_out.txt"
//#define AIRLINE_FILE_NAME_DST "airline_out.bin"

#define MANAGER_FILE_NAME_DST "airport_authority.txt"
#define AIRLINE_FILE_NAME_DST "airline.bin"

typedef enum
{

	eAddAirport, eAddPlane, eAddFlight, ePrintCompany, ePrintAirports,
	ePrintFlightsPlaneType, eSortFlight, eFindFlight, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Airport","Add Plane","Add Flight",
								"Print Airline", "Print all Airports",
								"Print all flights with plane type", "Sort Flight", "Find Flight" };




int manualTest() {
	AirportManager	manager;
	Airline			company;

	initManagerAndAirline(&manager, &company);

	int option;
	int stop = 0;


	do
	{
		option = menu();
		switch (option)
		{
		case eAddPlane:
			if (!addPlane(&company))
				printf("Error adding plane\n");
			break;

		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;

		case ePrintFlightsPlaneType:
			doPrintFlightsWithPlaneType(&company);
			break;

		case eSortFlight:
			sortFlight(&company);
			break;

		case eFindFlight:
			findFlight(&company);
			break;

		case EXIT:
			// save airline and manager to file
			if (!saveManagerToFile(&manager, MANAGER_FILE_NAME_DST) || !saveAirlineToFile(&company, AIRLINE_FILE_NAME_DST)) {
				printf("Cannot save files");
			}
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	freeManager(&manager);
	freeCompany(&company);

	return 1;
}


int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}


int initManagerAndAirline(AirportManager* pManager, Airline* pCompany) {
	// try to init manager from file
	if (!initManager(pManager, MANAGER_FILE_NAME_SRC)) {
		printf("Error init manager\n");
		return 0;
	}
	// try to init airline from file
	if (initAirlineFromFile(pCompany, pManager, AIRLINE_FILE_NAME_SRC)) {
		// success init from file
		return 1;
	}
	// if init manager sycceeded but init airline failed
	initAirline(pCompany);

	return 1;
}