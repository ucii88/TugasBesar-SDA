#ifndef STACK_H
#define STACK_H

#define MAX_STACK 20
#define MAX_STRING 50

typedef struct {
    char rute[MAX_STRING];
    int level;
} StackItem;

typedef struct {
    StackItem items[MAX_STACK];
    int top;
} Stack;

void init_stack(Stack* s);
void push(Stack* s, char* rute, int level);
void pop(Stack* s);

#endif