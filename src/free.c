#include "../includes/malloc.h"
void merge()
{
    struct block *curr, *prev;
    curr = freeList;
    while (curr && (curr->next) != NULL)
    {
        if ((curr->free) && (curr->next->free))
        {
            curr->size += (curr->next->size) + sizeof(struct block);
            curr->next = curr->next->next;
        }
        prev = curr;
        curr = curr->next;
    }
}

void free(void *ptr)
{
    if (!ptr)
    {
        return;
    }
    struct block *curr = ptr;
    --curr;

    curr->free = 1;
    if (curr->next && isLastBlock(curr->next))
    {
        curr->next = NULL;
    }
    merge();
}