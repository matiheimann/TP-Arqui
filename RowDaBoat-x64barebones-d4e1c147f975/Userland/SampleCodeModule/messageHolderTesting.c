#include <messageHolderTesting.h>
#include <stdlib.h>

void messageHolderTest()
{
  /*generateAndGetMessageHolderTest();
  printf("\n");
  deleteMessageHolderTest();
  printf("\n");*/
  sendAndReceiveTest();
  //printf("\n");
}

void generateAndGetMessageHolderTest()
{
  printf("Generate and get message holder test:\n");

  messageHolder* m1 = generateMessageHolder("m1");
  messageHolder* m2 = getMessageHolder("m1");

  printf("Getted message holder id: ");
  printf(m2->id);
  printf("\n");

  printf("Expected getted message holder id: ");
  printf(m1->id);

  deleteMessageHolder(m1->id);
  deleteMessageHolder(m2->id);

  printf("\n");
}

void deleteMessageHolderTest()
{

  printf("Delete message holder test\n");

  generateMessageHolder("m1");
  deleteMessageHolder("m1");

  messageHolder* retrieved = getMessageHolder("m1");

  if(retrieved == NULL)
  {
    printf("Message holder succesfully deleted\n");
  }

  printf("\n");
}

void sendAndReceiveTest()
{
  printf("_______SEND AND RECEIVE TEST______\n");
  generateMessageHolder("sendAndReceiveTest");
  newProcess((void*)&sender, 0, NULL);
  newProcess((void*)&receiver, 0, NULL);
}

void sender(int argc, char** argv)
{
  messageHolder* m1 = getMessageHolder("sendAndReceiveTest");
  printf("Sending hola...\n");
  send(m1, "hola", 4);
  while(1);
}

void receiver(int argc, char** argv)
{
  char buff[4];

  messageHolder* m2 = getMessageHolder("sendAndReceiveTest");

  printf("Receiving...\n");
  receive(m2, buff, 4);

  printf("MESSAGE RECEIVED: ");
  printf(buff);
  printf("\n");

  while(1);
}

void p1()
{
  printf("\nHello from ");
  printInt(getPid());
  printf("\n");
  exitProcess();
}
