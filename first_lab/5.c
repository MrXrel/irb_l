#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ERROR {
    SUM_OF_SERIES_IS_NOT_CONVERGE_ERROR = 1,
    NOT_A_DOUBLE_ERROR = 2,
    NOT_AN_INTERGER_ERROR = 3,
    UNDERFLOW_ERROR = 4,
    OVERFLOW_ERROR = 5,
};

enum RESULT {
    SUCCESS = 0,
    ZERO_NUMBER = 10,
    NOT_ZERO_NUMBER = 11,
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
        return NOT_A_DOUBLE_ERROR;
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

int validate_int(const char *str_number, int start_check_index) {
    int has_digit = 0, len = strlen(str_number);
    char c;
    for (int i = start_check_index; i < len; ++i) {
        c = str_number[i];

        if (i == start_check_index && c == '-') {
            continue;
        }
        if (i == start_check_index && c == '+') {
            continue;
        }

        if (!isdigit(c)) {
            return NOT_AN_INTERGER_ERROR;
        }
        if (isdigit(c)) {
            has_digit = 1;
        }
    }

    if (!has_digit) {
        return NOT_AN_INTERGER_ERROR;
    }
    return 0;
}

int check_if_zero_num(const char *str_number) {
    int len = strlen(str_number);
    char c;
    for (int i = 0; i < len; ++i) {
        c = str_number[i];
        
        // because before the exp is zero -00.00e123123 = 0
        if (c == 'e') {
            return ZERO_NUMBER;
        }
        if (c == '.' || c == '+' || c == '-') {
            continue;
        }
        if (c != '0') {
            return NOT_ZERO_NUMBER;
        }
    }
    return ZERO_NUMBER;
}

int validate_double(const char *str_number) {
    int has_point = 0, has_exp = 0, has_digit = 0, len = strlen(str_number);
    char c;
    for (int i = 0; i < len; ++i) {
        c = str_number[i];
        if (i == 0 && c == '-') {
            continue;
        }
        if (i == 0 && c == '+') {
            continue;
        }

        // already . or e in str_number
        if ((c == '.') && (has_point == 1)) {
            return NOT_A_DOUBLE_ERROR;
        }
        if ((c == 'e') && (has_exp == 1)) {
            return NOT_A_DOUBLE_ERROR;
        }

        // situation like e-5
        if ((c == 'e') && (!has_digit)) {
            return NOT_A_DOUBLE_ERROR;
        }

        if (c == 'e') {
            has_exp = 1;
            // if the number after e is int => num is double
            int check_int = check_validate_int(str_number, i + 1);
            if (check_int == NOT_AN_INTERGER_ERROR) {
                return NOT_A_DOUBLE_ERROR;
            }
            return 0;
        }

        if (c == '.') {
            has_point = 1;
            continue;
        }

        if (!isdigit(c)) {
            return NOT_A_DOUBLE_ERROR;
        }

        if (isdigit(c)) {
            has_digit = 1;
        }
    }

    if (!has_digit) {
        return NOT_A_DOUBLE_ERROR;
    }
    return 0;
}

int new_tranform(const char *str, double *number) {
    int check_double = check_validate_double(str);
    if (check_double == NOT_A_DOUBLE_ERROR) {
        return NOT_A_DOUBLE_ERROR;
    }
    int result = sscanf(str, "%lf", number);
    if (result != 1 || isinf(*number)) {
        *number = 0;
        return OVERFLOW_ERROR;
    }
    if ((fabs(*number) < DBL_MIN) && (check_zero_num(str) == NOT_ZERO_NUMBER)) {
        *number = 0;
        return UNDERFLOW_ERROR;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    double a = 0;
    int count = 0, res = 0;
    for (int i = 1; i < argc; ++i) {
        res = new_tranform(argv[i], &a);
        if (res != 0) {
            print_chars(argv[i]);
            printf("\n");
            ++count;
        }
    }
    printf("%d\n", count);

    // if (argc != 3) {
    //     printf("Not enough arguments\n");
    //     return -1;
    // }
    // double eps, x;
    // int res1 = transfer_to_double(argv[1], &eps);
    // int res2 = transfer_to_double(argv[2], &x);
    // if (res1 + res2 != 0) {
    //     return -1;
    // }
    // printf("%.15f\n", calculate_d(eps, x));
}