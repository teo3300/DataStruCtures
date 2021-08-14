#include "include/Heap.h"
#include <stdio.h>

#define MAX (1<<23)

int a_min_b(void *a, void *b){
    return a < b ? -1 : a > b ? 1 : 0;
}
int a_mag_b(void *a, void *b){
    return a > b ? -1 : a < b ? 1 : 0;
}

int main(int argc, char* argv[]){
    Heap heap = heapInit( MAX, a_min_b, USRALLOC, 0);
    for(long int i = 0; i<MAX; i++){
        heapOOOInsert(heap, (void*)i);
    }
    printf("heapSize: %d\n", heapSize(heap));
    printf("heapAvail: %d\n", heapAvail(heap));
    for(long int i = 0; i<MAX; i++){
        heapExtract(heap, NULL);
    }
    heapDestroy(heap);
}