#include "message.h"
#include "priorityBasedRoundRobin.h"
#include "process.h"

void asynchronousSend(msg)
{
  // mutex.lock()  es el mismo mutex que va a utilizar el proceso que recive el
  // mensaje

  // msg.src = sourcePID; se puede setear desde afuera
  // msg.dst = destinationPID;
  circularMsgBuffer tempBuffer;
  tempBuffer = map_buffer(msg.targetPID); // temporarily map destination's
                                          // buffer into sender process' address
                                          // space
  if (tempBuffer.size == MAXITEMS)
  { // if receiver buffer is full, block
    pushwaitqueue(msg.targetPID,
                  msg.sourcePID); // record this process in dst's sender queue
    block(msg.sourcePID);         //  hay que implementarlo
  }
  enqueueMessage(tempBuffer, msg.sourcePID);
  // funciones que hay que implementar isblocked y awake
  if (isblocked(msg.targetPID))
  {
    awake(msg.targetPID); // si el proceso destino esta bloqueado, hay que
                          // desperarlo
  }
  // unmap_buffer(); creo que es innecesario
  // mutex.unlock()
}

message asynchronousReceive()
{
  message tmp = NULL;
  // mutex.lock();
  // messageBuffer es la cola de mensajes del proceso que esta llamando al
  // receive
  // habria que pedir la messageBuffer
  if (messageBuffer.size == 0)
  {
    block(current_process); // se bloquea si no hay nada que esperar (busy
                            // waiting?)
  }
  tmp = pop(buff);
  while (topwaitqueue() != NULL)
  {
    awake(popwaitqueue()); // despertar el proceso que estaba esperando para
                           // enviar
  }
  // mutex.unlock();
  return (tmp);
}

message synchronousSend(msg)
{
  asynchronousSend(msg);          // se envia el mensaje
  return (asynchronousReceive()); // se espera a que conteste
}

message synchronousReceive()
{
  message tmp;
  tmp = asynchronousReceive(); // espera a recibir el mensaje
  asynchronousSend(tmp);       // contesta que lo recivio
}

// esta funcion deberia estar en process.c o roundrobin.c, debe devolver la
// lista circular de mensajes de cada processo
// el enunciado del TP dice que el identificador tiene que ser una cadena de
// caracteres, supongo que se puede usar el int del PID y pasarlo a char[]
circularMsgBuffer map_buffer(char* targetPID)
{
  // aca tiene que buscar el processo destino

  // hay que recorrer todos los processo hasta encontrar el que tenga el mismo
  // PID,
  // no se si esta bien recorrerlo asi
  // tambien falta la funcion stoi
  for (int i = priorityRings[0]->rear; i < priorityRings[0]->rear; i++)
  {
    if (priorityRings[0]->queue[i] == stoi(targetPID))
    {
      // retornar el ciruclarMsgBuffer del proceso
    }
  }

  for (int i = priorityRings[1]->rear; i < priorityRings[1]->rear; i++)
  {
    if (priorityRings[1]->queue[i] == stoi(targetPID))
    {
      // retornar el ciruclarMsgBuffer del proceso
    }
  }

  for (int i = priorityRings[2]->rear; i < priorityRings[2]->rear; i++)
  {
    if (priorityRings[2]->queue[i] == stoi(targetPID))
    {
      // retornar el ciruclarMsgBuffer del proceso
    }
  }
}
