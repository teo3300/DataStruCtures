#ifndef HEAP_H
#define HEAP_H

#undef  LIBALLOC
#undef  USRALLOC
#define LIBALLOC 1
#define USRALLOC 0

#define INLINE static inline

#define uint unsigned int
#define ulint unsigned long int

typedef struct{
    void      **data;
    int       (*sorting_criteria)(void*, void*);
    uint        data_size;
    uint        length;
    uint        libAlloc;
    uint        size;
} HEAP;
typedef HEAP *Heap;

#define PARENT(i)       ((i)>>1)
#define LEFT(i)         ((i)<<1)
#define RIGHT(i)        (((i)<<1)+1)
#define heapTop(heap)   (heap->data[1])
#define SWAP(a,b)       {void* C = heap->data[a]; heap->data[a] = heap->data[b]; heap->data[b] = C;}

INLINE uint heapSize(Heap heap){return heap->size;}
INLINE uint heapAvail(Heap heap){return heap->length - heap->size;}

// Initialize heap specifying maximum size and sorting criteria.
Heap heapInit(uint dim, int(*sorting_criteria)(void*, void*), uint memAlloc, uint data_size /*only used with libAlloc*/);
// Insert elements out of order.
void* heapOOOInsert(Heap heap, void* data);

void heapify(Heap heap, uint i);
void heapUpdate(Heap heap, uint i);

// Build heap from array
void heapBuild(Heap heap);
// Change sorting criteria and Build new heap with this new one
void heapRebuild(Heap heap, int(*sorting_criteria)(void*, void*));/*keep alloc type*/
// Insert elements in order
void* heapInsert(Heap heap, void* data);

// Extract heap head and heapify
void* heapExtract(Heap heap, void* dump);
// Print heap elements: "(index) <size, addr>"
void heapPrint(Heap heap);
// Print heap trace: "(index) [0, nil]"
void heapPrintTrace(Heap heap);
// Destroy heap and all its content
void heapDestroy(Heap heap);

#endif