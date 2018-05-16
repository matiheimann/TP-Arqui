#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h>

#define MEMORY_SIZE 4194304      // Memory size of 4MB
#define SMALLEST_BLOCK_SIZE 4096 // Page size of 4KB

typedef struct metadata
{
  unsigned char isAllocated : 1;
  unsigned char isLeft : 1;
  unsigned char order : 6;

} metadata;

void* allocate(size_t bytes);
int calculateBlockOrder(size_t bytes);
int logBase2(size_t number);
int pow(int base, int power);
int jumpNextPosition(int position, int order);
void readMetadataFromPosition(int position, metadata* blockMetadata);
void initializeMemory(void* beginningOfMemory);
void deallocate(void* address);
void mergeBlocks(int leftPosition, int rightPosition, int order);
int isLeft(int position, int order);
int jumpPreviousPosition(int position, int order);
void subdivideBlock(int position, metadata* positionBlockMetadata);

#endif
