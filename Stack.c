#include "Stack.h"
#include "Tree.h"

void init_stack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, char* rute, int level) {
    if (s->top < MAX_STACK - 1) {
        s->top++;
        strcpy(s->items[s->top].rute, rute);
        s->items[s->top].level = level;
    }
}

void pop(Stack* s) {
    if (s->top >= 0) {
        s->top--;
    }
}