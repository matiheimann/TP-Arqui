#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdint.h>

typedef struct fileData fileData;

typedef struct fileData
{
	char filename[100];
	uint8_t* fileAdress;
	uint64_t charactersWriten;
	int isOpen;

}fileData;


void readFile(char* filename);
void writeFile(char* filename, char* text);
void appendFile(char* filename, char* text);
void openFile(char* filename);
void closeFile(char* filename);
fileData createFileData(char* filename);
void initializeFileSystem();
void showFiles();
void deleteFile(char* filename);
void createFile(char* filename);

#endif