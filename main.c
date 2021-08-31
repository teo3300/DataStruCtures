#include "include/Heap.h"
#include "include/Tree.h"
#include <stdio.h>

#define MAX (1<<6)

typedef struct {
    int giorno;
    int mese;
    int anno;
    int ID;
} Test;

int a_min_b(void *a, void *b){
    Test *A = (Test*)a,
         *B = (Test*)b;
    return A->mese < B->mese ? -1 : A->mese < B->mese ? -1 : 0;
}

void print_info(void* Data){
    Test* data = (Test*)Data;
    printf("<%2d, %2d, %2d, %3d>", data->giorno, data->mese, data->anno, data->ID);
}

Test* filler (Test* t, long int i) {
    t->giorno = i%5;
    t->mese = i%12;
    t->anno = i%40;
    t->ID   = i;
    return t;
}

int main(int argc, char* argv[]){
    Test t;
    Tree tree = treeInit(a_min_b, LIBALLOC, sizeof(Test));
    treeSetPrint(tree, print_info);
    for(long int i = 0; i<MAX; i++){
        treeAppend(tree, filler(& t, i));
    }
    printf("treeSize: %d\n", treeSize(tree));
    treeStructPrint(tree);
    treeDestroy(tree);
}