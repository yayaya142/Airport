#ifndef __PLANE__
#define __PLANE__
#include <crtdbg.h> // TODO: remove before release


#define CODE_LENGTH 8
#define MIN_SN 1
#define MAX_SN 9999

typedef enum {
	eCommercial, eCargo, eMilitary, eNofPlaneTypes
} ePlaneType;

static const char* PlaneTypeStr[eNofPlaneTypes]
= { "Commercial", "Cargo", "Military" };


typedef struct
{
	int			serialNum;
	ePlaneType	type;
}Plane;

void			initPlane(Plane* pPlane, Plane* planeArr, int planeCount);
ePlaneType		getPlaneType();
const char* GetPlaneTypeStr(int type);
int				getPlaneSN(Plane* planeArr, int planeCount);
Plane* findPlaneBySN(Plane* planeArr, int count, int sn);
int				isSerialNumUnique(Plane* planeArr, int planeCount, int num);
void	printPlane(const void* plane);
void			freePlane(Plane* pPlane);
int savePlaneArrToBinFile(FILE* file, Plane* planeArr, int planeCount);
int savePlaneToBinFile(FILE* file, Plane* pPlane);
int savePlaneSerialNumberBinFile(FILE* file, Plane* pPlane);
Plane readPlaneSerialNumberBinFile(FILE* file, const Plane* planeArr, int planeCount);
Plane readPlaneFromBinFile(FILE* file);
Plane* readPlaneArrFromBinFile(FILE* file, int* restoredCount);

#endif