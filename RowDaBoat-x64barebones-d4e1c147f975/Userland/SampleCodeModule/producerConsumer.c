#include "producerConsumer.h"
#include <stdlib.h>

static mutex *criticalZone;
static int messagesWithoutRead = 0;
static char *sharedBuffer[MAX_MESSAGES_TO_SEND];
static int index = 0;
static end = 0;

void initializeProdcons(int argc, char **argv)
{
	clear();
	end = 0;
	printf("PRODCONS DEMO\n");
	criticalZone = generateMutex("criticalZone");
	newProcess((void *)&producer, 0, NULL);
	newProcess((void *)&consumer, 0, NULL);
	while (!end) {
		printf(">");
		char command[2];
		scanf(command);
		printf("\n");
		if (strcmp(command, "c") == 0) {
			newProcess((void *)&consumer, 0, NULL);
		} else if (strcmp(command, "p") == 0) {
			newProcess((void *)&producer, 0, NULL);
		} else if (strcmp(command, "e") == 0) {
			end = 1;
		}
	}
	deleteMutex("criticalZone");
	printf("Exiting consumer\n");
	exitProcess();
}

void producer(int argc, char **argv)
{
	int i = 0;

	char *messages[4] = {"hola",  "como estas?", "chau",
			     "troca", "ok",	  "perdon"};
	while (!end) {
		while (i < 4) {
			lockMutex(criticalZone);
			if (MAX_MESSAGES_TO_SEND > messagesWithoutRead) {
				sharedBuffer[(index + messagesWithoutRead) %
					     MAX_MESSAGES_TO_SEND] =
				    messages[i];
				i++;
				messagesWithoutRead++;
			}
			unlockMutex(criticalZone);
		}
	}
	exitProcess();
}

void consumer(int argc, char **argv)
{
	while (!end) {
		while (messagesWithoutRead > 0) {
			lockMutex(criticalZone);
			printf("<Consumer(");
			printInt(getPid());
			printf("):");
			printf(sharedBuffer[index]);
			printf(">\n");
			index++;
			index %= MAX_MESSAGES_TO_SEND;
			messagesWithoutRead--;
			unlockMutex(criticalZone);
		}
	}
	exitProcess();
}