#ifndef MALLOC_H
#define MALLOC_H

#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>

struct block
{
    size_t size;
    short free;
    struct block *next;
};

struct block *freeList;

void initialize();

void *incrementHeapIfNecessary(long incr, long lastUsedElementInTheHeap);

void *malloc(size_t noOfBytes);

void *my_memset(void *s, int c, unsigned int len);

void merge();

struct block *findLastBlock();

void *realloc(void *ptr, size_t newSize);

void *reallocarray(void *ptr, size_t nmemb, size_t size);

void merge();

void *calloc();

void free(void *ptr);

int isLastBlock(struct block *block);
#endif