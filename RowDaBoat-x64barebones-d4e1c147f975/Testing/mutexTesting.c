#include "mutex.h"
#include <stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

//Ejemplo de la siguiente pagina: https://www.thegeekstuff.com/2012/05/c-mutex-examples/?refcom
//Resuelto con la implementacion nuestra de mutexes

pthread_t tid[2];
int counter;
mutex* mutexLock;

void* doSomeThing(void *arg)
{
    lock(mutexLock);

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);

    for(i=0; i<(0xFFFFFFFF);i++);

    printf("\n Job %d finished\n", counter);

    unlock(mutexLock);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;

    mutexLock = createMutex(1);

    if (mutexLock == NULL)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    destroyMutex(1);

    return 0;
}
