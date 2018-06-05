#include "fileSystem.h"
#include "memoryManager.h"
#include <lib.h>
#include <videoDriver.h>

static fileData files[100];

void initializeFileSystem()
{
	for(int i = 0; i < 100; i++)
	{
		files[i].filename[0] = 0;
		files[i].fileAdress = NULL;
		files[i].charactersWriten = 0;
	}
}

void openFile(char* filename)
{
	int indexToAllocate = -1;

	for(int i = 0; i < 100; i++)
	{
		if(stringlen(files[i].filename) == 0)
		{
			indexToAllocate = i;
		}
		else if(strcmp(filename, files[i].filename) == 0)
		{
			return;
		}
	}

	if(indexToAllocate == -1)
	{
		printString("There is no space to allocate a new file\n");
		return;
	}

	memcpy(files[indexToAllocate].filename, filename, stringlen(filename));
	files[indexToAllocate].fileAdress = allocate(256);
	files[indexToAllocate].charactersWriten = 0;

}

void closeFile(char* filename)
{
	for(int i = 0; i < 100; i++)
	{
		if(strcmp(filename, files[i].filename) == 0)
		{
			files[i].filename[0] = 0;
			deallocate(files[i].fileAdress);
			return;
		}
	}
	printString("File does not exist\n");
}

void readFile(char* filename)
{
	for(int i = 0; i < 100; i++)
	{
		if(strcmp(filename, files[i].filename) == 0)
		{
			printString(files[i].fileAdress);
			printString("\n");
			return;
		}
	}

	printString("File does not exist\n");
}

void writeFile(char* filename, char* text)
{
	for(int i = 0; i < 100; i++)
	{
		if(strcmp(filename, files[i].filename) == 0)
		{
			memcpy(files[i].fileAdress, text, stringlen(text));
			files[i].charactersWriten = stringlen(text);
			return;
		}
	}

	printString("File does not exist\n");
}

void appendFile(char* filename, char* text)
{
	for(int i = 0; i < 100; i++)
	{
		if(strcmp(filename, files[i].filename) == 0)
		{
			memcpy(files[i].fileAdress + files[i].charactersWriten, text, stringlen(text));
			files[i].charactersWriten += stringlen(text);
			return;
		}
	}

	printString("File does not exist\n");	
}

void showFiles()
{
	for(int i = 0; i < 100; i++)
	{
		if(stringlen(files[i].filename) != 0)
		{
			printString("-");
			printString(files[i].filename);
			printString("\n");
		}
	}
}