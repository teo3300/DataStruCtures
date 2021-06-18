#include "include/DataStruCtures.h"
#include <stdio.h>
#include <string.h>

#define DUMP_LEN 32

char dump[DUMP_LEN];

int main(int argc, char** args){
    if(argc<2){fprintf(stderr, "Errore, passare almeno un parametro\n"); return 1;}
    Stack stack = stackInit(argc-1);
    Stack* stck = &stack;
    for(uint i=1; i<argc; i++){
        stackPush(stck, args[i], strlen(args[i])+1);
    }
    while(!stackEmpty(stck)){
        stackPop(stck, dump);
        printf("%s\n", dump);
    }
    stack = stackDestroy(stack);
    return 0;
}