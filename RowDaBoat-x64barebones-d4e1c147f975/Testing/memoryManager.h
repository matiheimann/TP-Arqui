#include <stddef.h>

#define MEMORY_SIZE 4194304 //Memory size of 4MB
#define SMALLEST_BLOCK_SIZE 4096 //Page size of 4KB

typedef struct metadata
{
    unsigned char isAllocated : 1;
    unsigned char isLeft : 1;
    unsigned char order : 6;

}metadata;

void* allocate(size_t bytes);
int calculateBlockOrder(size_t bytes);
double logBase2(size_t number);
int jumpNextPosition(int position, int order);
void readMetadataFromPosition(int position, metadata* blockMetadata);
void initializeMemory(void* beginningOfMemory);
void deallocate(void* address);
void mergeBlocks(int leftPosition, int rightPosition, int order);
int isLeft(int position, int order);
int jumpPreviousPosition(int position, int order);
