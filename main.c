#include "include/Tree.h"
#include "include/Debug.h"

#define MAX (1<<4)

int culo(void* a, void* b){
    return a > b ? -1 : a < b ? 1 : 0;
}

int main(){
    Tree tree = treeInit(culo, USRALLOC, 0);
    for (long int i=1; i<=MAX; i++){
        treeAppend(tree, (void*)i);
    }
    treeStructPrint(tree);
    treeDestroy(tree);
}