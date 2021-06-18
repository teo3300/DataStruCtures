#ifndef STACK_H
#define STACK_H

#define uint unsigned int
typedef struct StackNode{
    uint  data_size;
    void* data;
}stackNode;

typedef struct{
    stackNode* content;
    uint length;
    uint size;
}Stack;

Stack stackInit(uint dim);
uint  stackPush(Stack* stack, void* data, uint data_size);
uint  stackPop(Stack* stack, void* dump);
void  stackPrint(Stack stack);
uint  stackEmpty(Stack* stack);
Stack stackDestroy(Stack stack);

#endif