#ifndef FILE_SYSTEM_APP_H
#define FILE_SYSTEM_APP_H

void fileSystemApp();
void help();
void fopen(char* filename);
void fclose(char* filename);
void fread(char* filename);
void fwrite(char* filename, char* text);
void fappend(char* filename, char* text);

extern void fileOpen(char* filename);
extern void fileClose(char* filename);
extern void fileRead(char* filename);
extern void fileWrite(char* filename, char* text);
extern void fileAppend(char* filename, char* text);

#endif