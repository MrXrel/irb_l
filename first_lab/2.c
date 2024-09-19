#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846
const double EPS = 0.000000001;
typedef double (*function)(double n);

double find_sol(double n, function f, double eps) {
    double res1 = f(n);
    double res2 = f(2 * n);
    if (fabs(res1 - res2) < eps) {
        return res2;
    }
    return find_sol(2 * n, f, eps);
}

double calculate_e_limit(double eps) {
    double current_e = 1;
    double prev_e = 0;
    int i = 1;
    while (fabs(current_e - prev_e) > eps) {
        prev_e = current_e;
        current_e = pow(1 + 1.0 / i, i);
        ++i;
    }
    return current_e;
}

// Function to calculate e using the series expansion
double calculate_e_sum(double eps) {
    double e = 1.0;
    double fact = 1.0;
    int i = 1;
    while (1.0 / fact > eps) {
        fact *= i;
        e += 1.0 / fact;
        ++i;
    }
    return e;
}

double calculate_ln_sum(double eps) {
    double ln = 0;
    double add = 100;
    int i = 1;
    while (fabs(add) > eps) {
        add = ((double)1) / i;

        if ((i - 1) % 2 == 0) {
            ln += add;
        } else {
            ln -= add;
        }
        ++i;
    }
    return ln;
}

double calculate_pi_sum(double eps) {
    double pi = 0;
    double add = 100;
    int i = 1;
    while (add > eps) {
        add = ((double)1) / (2 * i - 1);

        if ((i - 1) % 2 == 0) {
            pi += add;
        } else {
            pi -= add;
        }
        ++i;
    }
    return 4 * pi;
}

double calculate_sqrt2_sum(double eps) {
    double sqrt2 = 1;
    double degree2 = 0.25;
    while (fabs(degree2) > eps) {
        sqrt2 *= pow(2, degree2);
        degree2 *= 0.5;
    }
    return sqrt2;
}

double calculate_sigma_sum(double n) {
    double sigma = 0;
    for (int i = 2; i <= n; i++) {
        sigma += ((1.0 / (fabs(sqrt(i)) * fabs(sqrt(i)))) - (1.0 / i));
    }
    return sigma - (M_PI * M_PI / 6);
}

double exp_function(double x) {
    return exp(x);
}

double square_function(double x) {
    return x * x;
}

double calculate_equation(double left, double right, double equals, function f, double eps) {
    double middle = (left + right) / 2;
    double res = f(middle);

    if (fabs(res - equals) < eps) {
        return middle;
    } else if (res > equals) {
        return calculate_equation(left, middle, equals, f, eps);
    } else {
        return calculate_equation(middle, right, equals, f, eps);
    }
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

int main() {
    double eps = EPS;

    // printf("%.15f\n", find_sol(1000, &calculate_e_limit, eps));
    // printf("%.15f\n", find_sol(1000, &calculate_e_sum, eps));
    // printf("%.15f\n", calculate_equation(-10, 10, 1, &log, eps));
    // double root = calculate_equation(0, 1, 2, &exp_function, eps);
    // printf("%.15f\n", root);
    // printf("%.15f\n", find_sol(1000, &calculate_ln_sum, eps));
    // printf("%.15f\n", find_sol(1000, &calculate_pi_sum, eps));
    // printf("%.15f\n", find_sol(1000, &calculate_square2_sum, eps));
    // printf("%.15f\n", find_sol(1000, &calculate_sigma_sum, eps));
    // root = calculate_equation(0, 2, 2, &square_function, eps);
    // printf("%.15f\n", root);
    // printf("%.15f\n", calculate_e_limit(eps));
    // printf("%.15f\n", calculate_sqrt2_sum(eps));
    // printf("%.15f\n", sqrt(2));
    // printf("%.15f\n", calculate_pi_sum(eps));
    double res;
    transfer_to_double("", &res);
    printf("%lf\n", res);
}
