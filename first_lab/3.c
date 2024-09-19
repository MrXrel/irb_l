#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

typedef int (*callback) (int argc, char** argv[]);

// Функция для решения квадратного уравнения
int solve_quadratic(double a, double b, double c, double epsilon) {
    double discriminant = b * b - 4 * a * c;
    
    if (fabs(discriminant) < epsilon) {
        printf("One solution: x = %.12f ", -b / (2 * a));
        printf("when a = %.12f, b = %.12f, c = %.12f\n", a, b, c);
        return 0;
    } else if (discriminant > epsilon) {
        double x1 = (-b + sqrt(discriminant)) / (2 * a);
        double x2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("Two solutions: x1 = %.12f, x2 = %.12f ", x1, x2);
        printf("when a = %.12f, b = %.12f, c = %.12f\n", a, b, c);
        return 0;
    } 

    return -1;
}

// Проверка кратности чисел
int check_multiples(int a, int b) {
    if (a % b == 0) {
        printf("%d is a multiple of %d\n", a, b);
    } else {
        printf("%d is not a multiple of %d\n", a, b);
    }
    return 0;
}

// Проверка на прямоугольный треугольник
int check_triangle(double a, double b, double c, double epsilon) {
    double a2 = a * a, b2 = b * b, c2 = c * c;

    if (fabs(a2 + b2 - c2) < epsilon || fabs(a2 + c2 - b2) < epsilon || fabs(b2 + c2 - a2) < epsilon) {
        printf("It's a rectangular triangle\n");
    } else {
        printf("It's not a rectangular triangle\n");
    }
    return 0;
}

int print_chars(const char* str) {
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

int transfer_to_int(const char* str, int* result) {
    int len = strlen(str);
    int sign = 1;
    for (int i = 0; i < len; i++) {
        if ((i == 0) && str[i] == '-') {
            sign = -1;
            continue;
        }
        if (!(str[i] >= '0' && str[i] <= '9')) {
            print_chars(str);
            printf(" not an integer\n");
            return -1;
        }

        if (*result > (INT_MAX - (str[i] - '0')) / 10) {
            printf("Overflow detected\n");
            return -1;
        }

        *result *= 10;
        *result += (str[i] - '0');
    }
    *result *= sign;
    return 0;
}

int find_flag(const char* flag, const char** flags, int size_of_flag) {
    for (int i = 0; i < size_of_flag; ++i) {
        if (strcmp(flag, flags[i]) == 0) {
            return i;
        }
    }
    return -1;
}

int for_q(int argc, char** argv[]) {
    if (argc != 6) {
        printf("Wrong number of arguments\n");
        return -1;
    }

    double arguments[4];
    for (int i = 2; i < argc; ++i) {
        int res = transfer_to_double((*argv)[i], &arguments[i - 2]);
        if (res == -1){
            return -1;
        }
    }
    double eps = arguments[0], a = arguments[1], b = arguments[2], c = arguments[3];

    int desc_res[6];
    desc_res[0] = solve_quadratic(a, b, c, eps);
    desc_res[1] = solve_quadratic(a, c, b, eps);
    desc_res[2] = solve_quadratic(b, a, c, eps);
    desc_res[3] = solve_quadratic(b, c, a, eps);
    desc_res[4] = solve_quadratic(c, a, b, eps);
    desc_res[5] = solve_quadratic(c, b, a, eps);
    
    int sum_of_res = 0;
    for (int i = 0; i < 6; ++i) {
        sum_of_res += desc_res[i];
    }

    if (sum_of_res == -6) {
        printf("There are no quadratic equations with solution with your coefs\n");
    }
    return 0;
}

int for_m(int argc, char** argv[]) { 
    if (argc != 4) {
        printf("Wrong number of arguments\n");
        return -1;
    }
    
    int arguments[2];
    for (int i = 2; i < argc; ++i) {
        int res = transfer_to_int((*argv)[i], &arguments[i - 2]);
        if (res == -1){
            return -1;
        }
    }
    int a = arguments[0], b = arguments[1];

    if (a == 0 || b == 0) {
        printf("One of the numbers is zero\n");
        return -1;
    }
    check_multiples(a, b);
    return 0;
}

int for_t(int argc, char** argv[]) { 
    if (argc != 6) {
        printf("Wrong number of arguments\n");
        return -1;
    }

    double arguments[4];
    for (int i = 2; i < argc; ++i) {
        int res = transfer_to_double((*argv)[i], &arguments[i - 2]);
        if (res == -1){
            return -1;
        }
    }
    double eps = arguments[0], a = arguments[1], b = arguments[2], c = arguments[3];

    check_triangle(a, b, c, eps);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No flags. Use one of this flag -q, -m, -t.\n");
        return - 1;
    }

    const char* flags[] = {"-q", "/q", "-m", "/m", "-t", "/t"};
    const callback callbacks[] = {&for_q, &for_m, &for_t};

    int res = find_flag(argv[1], flags, sizeof(flags) / sizeof(char*));
    if (res == -1) {
        printf("Flag ");        
        print_chars(argv[1]);
        printf(" is not valid. Use one of this flag -q, -m, -t.");
        printf("\n");
        return -1;
    }
    callback func = callbacks[res / 2];
    int func_res = func(argc, &argv);

    if (func_res == -1) {
        return -1;
    }

    return 0;
}
