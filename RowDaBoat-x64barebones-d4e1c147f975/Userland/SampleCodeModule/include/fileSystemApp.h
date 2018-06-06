#ifndef FILE_SYSTEM_APP_H
#define FILE_SYSTEM_APP_H

#define INVALID -1
#define OPEN 0
#define CLOSE 1
#define READ 2
#define WRITE 3
#define APPEND 4
#define HELP 5
#define EXIT 6
#define SHOW 7
#define CREATE 8
#define DELETE 15

void fileSystemApp();
void help();
void fopen(char* filename);
void fclose(char* filename);
void fread(char* filename);
void fwrite(char* filename, char* text);
void fappend(char* filename, char* text);
void executeCommand(int command, char* filename, char* text);
int selectCommand(char* command);

extern void fileOpen(char* filename);
extern void fileClose(char* filename);
extern void fileRead(char* filename);
extern void fileWrite(char* filename, char* text);
extern void fileAppend(char* filename, char* text);
extern void filesShow();
extern void fileCreate(char* filename);
extern void fileDelete(char* filename);

#endif