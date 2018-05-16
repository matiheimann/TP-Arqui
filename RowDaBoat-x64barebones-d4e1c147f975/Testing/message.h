#define MESSAGE_SIZE 256

typedef struct message {
	char *sourcePID;
	char *targetPID;
	char[MESSAGE_SIZE] body;
} message;

void asynchronousSend(msg);
message asynchronousReceive();
message synchronousSend(msg);
message synchronousReceive();
