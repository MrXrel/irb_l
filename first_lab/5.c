#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ERROR {
    SUM_OF_SERIES_IS_NOT_CONVERGE_ERROR = 1,
    NOT_A_DOUBLE_NUM_ERROR = 2,
};

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
        return NOT_A_DOUBLE_NUM_ERROR;
    }
    *num = value;
    return 0;
}

double calculate_a(double eps, double x) {
    double x_value = 1, result = 0, add = 2 * eps;
    long n_fact = 1, count = 0;
    do {
        add = (x_value / n_fact);
        result += (x_value / n_fact);
        ++count;
        x_value *= x;
        n_fact *= count;
    } while (fabs(add) > eps);
    return result;
}

double calculate_b(double eps, double x) {
    double x_value = 1, result = 0, add = 2 * eps;
    long n_fact = 1, count = 0, i = 0;
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
    } while (fabs(add) > eps);

    return result;
}

double calculate_c(double eps, double x) {
    double add = 2 * eps, result = 0, x_value = 1;
    long n3_fact = 1, degree3 = 1, n_square_fact = 1;
    long count1 = 0, count3 = 0;

    do {
        add = (x_value / n3_fact) * degree3 * n_square_fact;

        result += add;

        x_value *= (x * x);
        degree3 *= 27;
        
        n3_fact *= ((count3 + 1) * (count3 + 2) * (count3 + 3));
        n3_fact /= (count1 + 1);
        count3 += 3;

        ++count1;
        n_square_fact *= (count1 * count1);
    } while (fabs(add) > eps);
    return result;
}

double calculate_d(double eps, double x) {
    double add = eps + 1, result = 0, x_value = x * x;
    long n_2_fact = 2, count = 2, i = 1;
    
    do {
        add = x_value / n_2_fact;
        if (i % 2 == 0) {
            result += add;
        } else {
            result -= add;
        }

        x_value *= (x * x);
        n_2_fact *= ((count + 1) * (count + 2));
        count += 2;
        ++i;
    } while (fabs(add) > eps);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Not enough arguments\n");
        return -1;
    }
    double eps, x;
    int res1 = transfer_to_double(argv[1], &eps);
    int res2 = transfer_to_double(argv[2], &x);
    if (res1 + res2 != 0) {
        return -1;
    }
    printf("%.15f\n", calculate_d(eps, x));
}