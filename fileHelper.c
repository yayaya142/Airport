#include "fileHelper.h"



int writeStringToFile(FILE* file, const char* str) {
	if (!file) {
		return 0;
	}
	fprintf(file, "%s\n", str);
	return 1;
}

int writeStringTobinFile(FILE* file, const char* str) {
	if (!file) {
		return 0;
	}
	int len = (size_t)strlen(str) + 1;
	// write the length of the string
	if (fwrite(&len, sizeof(int), 1, file) != 1)
		return 0;
	// write the string
	if (fwrite(str, sizeof(char), len, file) != len)
		return 0;

	return 1;
}

char* readStringFromTextFile(FILE* file) {
	// allocate dynamic memory for the string make sure to use cautiously! 
	char tempStr[MAX_BUFFER_SIZE];
	if (!file) {
		return NULL;
	}

	if (fgets(tempStr, MAX_BUFFER_SIZE, file) == NULL) {
		return NULL;
	}
	tempStr[strcspn(tempStr, "\n")] = '\0'; // Remove newline character
	char* str = (char*)malloc(strlen(tempStr) + 1);
	strcpy(str, tempStr);
	return str;
}

char* readStringFromBinFile(FILE* file) {
	// allocate dynamic memory for the string make sure to use cautiously!
	if (!file) {
		return NULL;
	}
	int len;
	if (fread(&len, sizeof(int), 1, file) != 1) {
		return NULL;
	}
	char* str = (char*)malloc(len * sizeof(char));
	if (fread(str, sizeof(char), len, file) != len) {
		return NULL;
	}
	return str;
}