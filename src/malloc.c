
#include "../includes/malloc.h"

void initialize()
{
    freeList = (void *)sbrk(2 * getpagesize());
    freeList->size = 0;
    freeList->free = 1;
    freeList->next = NULL;
}

int isLastBlock(struct block *block)
{
    if (block->next == NULL)
    {
        return 1;
    }
    return 0;
}

struct block *findLastBlock()
{
    struct block *current = freeList;
    while (isLastBlock(current) == 0)
    {
        current = current->next;
    }
    return current;
}
unsigned powerOfTwo(unsigned x)
{
    if (x <= 1)
        return 1;
    int power = 2;
    x--;
    while (x >>= 1)
        power <<= 1;
    return power;
}

void *incrementHeapIfNecessary(long incr, long lastUsedElementInTheHeap)
{
    ptrdiff_t difference = incr - ((long)sbrk(0) - lastUsedElementInTheHeap);

    if (difference > 0)
    {
        int sz = getpagesize();
        int numberOfDoublePages = difference / (2 * sz);
        if (difference % (2 * sz) != 0)
        {
            ++numberOfDoublePages;
        }
        int initial = sbrk(0);

        void *result = sbrk(2 * numberOfDoublePages * sz);

        return result;
    }
}

void *addBlock(size_t size)
{

    struct block *lastBlock = findLastBlock();
    if (incrementHeapIfNecessary(size + sizeof(struct block), lastBlock) == (void *)-1)
    {

        return NULL;
    }
    lastBlock->size = size;
    lastBlock->free = 0;

    ;
    void *result = lastBlock + 1;

    struct block *nouveauBlock = (void *)result + size;

    if (nouveauBlock)
    {
        nouveauBlock->free = 1;
        nouveauBlock->next = NULL;
        nouveauBlock->size = 0;
        lastBlock->next = (struct block *)nouveauBlock;
        return result;
    }

    return NULL;
}

void *findBestFitAndAllocate(size_t size)
{
    void *result = NULL;
    struct block *bestFit = NULL;
    struct block *current = freeList;
    while (isLastBlock(current) == 0)
    {
        if (current->free == 0 || current->size < size)
        {
            current = current->next;
            continue;
        }
        if (!bestFit)
        {
            bestFit = current;
            current = current->next;
            continue;
        }
        if (current->size == size)
        {
            result = (void *)(++current);
            return result;
        }
        if (current->size < bestFit->size)
        {
            bestFit = current;
        }
        current = current->next;
    }
    if (bestFit)
    {
        // split
        bestFit->free = 0;
        result = (void *)(++bestFit);
    }
    return result;
}

void *malloc(size_t noOfBytes)
{
    // Making sure next pointer is aligned in power of two
    int size = powerOfTwo(noOfBytes + sizeof(struct block));
    size -= sizeof(struct block);
    if (!(freeList))
    {
        initialize();
    }

    void *bestFit = findBestFitAndAllocate(size);
    if (bestFit)
    {
        return bestFit;
    }
    else
    {
        return addBlock(size);
    }
}
