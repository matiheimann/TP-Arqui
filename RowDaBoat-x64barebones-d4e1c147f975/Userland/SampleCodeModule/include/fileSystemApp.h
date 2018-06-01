#ifndef FILE_SYSTEM_APP_H
#define FILE_SYSTEM_APP_H

void fopen(char* filename);
void fclose(char* filename);
void fread(char* filename);
void fwrite(char* filename, char* text);
void fappend(char* filename, char* text);
void fileOpen(char* filename);
void fileClose(char* filename);
void fileRead(char* filename);
void fileWrite(char* filename, char* text);
void fileAppend(char* filename, char* text);

#endif