#include "fileSystemApp.h"
#include <stdlib.h>

void fileSystemApp()
{
	clearScreen();
	printf("Welcome to the file system app\n");
	int end = 0;
	while (!end) 
	{
		putchar('>');
		printf("Choose command: ");
		char command[100] = {0};
		scanf(command);
		int result = selectCommand(command);
		if(result != INVALID && result != HELP && result != EXIT && result != SHOW)
		{
			char filename[100] = {0};
			char text[100] = {0};
			printf(">Choose file: ");
			scanf(filename);
			if(result == WRITE || result == APPEND)
			{
				printf("Choose text: ");
				scanf(text);
			}
			executeCommand(result, filename, text);
		}
		else if(result == HELP)
		{
			help();
		}
		else if(result == EXIT)
		{
			end = 1;
		}
		else if(result == SHOW)
		{
			filesShow();
		}
		else
		{
			printf("Invalid operation\n");
		}
	}
	printf("----------Exiting file system app----------\n");
	exitProcess();
}

int selectCommand(char* command)
{
	if(strcmp(command, "Open") == 0)
	{
		return OPEN;
	}
	else if(strcmp(command, "Close") == 0)
	{
		return CLOSE;
	}
	else if(strcmp(command, "Read") == 0)
	{
		return READ;
	}
	else if(strcmp(command, "Write") == 0)
	{
		return WRITE;
	}
	else if(strcmp(command, "Append") == 0)
	{
		return APPEND;
	}
	else if(strcmp(command, "Help") == 0)
	{
		return HELP;
	}
	else if(strcmp(command, "Exit") == 0)
	{
		return EXIT;
	}
	else if(strcmp(command, "Show files") == 0)
	{
		return SHOW;
	}
	else if(strcmp(command, "Create") == 0)
	{
		return CREATE;
	}
	else if(strcmp(command, "Delete") == 0)
	{
		return DELETE;
	}
	return INVALID;
}

void executeCommand(int command, char* filename, char* text)
{
	if(command == OPEN)
	{
		fopen(filename);
	}
	else if(command == CLOSE)
	{
		fclose(filename);
	}
	else if(command == READ)
	{
		fread(filename);
	}
	else if(command == WRITE)
	{
		fwrite(filename, text);
	}
	else if(command == APPEND)
	{
		fappend(filename, text);
	}
	else if(command == CREATE)
	{
		fileCreate(filename);
	}
	else if(command == DELETE)
	{
		fileDelete(filename);
	}
}

void fopen(char* filename)
{
	fileOpen(filename);
}

void fclose(char* filename)
{
	fileClose(filename);
}

void fread(char* filename)
{
	fileRead(filename);
}

void fwrite(char* filename, char* text)
{
	fileWrite(filename, text);
}

void fappend(char* filename, char* text)
{
	fileAppend(filename, text);
}

void help()
{
	printf("Choose the name of the file and the operation you want to use.\n");
	printf("Create: create a new file.\n");
	printf("Open: opens a file, if it is not created it will create it.\n");
	printf("Show files: show every file\n");
	printf("Read: prints the content of the file.\n");
	printf("Write: write from the beggining of the file.\n");
	printf("Append: write from the last part that was writen before.\n");
	printf("Close: close the file.\n");
	printf("Delete: deletes the file\n");
	printf("Exit: going back to the shell\n");
}