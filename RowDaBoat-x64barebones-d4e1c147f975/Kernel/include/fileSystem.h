#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdint.h>

typedef struct fileData fileData;

typedef struct fileData
{
	char* filename;
	uint64_t* fileAdress;
	uint64_t charactersWriten;
	fileData* next;

}fileData;

typedef struct fileTable
{
	fileData* first;

}fileTable;


void readFile(char* filename);
void writeFile(char* filename, char* text);
void appendFile(char* filename, char* text);
void openFile(char* filename);
void closeFile(char* filename);
void addToTable(char* filename, fileTable* table);
void deleteFromTable(char* filename, fileTable* table);
fileTable createTable();
fileData createFileData(char* filename);
void initializeFileSystem();
fileData* addNode(char* filename, fileData* current);
fileData* deleteNode(char* filename, fileData* current);
fileData* getFile(char* filename, fileData* current);

#endif