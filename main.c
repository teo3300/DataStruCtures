#include "include/Tree.h"
#include <stdio.h>

int data_size_sort(treeNode a, treeNode b){
    return a.data_size < b.data_size ? 1 : a.data_size > b.data_size ? -1 : 0;
}

int main(int argc, char* argv[]){
    Tree* tree = treeInit(data_size_sort);
    treeNode to_find = (treeNode){.data = NULL, .data_size = 500};
    for (int i=0; i<1000; i++){
        treeAppend(tree, NULL, i);
    }
    printf("nodo 500: %p\n", treeFind(tree, to_find));
    treeDestroy(tree);
}