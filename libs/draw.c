#include "draw.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUGER
#define LOG "\033[0;31m|DEBUGER||Graph.c|\033[0;37m"
#endif

void print_graph(double y_arr[COLS]) {
    char graphic[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            graphic[i][j] = '.';
        }
    }
    double y_step = 2.0 / (ROWS - 1);
    double x_step = 4 * M_PI / (COLS - 1);
    for (double x = 0; x <= 4 * M_PI; x = x + x_step, y_arr++) {
        double y = *y_arr;
        long y_pos = lround((y + 1) / y_step);
        long x_pos = lround(x / x_step);
#ifdef DEBUGER
        printf("%s|Draw| Put '*' at W:%ld H:%ld\n", LOG, y_pos, x_pos);
#endif
        if ((0 <= y_pos) && (y_pos <= ROWS - 1) && (0 <= x_pos) && (x_pos <= COLS - 1)) {
            graphic[y_pos][x_pos] = '*';
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            putchar(graphic[i][j]);
        }
        if (i != ROWS - 1) {
            printf("\n");
        }
    }
}