#include "../includes/malloc.h"

void *my_memset(void *s, int c, unsigned int len)
{
    unsigned char *p = s;
    while (len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}

void *calloc(size_t num, size_t size)
{
    void *p;
    size_t sizeInBytes;
    sizeInBytes = num * size;

    p = malloc(sizeInBytes);

    if (p != NULL)
    {
        my_memset(p, 0, sizeInBytes);
    }
    return p;
}