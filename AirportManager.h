#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__
#include <crtdbg.h> // TODO: remove before release

#include "Airport.h"
#include "listGen.h"
typedef struct
{
	LIST 	 airportList;
}AirportManager;

int		initManager(AirportManager* pManager);
int		addAirport(AirportManager* pManager);
int		initAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
int		checkUniqeCode(const char* code, const AirportManager* pManager);
void	printAirports(const AirportManager* pManager);
void	freeManager(AirportManager* pManager);
int hasXorMoreAirports(const AirportManager* pManager, int x);
#endif