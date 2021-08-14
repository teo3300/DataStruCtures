#include "../include/Heap.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>

Heap heapInit(uint dim, int(*sorting_criteria)(void*, void*), uint memAlloc, uint data_size){
    Heap heap = (Heap)malloc(sizeof(HEAP));                             if(heap == NULL) return NULL;
    heap->data              = (void**)malloc((dim+1)*sizeof(void*));    if(heap->data == NULL) return NULL;
    heap->sorting_criteria  = sorting_criteria;
    heap->data_size         = data_size;
    heap->size              = 0;
    heap->length            = dim;
    heap->libAlloc          = memAlloc;
    return heap;
}

void* heapOOOInsert(Heap heap, void* data){
    if(heap->size == heap->length) return NULL;
    if (heap->libAlloc) {
        heap->data[++heap->size] = (void*)malloc(heap->data_size);  if(heap->data[heap->size] == NULL) return NULL;
        memcpy(heap->data[heap->size], data, heap->data_size);
    } else {
        heap->data[++heap->size] = data;
    }
    return heap->data[heap->size];
}

void heapify(Heap heap, uint i){
    uint l = LEFT(i);
    uint r = RIGHT(i);
    uint top;
    if(l <= heap->size && heap->sorting_criteria(heap->data+l, heap->data+i) > 0)
        top = l;
    else top = i;
    if(r <= heap->size && heap->sorting_criteria(heap->data+r, heap->data+top) > 0)
        top = r;
    if(top != i){
        SWAP(i, top);
        heapify(heap, top);
    }
}

void heapUpdate(Heap heap, uint i){
    while(i > 1 && heap->sorting_criteria(heap->data+i, heap->data+PARENT(i)) > 0){
        SWAP(i, PARENT(i));
        i = PARENT(i);
    }

}

void heapBuild(Heap heap){
    for(uint i=(heap->size)>>1; i>0; i--)
        heapify(heap, i);
}

void heapRebuild(Heap heap, int (*sorting_criteria)(void*, void*)){
    heap->sorting_criteria = sorting_criteria;
    heapBuild(heap);
}

void* heapInsert(Heap heap, void* data){
    void* ret = heapOOOInsert(heap, data);
    if(! ret) return 0;
    heapUpdate(heap, heap->size);
    return ret;
}

void* heapExtract(Heap heap, void* dump){
    void* ret;
    if (! heap->size) return NULL;
    if (heap->libAlloc) {
        memcpy(dump, heapTop(heap), heap->data_size);
        free(heapTop(heap));
        ret = dump;
    } else {
        ret = heapTop(heap);
    }
    heapTop(heap) = heap->data[heap->size];
    heap->size--;
    heapify(heap, 1);
    return ret;
}

void heapPrint(Heap heap){
    printf("Heap:\n");
    for(uint i=1; i<=heap->size; i++)
        printf("(%u) <%p>\n", i, heap->data[i]);
        //printf("%2d: %s\n", i, (char*)heap->content[i].data);
}

void heapPrintTrace(Heap heap){
    printf("Trace:\n");
    for(uint i=heap->size+1; i<=heap->length; i++)
        printf("(%u) [%p]\n", i, heap->data[i]);
}

void heapDestroy(Heap heap){
    if (heap->libAlloc) {
        for(uint i=1; i<=heap->size; i++)
            if(heap->data[i])
                free(heap->data[i]);
    }
    free(heap->data);
    free(heap);
}