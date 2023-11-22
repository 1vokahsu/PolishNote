#include "math_solution.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUGER
#define LOG "\033[0;31m|DEBUGER||Helper.c|\033[0;37m"
#endif

double make_calculation(char sym, double operand1, double operand2) {
    double answer = 0.0f;
    switch (sym) {
        case '+':
            answer = operand1 + operand2;
#ifdef DEBUGER
            printf("%s|Make Calculation| Make Calcualtion -> %lf + %lf = %lf\n", LOG, operand1, operand2,
                   answer);
#endif
            break;
        case '-':
            answer = operand1 - operand2;
#ifdef DEBUGER
            printf("%s|Make Calculation| Make Calcualtion ->%lf - %lf = %lf\n", LOG, operand1, operand2,
                   answer);
#endif
            break;
        case '*':
            answer = operand1 * operand2;
#ifdef DEBUGER
            printf("%s|Make Calculation| Make Calcualtion -> %lf * %lf = %lf\n", LOG, operand1, operand2,
                   answer);
#endif
            break;
        case '/':
            if ((0 <= operand2) && (operand1 <= 0.05)) {
                answer = 0;
            } else {
                answer = operand1 / operand2;
            }
#ifdef DEBUGER
            printf("%s|Make Calculation| Make Calcualtion -> %lf / %lf = %lf\n", LOG, operand1, operand2,
                   answer);
#endif
            break;
        case '^':
            answer = pow(operand1, operand2);
            printf("%lf\n", answer);
            break;
        case 's':
            answer = sin(operand1);
#ifdef DEBUGER
            printf("%s|Make Calculation| Make Calcualtion -> sin(%lf) = %lf\n", LOG, operand1, answer);
#endif
            break;
        case 'c':
            answer = cos(operand1);
#ifdef DEBUGER
            printf("%s|Make Calculation| Make Calcualtion -> cos(%lf) = %lf\n", LOG, operand1, answer);
#endif
            break;
        case 't':
            answer = tan(operand1);
#ifdef DEBUGER
            printf("%s|Make Calculation| Make Calcualtion -> tan(%lf) = %lf\n", LOG, operand1, answer);
#endif
            break;
        case 'g':
            answer = cos(operand1) / sin(operand1);
#ifdef DEBUGER
            printf("%s|Make Calculation| Make Calcualtion -> ctg(%lf) = %lf\n", LOG, operand1, answer);
#endif
            break;
        case 'q':
            answer = sqrt(operand1);
#ifdef DEBUGER
            printf("%s|Make Calculation| Make Calcualtion -> sqrt(%lf) = %lf\n", LOG, operand1, answer);
#endif
            break;
        case 'l':
            if (operand1 <= 0.05) {
                answer = 0;
            } else {
                answer = log10(operand1);
            }
#ifdef DEBUGER
            printf("%s|Make Calculation| Make Calcualtion -> ln(%lf) = %lf\n", LOG, operand1, answer);
#endif
            break;
        default:
            break;
    }
    return answer;
}

int simplOper(char token) {
    int flag = 0;
    const char oper[5] = {'+', '-', '*', '/', '^'};
    for (int i = 0; i < 5; i++) {
        if (oper[i] == token) {
            flag = 1;
            break;
        }
    }

    return flag;
}

double evaluate(char* expression) {
    int strl = strlen(expression);
#ifdef DEBUGER
    printf("%s|Evaluate| Grid char with Length: %d\n", LOG, strl);
#endif
    struct stack* stack = init(strl);
    char* token = strtok(expression, " ");
    while (token != NULL) {
        if (support_isDigit(token[0]) || support_isDigit(token[1])) {
            double value = support_char2int(token);
#ifdef DEBUGER
            printf("%s|Evaluate| Grid value: %lf\n", LOG, value);
#endif
            push(stack, value);
        } else if (simplOper(token[0])) {
            double operand2 = pop(stack);
            double operand1 = pop(stack);
            push(stack, make_calculation(token[0], operand1, operand2));
        } else {
            double operand2 = 0.0;
            double operand1 = pop(stack);
            push(stack, make_calculation(token[0], operand1, operand2));
        }
        token = strtok(NULL, " \n");
    }

    double result = pop(stack);
    destroy(stack);
    return result;
}