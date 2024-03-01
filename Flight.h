#ifndef __FLIGHT__
#define __FLIGHT__

#include "AirportManager.h"
#include "Date.h"
#include "Plane.h"
#include <crtdbg.h> // TODO: remove before release


typedef struct
{
	char	sourceCode[IATA_LENGTH + 1];
	char	destCode[IATA_LENGTH + 1];
	Plane	flightPlane;
	Date	date;
}Flight;

void	initFlight(Flight* pFlight, Plane* thePlane, const AirportManager* pManager);
int		isFlightFromSourceAirport(const Flight* pFlight, const char* code);
int		isFlightToDestAirport(const Flight* pFlight, const char* code);
void	printFlight(const Flight* pFlight);
void printFlightWrapper(const void* flight);
void freeFlight(void* flight);
Airport* setAirportToFlight(const AirportManager* pManager, const char* msg);
int		isPlaneTypeInFlight(const Flight* pFlight, ePlaneType type);
int compareFlightByDate(const void* pFlight1, const void* pFlight2);
int compareFlightByOriginCode(const void* pFlight1, const void* pFlight2);
int compareFlightByDestinationCode(const void* pFlight1, const void* pFlight2);
#endif
