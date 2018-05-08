#include "messageHolder.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {

  char* id1 = "id1";
  char* id2 = "id2";
  char* id3 = "id3";
  char* id4 = "id4";
  char* id5 = "id5";

  createMessageHolder(id1);
  createMessageHolder(id2);
  createMessageHolder(id3);
  createMessageHolder(id4);
  createMessageHolder(id5);

  messageHolder* m3 = retrieveMessageHolder("id3");
  printf("M3 id: %s\n", m3->id);
  printf("M3 mutex id: %d\n", m3->messageMutex->id);

  messageHolder* m1 = retrieveMessageHolder("id1");
  printf("M1 id: %s\n", m1->id);
  printf("M1 mutex id: %d\n", m1->messageMutex->id);

  messageHolder* m5 = retrieveMessageHolder("id5");
  printf("M5 id: %s\n", m5->id);
  printf("M5 mutex id: %d\n", m5->messageMutex->id);

  destroyMessageHolder(id1);
  destroyMessageHolder(id2);
  destroyMessageHolder(id3);
  destroyMessageHolder(id4);
  destroyMessageHolder(id5);

  messageHolder* m4 = retrieveMessageHolder("id4");
  if(m4 == NULL)
  {
    printf("M4 does not exist\n");
  }
}
