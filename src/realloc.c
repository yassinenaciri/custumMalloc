#include "../includes/malloc.h"

void myMemCpy(void *dest, void *src, size_t n)
{

    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    for (int i = 0; i < n; i++)
        cdest[i] = csrc[i];
}

void *createNewBlockAndCopy(void *ptr, size_t newSize, size_t sizeToCopy)
{
    void *p;

    p = malloc(newSize);
    if (p == NULL)
    {
        return p;
    }

    if (ptr != NULL)
    {

        myMemCpy(p, ptr, sizeToCopy);

        free(ptr);
    }

    return p;
}

void *realloc(void *ptr, size_t newSize)
{
    struct block *associatedBlock = (struct block *)ptr;
    --associatedBlock;
    if (!associatedBlock || !associatedBlock->size)
    {
        return NULL;
    }
    else if (newSize < associatedBlock->size)
    {
        // split
        return ptr; // tocheck
    }
    else if (newSize == associatedBlock->size)
    {
        return ptr;
    }
    else if (isLastBlock(associatedBlock->next))
    {
        associatedBlock->size = newSize;
        incrementHeapIfNecessary(newSize + sizeof(struct block), (int)associatedBlock);

        struct block *nouveauBlock = (void *)ptr + newSize;

        nouveauBlock->free = 1;
        nouveauBlock->next = NULL;
        nouveauBlock->size = 0;
        associatedBlock->next = (struct block *)nouveauBlock;
        return ptr;
    }
    else
    {
        return createNewBlockAndCopy(ptr, newSize, associatedBlock->size);
    }
}