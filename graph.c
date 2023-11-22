#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/draw.h"
#include "libs/kurwa.h"
#include "libs/math_solution.h"
#include "libs/stack.h"

#define _USE_MATH_DEFINES

#define maxLen 1000

#ifdef DEBUGER
#define LOG "\033[0;31m|DEBUGER||Graph.c|\033[0;37m"
#endif

char *x_changer(const char *textAdded, const char *textOriginal);
int main() {
    char exp[maxLen];
    double part_x = M_PI * 4 / (COLS - 1);
    printf("Enter text: ");
    fgets(exp, sizeof(exp), stdin);
    system("clear");
    // exp[strcspn(exp, "\n")] = '\0';

    double y_arr[COLS];
    for (int i = 0; i < COLS; i++) {
        char *kurwaMoment = convertToPolishNotation(exp);
#ifdef DEBUGER
        printf("%s|main| Poland text: %s\n", LOG, kurwaMoment);
#endif
        char *normal = NULL;
        double x = part_x * i;
        char x_char[10];
        sprintf(x_char, "%lf", x);
        // '1212.23123123' -> char
        // char -> int
        normal = x_changer(x_char, kurwaMoment);
#ifdef DEBUGER
        printf("%s|main| Normal text: %s\n", LOG, normal);
#endif
        double y = evaluate(normal);
        y_arr[i] = y;
#ifdef DEBUGER
        printf("%s|main| X: %lf\tY:%lf\n", LOG, x, y);
#endif
        free(normal);
        free(kurwaMoment);
    }
    print_graph(y_arr);
    return 0;
}

char *x_changer(const char *textAdded, const char *textOriginal) {
    int length_original = strlen(textOriginal);
    int length_added_part = strlen(textAdded);
    int count_x = 0;
    for (int i = 0; i < length_original; i++) {
        if (textOriginal[i] == 'x') {
            count_x++;
        }
    }
    int result_length = length_original + count_x * (length_added_part - 1);
    char *result = (char *)malloc((result_length + 1) * sizeof(char));
    char *resultPtr = result;
    for (int i = 0; i < length_original; i++) {
        if (textOriginal[i] == 'x') {
            for (int j = 0; j < length_added_part; j++) {
                *resultPtr = textAdded[j];
                resultPtr++;
            }
        } else {
            *resultPtr = textOriginal[i];
            resultPtr++;
        }
    }
    *resultPtr = '\0';
    return result;
}