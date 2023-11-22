#ifndef STACK_H
#define STACK_H

struct stack {
    int maxsize;
    int len;
    double* items;
};

struct stack* init(int cap);
int isFull(struct stack* ptr);
int isEmpty(struct stack* ptr);
int push(struct stack* ptr, double value);
double pop(struct stack* ptr);
void destroy(struct stack* ptr);

#endif
