#include "include/Tree.h"
#include <stdio.h>
#include <string.h>

int a_min_b(void *a, void *b){
    //printf("sorting criteria: %lu < %lu: %s\n", (ulint)a, (ulint)b, (ulint)a < (ulint)b ? "true" : "false");
    return a < b ? 1 : a > b ? -1 : 0;
}
int a_mag_b(void *a, void *b){
    //printf("sorting criteria: %lu > %lu: %s\n", (ulint)a, (ulint)b, (ulint)a > (ulint)b ? "true" : "false");
    return a > b ? 1 : a < b ? -1 : 0;
}

int main(int argc, char* argv[]){
    Tree tree = treeInit(a_min_b, USRALLOC, 0);
    treeRemove(tree, tree->root);
    treeRemove(tree, treeFirstFind(tree, (void*)10));
    for(long int i = 1; i<=20; i++){
        treeAppend(tree, (void*)i);
    }
    treeStructPrint(tree);
    printf("\n");
    treeRemove(tree, treeFirstFind(tree, (void*)10));
    treeRebuild(tree, a_mag_b);
    treeRemove(tree, treeFirstFind(tree, (void*)5));
    treeStructPrint(tree);
    printf("tree min: %lu\n", (ulint)treeAbsMinimum(tree)->data);
    printf("tree max: %lu\n", (ulint)treeAbsMaximum(tree)->data);
    treeDestroy(tree);
}