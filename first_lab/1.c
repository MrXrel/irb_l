#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*callback)(int, const char*);
enum ERROR {
    NOT_AN_INTEGER_ERROR = 1,
    OVERFLOW_ERROR = 2,
    NEGATIVE_OR_ZERO_ERROR = 3,
    NOT_IN_RANGE_1_10_ERROR = 4,
    WRONG_FLAG_ERROR = 5,
    WRONG_AMOUNT_OF_ARGUMENTS_ERROR = 6
};

int print_chars(const char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        printf("%c", str[i]);
    }
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
            return NOT_AN_INTEGER_ERROR;
        }

        if (*result > (INT_MAX - (str[i] - '0')) / 10) {
            return OVERFLOW_ERROR;
        }

        *result *= 10;
        *result += (str[i] - '0');
    }
    *result *= sign;
    return 0;
}

int for_p(int num, const char* str) {
    if (num <= 1) {
        printf("Number %d is not prime\n", num);
        return 0;
    }

    for (int i = 2; i * i <= num; ++i) {
        if ((num % i) == 0) {
            printf("Number %d is not prime\n", num);
            return 0;
        }
    }
    printf("Number %d is prime\n", num);
    return 0;
}

int for_h(int num, const char* str) {
    if ((abs(num) > 100) || (num == 0)) {
        printf("There are no natural numbers within 100 that are multiples of the number %d", num);
        return 0;
    }

    int count = 1;
    int res = abs(num * count);
    while (res <= 100) {
        printf("%d ", res);
        ++count;
        res = abs(num * count);
    }
    return 0;
}

int for_s(int num, const char* str) {
    int len = strlen(str);
    char prev = 'N';
    int sum = 0;
    int start_zeros = 1;

    for (int i = 0; i < len; ++i) {
        // checking sign
        if (i == 0 && str[i] == '-') {
            printf("-");
            continue;
        }

        // deleting zeros from the start
        if (str[i] == '0' && start_zeros) {
            continue;
        }
        if (str[i] != '0' && start_zeros) {
            start_zeros = 0;
        }
        // case 0  prev == N (empty)
        // case 1  prev + current > 15
        // case 2  prev + current <= 15
        // case 3  prev == 0
        if (prev == 'N') {
            prev = str[i];
            continue;
        }
        if (prev == '0') {
            printf("%c ", str[i]);
            prev = 'N';
            continue;
        }

        sum = (prev - '0') * 10 + (str[i] - '0');

        if (sum > 15) {
            printf("%c ", prev);
            prev = str[i];
            continue;
        }
        if (sum <= 15) {
            printf("%d ", sum);
            prev = 'N';
            continue;
        }
    }
    // check if prev is not empty
    if (prev != 'N') {
        printf("%c", prev);
    }

    return 0;
}

int for_a(int num, const char* str) {
    if (num <= 0) {
        return NEGATIVE_OR_ZERO_ERROR;
    }
    long ans = 0;
    ans = (1 + num) * num / 2;

    printf("%ld", ans);
    return 0;
}

int for_f(int num, const char* str) {
    if (num < 0) {
        return NEGATIVE_OR_ZERO_ERROR;
    }
    long ans = 1;
    if (num == 0) {
        printf("1");
        return 0;
    }
    for (int i = 1; i <= num; ++i) {
        ans *= i;
    }
    printf("%ld", ans);
    return 0;
}

int for_e(int num, const char* str) {
    if (!(num >= 1 && num <= 10)) {
        return NOT_IN_RANGE_1_10_ERROR;
    }
    for (int i = 1; i <= 10; ++i) {
        long res = 1;
        for (int exp = 1; exp <= num; ++exp) {
            res *= i;
            printf("%ld ", res);
        }
        printf("\n");
    }
    return 0;
}

int string_eq(const char* l, const char* r) { return !strcmp(l, r); }

int find_flag(const char* arg, const char** f_arr, int f_arr_sz) {
    int i = 0;

    for (i = 0; i < f_arr_sz; i++) {
        if (string_eq(arg, f_arr[i])) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    const char* flags[] = {"-h", "/h", "-p", "/p", "-s", "/s", "-a", "/a", "-f", "/f", "-e", "/e"};
    callback callbacks[] = {&for_h, &for_p, &for_s, &for_a, &for_f, &for_e};

    if (argc != 3) {
        printf("Wrong amount of parameters\n");
        printf("E.X -f 5\n");
        return WRONG_AMOUNT_OF_ARGUMENTS_ERROR;
    }

    int num = 0;
    int res = transfer_to_int(argv[1], &num);

    switch (res) {
        case NOT_AN_INTEGER_ERROR:
            print_chars(argv[1]);
            printf(" not an integer\n");
            return NOT_AN_INTEGER_ERROR;

        case OVERFLOW_ERROR:
            printf("Overflow detected\n");
            return OVERFLOW_ERROR;

        default:
            break;
    }

    int flag_res =
        find_flag(argv[2], flags, sizeof(flags) / sizeof(const char*));

    if (flag_res == -1) {
        printf("Unknown flag %s\n", argv[2]);
        return WRONG_FLAG_ERROR;
    }
    callback found_callback = callbacks[flag_res / 2];

    res = found_callback(num, argv[1]);

    switch (res) {
        case NEGATIVE_OR_ZERO_ERROR:
            printf("Number %d should be positive\n", num);
            return NEGATIVE_OR_ZERO_ERROR;

        case NOT_IN_RANGE_1_10_ERROR:
            printf("Number %d shoud be in range [1, 10]\n", num);
            return NOT_AN_INTEGER_ERROR;

        default:
            break;
    }

    printf("\n");
    return 0;
}
