#ifndef HEAP_H
#define HEAP_H

//#define DEBUG

#define uint unsigned int
typedef union HeapNode{
    struct{
        uint data_size;
        void* data;
    };
    struct{
        uint length;
        uint size;
    };
}heapNode;
typedef struct{
    heapNode*   content;
    uint        (*sorting_criteria)(heapNode, heapNode);
}Heap;

#define PARENT(i)       ((i)>>1)
#define LEFT(i)         ((i)<<1)
#define RIGHT(i)        (((i)<<1)+1)
#define heapTop(heap)   (heap.content[1])
#define SWAP(a,b)       {heapNode C = heap.content[a]; heap.content[a] = heap.content[b]; heap.content[b] = C;}

// Initialize heap specifying maximum size and sorting criteria.
Heap  heapInit(uint dim, uint(*sorting_criteria)(heapNode, heapNode));
// Insert elements out of order.
uint  heapOOOInsert(Heap heap, void* data, uint size);

void  heapify(Heap heap, uint i);

// Build heap from array
void  heapBuild(Heap heap);
// Change sorting criteria and Build new heap with this new one
void  heapRebuild(Heap heap, uint(*sorting_criteria)(heapNode, heapNode));
// Insert elements in order
uint  heapInsert(Heap heap, void* data, uint size);

void  heapUpdate(Heap heap, uint i, uint size);

// Extract heap head and heapify
uint  heapExtract(Heap heap, void* dump);
// Print heap elements: "(index) <size, addr>"
void  heapPrint(Heap heap);
// Print heap trace: "(index) [0, nil]"
void  heapPrintTrace(Heap heap);
// Destroy heap and all its content
Heap  heapDestroy(Heap heap);

#endif