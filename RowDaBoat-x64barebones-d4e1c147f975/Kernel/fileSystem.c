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
		files[i].isOpen = 0;
	}
}

void createFile(char* filename)
{
	int indexToAllocate = -1;

	for(int i = 0; i < 100; i++)
	{
		if(stringlen(files[i].filename) == 0)
		{
			indexToAllocate = i;
		}
		else if(strcmp(files[i].filename, filename) == 0)
		{
			printString("The file already exists \n");
		}
	}

	memcpy(files[indexToAllocate].filename, filename, stringlen(filename));
	files[indexToAllocate].fileAdress = allocate(256);
	files[indexToAllocate].charactersWriten = 0;
	files[indexToAllocate].isOpen = 0;
}

void deleteFile(char* filename)
{
	for(int i = 0; i < 100; i++)
	{
		if(strcmp(files[i].filename, filename) == 0)
		{
			files[i].fileAdress[0] = 0;
			deallocate(files[i].fileAdress);
			files[i].filename[0] = 0;
			return;
		}
	}

	printString("The file does not exist \n");
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
			files[i].isOpen = 1;
			return;
		}
	}
	if(indexToAllocate != -1)
	{
		memcpy(files[indexToAllocate].filename, filename, stringlen(filename));
		files[indexToAllocate].fileAdress = allocate(256);
		files[indexToAllocate].charactersWriten = 0;
		files[indexToAllocate].isOpen = 1;			
	}
	else
	{
		printString("There is no more space to allocate a file and the file required is not created \n");
	}


}

void closeFile(char* filename)
{
	for(int i = 0; i < 100; i++)
	{
		if(strcmp(filename, files[i].filename) == 0)
		{
			files[i].isOpen = 0;
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
			if(files[i].isOpen)
			{
				printString((char*)(files[i].fileAdress));
				printString("\n");				
			}
			else
			{
				printString("The file must be opened to be read \n");
				return;
			}
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
			if(files[i].isOpen)
			{
				memcpy(files[i].fileAdress, text, stringlen(text));
				files[i].charactersWriten = stringlen(text);
				return;				
			}
			else
			{
				printString("The file must be opened to be written \n");
				return;
			}

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
			if(files[i].isOpen)
			{
				memcpy(files[i].fileAdress + files[i].charactersWriten, text, stringlen(text));
				files[i].charactersWriten += stringlen(text);
				return;
			}
			else
			{
				printString("The file must be opened to be written \n");
				return;
			}
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
			if(files[i].isOpen)
			{
				printString(" OPENED");
			}
			else
			{
				printString(" CLOSED");
			}
			printString("\n");
		}
	}
}