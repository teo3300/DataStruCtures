#include "../include/Stack.h"
#include <string.h>
#include <malloc.h>

#define ToS     stack->content[stack->size]

Stack stackInit(uint dim){
    Stack stack = (Stack){.content = (stackNode*)malloc(dim*sizeof(stackNode)), .length = dim, .size = 0};
    return stack;
}
uint stackPush(Stack* stack, void* data, uint data_size){
    if(!(stack->size < stack->length))return 0;
    ToS.data_size = data_size;
    ToS.data = (void*)malloc(data_size);
    memcpy(ToS.data, data, data_size);
    stack->size++;
    return data_size;
}

uint stackPop(Stack* stack, void* dump){
    uint ret_size = 0;
    if(stackEmpty(stack)) return ret_size;
    stack->size--;
    ret_size = ToS.data_size;
    memcpy(dump, ToS.data, ToS.data_size);
    free(ToS.data);
    return ret_size;
}

void stackPrint(Stack stack){
    printf("Length: %u, Size: %u\n", stack.length, stack.size);
    for(uint i=0; i<stack.size; i++)
        printf("(%u) <%u, %p>\n", i, stack.content[i].data_size, stack.content[i].data);
}

uint stackEmpty(Stack* stack){
    return (stack->size == 0);
}

Stack stackDestroy(Stack stack){
    for(uint i=0; i<stack.size; i++)
        if(stack.content[i].data != NULL)
            free(stack.content[i].data);
    free(stack.content);
    stack.content = NULL;
    stack.size = 0;
    stack.length = 0;
    return stack;
}