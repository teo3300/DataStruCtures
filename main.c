#include "include/Heap.h"
#include <stdio.h>
#include <string.h>

int strcmp_sort(heapNode a, heapNode b){
    return strcmp(b->data, a->data);
}
int size_sort(heapNode a, heapNode b){
    return a->data_size < b->data_size;
}

char buffer[100];

char parse(char* buffer, char* tmp){
    *tmp = getchar();
    int i=0;
    while(*tmp != ' ' && *tmp != '\n'){
        *(buffer+i) = *tmp;
        i++;
        *tmp = getchar();
    }
    *(buffer+i) = '\0';
    return i+1;
}

int main(int argc, char* argv[]){
    Heap heap = heapInit(18, strcmp_sort);
    char tmp = '\0';
    while(tmp != '\n'){
        heapOOOInsert(heap, buffer, parse(buffer, &tmp));
    }
    heapBuild(heap);
    while(heapSize(heap)){
        if(heapExtract(heap, buffer)){
            printf("+ %s\n", buffer);
        } else {
            printf("- elemento vuoto\n");
        }
    }
    heapDestroy(heap);
}