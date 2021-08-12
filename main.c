#include "include/Heap.h"
#include <stdio.h>
#include <string.h>

int strcmp_sort(heapNode a, heapNode b){
    return strcmp(a->data, b->data);
}
int data_size_sort(heapNode a, heapNode b){
    return a->data_size < b->data_size;
}

int main(int argc, char* argv[]){
    Heap heap = heapInit(16, data_size_sort);
    heapDestroy(heap);
}