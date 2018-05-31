#include "fileSystem.h"
#include "memoryManager.h"
#include <videoDriver.h>

static fileTable fileAllocatorTable;

void initializeFileSystem()
{
	fileAllocatorTable = createTable();
}

fileTable createTable()
{
	fileTable ft;
	ft.first = NULL;
	return ft;
}

fileData createFileData(char* filename)
{
	fileData fd;
	fd.filename = filename;
	fd.next = NULL;
	fd.charactersWriten = 0;
	fd.fileAdress = allocate(4095);
	return fd;
}

void openFile(char* filename)
{
	addToTable(filename, &fileAllocatorTable);
}

void addToTable(char* filename, fileTable* table)
{
	table->first = addNode(filename, table->first);
}

fileData* addNode(char* filename, fileData* current)
{
	if(current == NULL)
	{
		fileData fd = createFileData(filename);
		return &fd;
	}

	if(current->filename == filename)
	{
		return current;
	}
	current->next = addNode(filename, current->next);
	return current;
}

void closeFile(char* filename)
{
	deleteFromTable(filename, &fileAllocatorTable);
}

void deleteFromTable(char* filename, fileTable* table)
{
	table->first = deleteNode(filename, table->first);
}

fileData* deleteNode(char* filename, fileData* current)
{
	if(current == NULL)
	{
		return NULL;
	}

	if(current->filename == filename)
	{
		deallocate(current->fileAdress);
		return current->next;
	}

	current->next = deleteNode(filename, current->next);

	return current;
}

fileData* getFile(char* filename, fileData* current)
{
	if(current == NULL)
	{
		return NULL;
	}

	if(filename == current->filename)
	{
		return current;
	}

	return getFile(filename, current->next);
} 

void writeFile(char* filename, char* text)
{
	fileData* fd = getFile(filename, fileAllocatorTable.first);
	fd->charactersWriten = 0;
	int i = 0;
	while(text[i] != 0)
	{
		*(fd->fileAdress + i) = text[i];
		(fd->charactersWriten)++;
	}
	return;
}

void readFile(char* filename)
{
	fileData* fd = getFile(filename, fileAllocatorTable.first);
	int i = 0;
	for(i = 0; i < fd->charactersWriten; i++)
	{
		printChar((char)*(fd->fileAdress + i));
	}
	return;
}