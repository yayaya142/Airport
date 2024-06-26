#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"
#include "fileHelper.h"
#include <crtdbg.h> // TODO: remove before release



typedef enum {
	eNotSorted, eSortByOrigin, eSortByDest, eSortByDate, eNofSortTypes
} eSortType;

static const char* sortTypeStr[eNofSortTypes] = { "None", "Source Code", "Dest Code", "Date" };

typedef struct
{
	char* name;
	int			flightCount;
	Flight** flightArr;
	int			planeCount;
	Plane* planeArr;
	eSortType	sortType;
}Airline;

void	initAirline(Airline* pComp);
int		addFlight(Airline* pComp, const AirportManager* pManager);
int		addPlane(Airline* pComp);
Plane* FindAPlane(Airline* pComp);
void	printCompany(const Airline* pComp);
void	printFlightArr(Flight** arr, int size);
void	printPlanesArr(Plane* arr, int size);
void	doPrintFlightsWithPlaneType(const Airline* pComp);
void	freeFlightArr(Flight** arr, int size);
void	freePlanes(Plane* arr, int size);
void	freeCompany(Airline* pComp);
void sortFlightsByDate(Airline* pComp);
void sortFlightsByDest(Airline* pComp);
void sortFlightsByOrigin(Airline* pComp);
void sortFlight(Airline* pComp);
Flight* findFlight(const Airline* pComp);
int saveAirlineToFile(const Airline* pComp, const char* fileName);
int initAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName);
#endif

