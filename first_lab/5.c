#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_chars(const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        printf("%c", str[i]);
    }
    return 0;
}

int transfer_to_double(const char *str, double *num) {
    char *endptr;
    double value = strtod(str, &endptr);

    if (*endptr != '\0') {
        print_chars(str);
        printf(" is not a number\n");
        return -1;
    }
    *num = value;
    return 0;
}

double calculate_a(double eps, double x) {
    double x_value = 1;
    long n_fact = 1;
    long count = 0;
    double result = 0;
    do {
        result += (x_value / n_fact);
        ++count;
        x_value *= x;
        n_fact *= count;
    } while (x_value / n_fact > eps);
    return result;
}

double calculate_b(double eps, double x) {
    double x_value = 1;
    long n_fact = 1;
    long count = 0;
    double result = 0;
    double add = 20;
    long i = 0;
    do {
        add = (x_value / n_fact);
        if ((i % 2) == 0) {
            result += add;
        } else {
            result -= add;
        }

        x_value *= (x * x);
        n_fact *= ((count + 1) * (count + 2));

        count += 2;
        ++i;
    } while (add > eps);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Not enough arguments\n");
    }
    double eps, x;
    int res1 = transfer_to_double(argv[1], &eps);
    int res2 = transfer_to_double(argv[2], &x);
    if (res1 + res2 != 0) {
        return -1;
    }
    printf("%.15f\n", calculate_b(eps, x));
    printf("%.15f\n", cos(x));
}