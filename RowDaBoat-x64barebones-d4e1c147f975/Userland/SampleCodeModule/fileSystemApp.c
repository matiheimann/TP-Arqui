#include "fileSystemApp.h"
#include <stdlib.h>

void fileSystemApp()
{
	clearScreen();
	printf("Welcome to the file system app\n");
	fopen("File 1");
	fwrite("File 1", "123");
	printf("asd1\n");	
	fappend("File 1", "456");
	printf("File 1\n");
	fread("File 1");
	printf("asd3\n");
	exitProcess();
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
	printf("Open: opens a file, if it is not created it will create it\n");
	printf("Read: prints the content of the file\n");
	printf("Write: write from the beggining of the file.\n");
	printf("Append: write from the last part that was writen before\n");
	printf("Close: close and deletes the file\n");
}