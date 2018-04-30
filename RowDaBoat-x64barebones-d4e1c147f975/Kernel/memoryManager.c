#include <string.h>
#include <videoDriver.h>
#include "include/memoryManager.h"

static char* memory;

void initializeMemory(void* beginningOfMemory)
{
    memory = (char*)beginningOfMemory;
    memset(memory, 0, MEMORY_SIZE);
    memset(memory, 42, 1);
}

void* allocate(size_t bytes)
{
    if(bytes >= MEMORY_SIZE)
    {
        printString("Error, not enough memory\n");
        return NULL;
    }

    int position = 0;
    int orderOfBlockRequired = calculateBlockOrder(bytes);

    unsigned char c = 0;
    metadata * currentBlockMetadata = memset(&c, 0, 1);

    while(position < MEMORY_SIZE)
    {
        readMetadataFromPosition(position, currentBlockMetadata);

        if(orderOfBlockRequired <= currentBlockMetadata->order)
        {
            if(currentBlockMetadata->isAllocated)
            {
                position = jumpNextPosition(position, currentBlockMetadata->order);
            }
            else if(orderOfBlockRequired == currentBlockMetadata->order)
            {
                memory[position]++; //Allocated bit set to 1
                position++; //Position to return after metadata block
                return (void*) (memory + position);
            }
            else
            {
                subdivideBlock(position, currentBlockMetadata);
            }
        }

        else
        {
            position = jumpNextPosition(position, orderOfBlockRequired);
        }

    }

    printString("Error, no more memory available\n");
    return NULL;

}

void deallocate(void* address)
{
    if(address <= (void*)memory || (address > (void*)memory + MEMORY_SIZE))
    {
        printString("Error, invalid memory adress\n");
        return;
    }

    int position = address - (void*)memory - 1; //Metada block from corresponding adress

    if(position % SMALLEST_BLOCK_SIZE != 0 || memory[position] % 2 == 0) //Check if is a valid metadata block position
    {                                                                    // and if occupied position
        return;
    }

    unsigned char c1 = 0;
    unsigned char c2 = 0;
    metadata * metadata1 = memset(&c1, 0, 1);
    metadata * metadata2 = memset(&c2, 0, 1);

    memory[position] -= 1;

    while(position >= 0 && position < MEMORY_SIZE)
    {
        readMetadataFromPosition(position, metadata1);
        if(metadata1->isLeft)
        {
            int positionBuddy = jumpNextPosition(position, metadata1->order);

            if(positionBuddy < 0 || positionBuddy >= MEMORY_SIZE)
            {
                return;
            }

            readMetadataFromPosition(positionBuddy, metadata2);

            if(metadata2->isAllocated || metadata1->order != metadata2->order)
            {
                return;
            }

            mergeBlocks(position, positionBuddy, metadata1->order);

        }
        else
        {
            int positionBuddy = jumpPreviousPosition(position, metadata1->order);

            if(positionBuddy < 0 || positionBuddy >= MEMORY_SIZE)
            {
                return;
            }

            readMetadataFromPosition(positionBuddy, metadata2);

            if(metadata2->isAllocated || metadata1->order != metadata2->order)
            {
                return;
            }

            mergeBlocks(positionBuddy, position, metadata1->order);
        }
    }

}

void subdivideBlock(int position, metadata* positionBlockMetadata)
{
    int buddy = jumpNextPosition(position, positionBlockMetadata->order - 1);

    char metadataLeft = 2;
    char metadataRight = 0;

    metadataLeft += ((positionBlockMetadata->order - 1) * 4);
    metadataRight += ((positionBlockMetadata->order - 1) * 4);

    memory[position] = metadataLeft;
    memory[buddy] = metadataRight;
}

void mergeBlocks(int leftPosition, int rightPosition, int order)
{
    char newMetadata = 4 * (order + 1); // Set order field of metadata block

    if(isLeft(leftPosition, order))
    {
        newMetadata += 2; //Set left field of metadata block to 1
    }

    memory[rightPosition] = 0; //Clear metadata on right position

    memory[leftPosition] = newMetadata; 
}

int isLeft(int position, int order)
{
    return (position % (int)(SMALLEST_BLOCK_SIZE * pow(2, order + 1))== 0) ? 1 : 0;
}

int jumpNextPosition(int position, int order)
{
    position += (int)(pow(2, order + 12));
    return position;
}

int jumpPreviousPosition(int position, int order)
{
    position -= (int)(pow(2, order + 12));
    return position;
}

void readMetadataFromPosition(int position, metadata* blockMetadata)
{
    memset(blockMetadata, memory[position], 1);
}

int calculateBlockOrder(size_t bytes)
{
    if(bytes < SMALLEST_BLOCK_SIZE)
    {
        return 0;
    }

    return (logBase2(bytes) - logBase2(SMALLEST_BLOCK_SIZE)) + 1;
}

int logBase2(size_t number)
{
    int result = 0;

    while(number >= 2)
    {
        result++;
        number/= 2;
    }
    return result;
}

int pow(int base, int power) 
{
    int result = 1;
    int i;

    for(i=0; i<power; i++)
    {
        result *= base;
    }

    return result;
}