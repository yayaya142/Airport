#ifndef __FILE_HELPER__
#define __FILE_HELPER__

#include <stdio.h>
#include <crtdbg.h> // TODO: remove before release
#include "General.h"

#define MAX_BUFFER_SIZE 256

int writeStringToFile(FILE* file, const char* str);
int writeStringTobinFile(FILE* file, const char* str);
char* readStringFromTextFile(FILE* file);
char* readStringFromBinFile(FILE* file);






#endif 
