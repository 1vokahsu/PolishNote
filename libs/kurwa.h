#ifndef KURWA_H
#define KURWA_H

char* convertToPolishNotation(const char* text);
char pop_kurwa(const char* stack, int* top);
void push_kurwa(char* stack, int* top, char x);

#endif