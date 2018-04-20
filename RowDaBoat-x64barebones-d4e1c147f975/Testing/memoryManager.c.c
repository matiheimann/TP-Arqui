#include <stdio.h>

void* alloc(size_t bytes);
int calculateBlockOrder(size_t bytes);
double log2(size_t number);

unsigned char memory[4194304];

typedef struct metadata
{
    unsigned char isAllocated : 1;
    unsigned char isLeft : 1;
    unsigned char order : 6;

}metadata;

void initializeMemory()
{
    memset(memory, 0, 4194304);
    memset(memory, 42, 1);
}

void* alloc(size_t bytes)
{
    if(bytes > 4194303)
    {
        return null;
    }

    int position = 0;
    int orderOfBlockRequired = calculateBlockOrder(bytes);

    metadata * currentBlockMetadata;

    while(position < 4194304)
    {
        readMetadata(position, currentBlockMetadata);

        if(orderOfBlockRequired <= currentBlockMetadata->order)
        {
            if(currentBlockMetadata->isAllocated)
            {
                position = jumpNextPosition(position, currentBlockMetadata->order);
            }
            else if(orderOfBlockRequired == currentBlockMetadata->order)
            {
                memory[position]++;
                position++;
                return (void*) (&memory + position);
            }
            else
            {
                int buddy = jumpNextPosition(position, currentBlockMetadata->order - 1);

                char metadataLeft = 2;
                char metadataRight = 0;

                metadataLeft += ((currentBlockMetadata->order - 1) * 4);
                metadataRight += ((currentBlockMetadata->order - 1) * 4);

                memory[position] = metadataLeft;
                memory[buddy] = metadataRight;
            }
        }

        else
        {
            position = jumpNextPosition(position, orderOfBlockRequired);
        }

    }

    return null;

}

int jumpNextPosition(int position, int order)
{
    position += (int)(pow(2, order + 12));
    return position;
}

void readMetadata(int position, metadata* blockMetadata)
{
    memset(blockMetadata, memory[position], 1);
}

int calculateBlockOrder(size_t bytes)
{
    if(bytes < 4096)
    {
        return 0;
    }

    return floor(log2(bytes) - log2(4096)) + 1;
}

double log2(size_t number)
{
    return log(number)/log(2);
}