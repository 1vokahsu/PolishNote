#include "stack.h"

#include <stdlib.h>

struct stack* init(int cap) {
    struct stack* ptr = (struct stack*)malloc(sizeof(struct stack));
    ptr->maxsize = cap;
    ptr->len = -1;
    ptr->items = (double*)malloc(sizeof(double) * cap);
    return ptr;
}

int isFull(struct stack* ptr) { return ptr->len == ptr->maxsize - 1; }

int isEmpty(struct stack* ptr) { return ptr->len == -1; }

int push(struct stack* ptr, double value) {
    if (isFull(ptr)) {
        int newMaxsize = ptr->maxsize + 1;
        ptr->items = (double*)realloc(ptr->items, sizeof(double) * newMaxsize);
        if (ptr->items == NULL) {
            return 0;
        }
        ptr->maxsize = newMaxsize;
    }
    ptr->items[++ptr->len] = value;
    return 1;
}

double pop(struct stack* ptr) {
    if (isEmpty(ptr)) {
        return 0.0;
    } else {
        return ptr->items[ptr->len--];
    }
}

void destroy(struct stack* ptr) {
    free(ptr->items);
    free(ptr);
}