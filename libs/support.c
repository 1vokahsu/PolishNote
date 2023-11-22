#include "support.h"

int support_isDigit(char c) { return (c >= '0' && c <= '9'); }

double support_char2int(const char* str) {
    double result = 0.0;
    double sign = 1.0;
    int i = 0;

    if (str[0] == '-') {
        sign = -1.0;
        i = 1;
    }

    int decimal_point = -1;
    int decimal_places = 0;
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            if (decimal_point != -1) {
                decimal_places++;
            }
            result = result * 10.0 + (str[i] - '0');
        } else if (str[i] == '.') {
            decimal_point = i;
        } else {
            break;
        }
        i++;
    }

    if (decimal_point != -1) {
        while (decimal_places > 0) {
            result /= 10.0;
            decimal_places--;
        }
    }

    return sign * result;
}