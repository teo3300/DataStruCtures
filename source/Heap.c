#include "../include/Heap.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>

Heap heapInit(uint dim, uint(*sorting_criteria)(heapNode, heapNode)){
    Heap heap = (Heap){.content = (heapNode*)malloc((dim+1)*sizeof(heapNode)), .sorting_criteria = sorting_criteria};
    heap.content->length = dim;
    heap.content->size = 0;
    return heap;
}

uint heapOOOInsert(Heap heap, void* data, uint size){
    if(heap.content->size == heap.content->length) return 0;
    heap.content[++heap.content->size] = (heapNode){.data_size = size, .data = (void*)malloc(size)};
    memcpy(heap.content[heap.content->size].data, data, size);
    return 1;
}

void heapify(Heap heap, uint i){
    uint l = LEFT(i);
    uint r = RIGHT(i);
    uint top;
    if(l <= heap.content->size && heap.sorting_criteria(heap.content[l], heap.content[i]))
        top = l;
    else top = i;
    if(r <= heap.content->size && heap.sorting_criteria(heap.content[r], heap.content[top]))
        top = r;
    if(top != i){
        SWAP(i, top);
        heapify(heap, top);
    }
}

void heapBuild(Heap heap){
    for(uint i=(heap.content->size)>>1; i>0; i--)
        heapify(heap, i);
}

void heapRebuild(Heap heap, uint (*sorting_criteria)(heapNode, heapNode)){
    heap.sorting_criteria = sorting_criteria;
    heapBuild(heap);
}

void heapUpdate(Heap heap, uint i, uint size){
    heap.content[i].data_size = size;
    while(i > 1 && heap.sorting_criteria(heap.content[PARENT(i)], heap.content[i])){
        SWAP(i, PARENT(i));
        i = PARENT(i);
    }
}

uint heapInsert(Heap heap, void* data, uint size){
    if(heap.content->size == heap.content->length) return 0;
    heap.content[++heap.content->size] = (heapNode){.data = (void*)malloc(size), .data_size = size};
    memcpy(heap.content[heap.content->size].data, data, size);
    heapUpdate(heap, heap.content->size, size);
    return 1;
}

uint heapExtract(Heap heap, void* dump){
    uint ret_size = 0;
    if(heap.content->size < 1)
        return ret_size;
    ret_size = heapTop(heap).data_size;
    memcpy(dump,  heapTop(heap).data, heapTop(heap).data_size);
    free(heapTop(heap).data);
    heapTop(heap) = heap.content[heap.content->size];
    heap.content->size--;
    heapify(heap, 1);
    return ret_size;
}

void heapPrint(Heap heap){
    printf("Heap:\n");
    for(uint i=1; i<=heap.content->size; i++)
        printf("(%u) <%u, %p>\n", i, heap.content[i].data_size, heap.content[i].data);
}

void heapPrintTrace(Heap heap){
    printf("Trace:\n");
    for(uint i=heap.content->size+1; i<=heap.content->length; i++)
        printf("(%u) [%u, %p]\n", i, heap.content[i].data_size, heap.content[i].data);
}

Heap heapDestroy(Heap heap){
    for(uint i=1; i<=heap.content->size; i++)
        if(heap.content[i].data != NULL)
            free(heap.content[i].data);
    free(heap.content);
    heap.content = NULL;
    heap.sorting_criteria = NULL;
    return heap;
}