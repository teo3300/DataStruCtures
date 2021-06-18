#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#define DEBUG

#ifdef DEBUG
    #define LOG(x)          printf("L: %d\t> ", __LINE__); printf(#x); printf("\n")
    #define PRINT(labl, x)  printf("D: %d\t> ", __LINE__); printf(#labl); printf(": %d", x); printf("\n")
#endif
#ifndef DEBUG
    #define LOG(x)
    #define PRINT(labl, x)
#endif

#include "Heap.h"
#include "Stack.h"

#undef LOG
#undef PRINT

#endif