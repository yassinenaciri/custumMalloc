#include "../includes/malloc.h"

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    size_t sizeInBytes;
    sizeInBytes = nmemb * size;

    return realloc(ptr, sizeInBytes);
}