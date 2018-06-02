#include "fileSystem.h"
#include "memoryManager.h"
#include <lib.h>
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
	memcpy(fd.filename, filename, stringlen(filename));
	fd.next = NULL;
	fd.charactersWriten = 0;
	fd.fileAdress = allocate(1);
	return fd;
}

void openFile(char* filename)
{
	fileAllocatorTable.first = addNode(filename, fileAllocatorTable.first);
	printInt(fileAllocatorTable.first);
	printChar('\n');
	printString(fileAllocatorTable.first->filename);
}

fileData* addNode(char* filename, fileData* current)
{
	if(current == NULL)
	{
		fileData fd = createFileData(filename);
		fileData* fds = &fd;
		return fds;
	}

	if(strcmp(filename, current->filename) == 0)
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

	if(strcmp(filename, current->filename) == 0)
	{
		deallocate(current->fileAdress);
		return current->next;
	}

	current->next = deleteNode(filename, current->next);

	return current;
}

fileData* getFile(char* filename, fileData* current)
{
	printString("\n");
	printInt(current);
	if(current == NULL)
	{
		return NULL;
	}

	if(strcmp(filename, current->filename) == 0)
	{
		return current;
	}

	return getFile(filename, current->next);
} 

void writeFile(char* filename, char* text)
{
	fileData* fd = getFile(filename, fileAllocatorTable.first);
	if(fd == NULL)
	{
		printString("The file does not exist\n");
		return;
	}
	fd->charactersWriten = 0;
	int i = 0;
	while(text[i] != 0)
	{
		i++;
		printInt(i);
		*(fd->fileAdress + i) = text[i];
		(fd->charactersWriten)++;
	}
}

void readFile(char* filename)
{
	fileData* fd = getFile(filename, fileAllocatorTable.first);
	if(fd == NULL)
	{
		printString("The file does not exist\n");
		return;
	}	
	int i = 0;
	for(i = 0; i < fd->charactersWriten; i++)
	{
		printChar(*(fd->fileAdress + i));
	}
}

void appendFile(char* filename, char* text)
{
	fileData* fd = getFile(filename, fileAllocatorTable.first);
	if(fd == NULL)
	{
		printString("The file does not exist\n");
		return;
	}
	int i = 0;
	while(text[i] != 0)
	{
		*(fd->fileAdress + fd->charactersWriten + i) = text[i];
		i++;
	}
}