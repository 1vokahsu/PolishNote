#include "kurwa.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "support.h"

#define maxLen 1000

void push_kurwa(char* stack, int* top, char x) { stack[++(*top)] = x; }

char pop_kurwa(const char* stack, int* top) {
    if (*top == -1)
        return -1;
    else
        return stack[(*top)--];
}

int priority(char x) {
    int flag = 0;
    if (x == '(')
        flag = 0;
    else if (x == '+' || x == '-')
        flag = 1;
    else if (x == '*' || x == '/')
        flag = 2;
    else if (x == '^')
        flag = 3;
    else if (x == 's' || x == 'c' || x == 't' || x == 'g' || x == 'q' || x == 'l')
        flag = 4;
    else
        flag = -1;
    return flag;
}

char* convertToPolishNotation(const char* text) {
    char ptr[maxLen];
    int ptrIndex = 0;
    int textIndex = 0;
    char stack[maxLen];
    int top = -1;

    while (text[textIndex] != '\0') {
        if (support_isDigit(text[textIndex]) || text[textIndex] == 'x') {
            if (text[textIndex] != 'x') {
                while (support_isDigit(text[textIndex]) || text[textIndex] == '.') {
                    ptr[ptrIndex++] = text[textIndex++];
                }
            } else {
                ptr[ptrIndex++] = text[textIndex++];
            }
            ptr[ptrIndex++] = ' ';
        } else if (text[textIndex] == '(') {
            push_kurwa(stack, &top, text[textIndex]);
            textIndex++;
        } else if (text[textIndex] == ')') {
            while (top != -1 && stack[top] != '(') {
                ptr[ptrIndex++] = pop_kurwa(stack, &top);
                ptr[ptrIndex++] = ' ';
            }
            if (top != -1 && stack[top] == '(') {
                pop_kurwa(stack, &top);
            }
            textIndex++;
        } else if (text[textIndex] == '+' || text[textIndex] == '-' || text[textIndex] == '*' ||
                   text[textIndex] == '/' || text[textIndex] == '^' ||
                   (text[textIndex] == 't' && text[textIndex + 1] == 'a') || text[textIndex] == 'l') {
            if (text[textIndex] != '-') {
                while (top != -1 && priority(stack[top]) >= priority(text[textIndex])) {
                    ptr[ptrIndex++] = pop_kurwa(stack, &top);
                    ptr[ptrIndex++] = ' ';
                }
                push_kurwa(stack, &top, text[textIndex]);
            } else {
                /*
                not 1-
                not x-
                */
                if (((!(support_isDigit(text[textIndex - 1])) && text[textIndex - 1] != 'x') &&
                     support_isDigit(text[textIndex + 1])) ||
                    (text[textIndex + 1] == 'x' && !(support_isDigit(text[textIndex - 1])))) {
                    ptr[ptrIndex++] = text[textIndex];
                } else {
                    while (top != -1 && priority(stack[top]) >= priority(text[textIndex])) {
                        ptr[ptrIndex++] = pop_kurwa(stack, &top);
                        ptr[ptrIndex++] = ' ';
                    }
                    push_kurwa(stack, &top, text[textIndex]);
                }
            }
            textIndex++;
        } else if (text[textIndex] == 's') {
            if (text[textIndex + 1] == 'i' || text[textIndex + 1] == 'q') {
                char sym;
                sym = text[textIndex + 1] == 'i' ? ('s') : ('q');
                push_kurwa(stack, &top, sym);
                textIndex += 2;
            } else {
                textIndex++;
            }
        } else if (text[textIndex] == 'c') {
            if (text[textIndex + 1] == 'o' || text[textIndex + 1] == 't') {
                char sym;
                sym = text[textIndex + 1] == 'o' ? ('c') : ('g');
                push_kurwa(stack, &top, sym);
                textIndex += 2;
            } else {
                textIndex++;
            }
        } else {
            textIndex++;
        }
    }

    while (top != -1) {
        ptr[ptrIndex++] = pop_kurwa(stack, &top);
        ptr[ptrIndex++] = ' ';
    }

    ptr[ptrIndex] = '\0';

    return strdup(ptr);
}