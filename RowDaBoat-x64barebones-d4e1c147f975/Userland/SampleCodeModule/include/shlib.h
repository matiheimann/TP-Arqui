#ifndef SHLIB_H
#define SHLIB_H

void printWelcomeMessage();
void printHelp(int argc, char **argv);
int execute(char *command);
void displayTimeDataProcess(int argc, char **argv);
void graphPlotterProcess(int argc, char **argv);
void printWelcomeMessageProcess(int argc, char **argv);
void printHelpProcess(int argc, char **argv);
void psProcess(int argc, char **argv);

#endif
