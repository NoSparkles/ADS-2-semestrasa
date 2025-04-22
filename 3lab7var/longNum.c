#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "longNum.h"


LongNum* createLongNum(const char *str) {
    LongNum *num = (LongNum*)malloc(sizeof(LongNum));
    num->length = strlen(str);
    num->digits = (int*)malloc(num->length * sizeof(int));

    for (int i = 0; i < num->length; i++) {
        num->digits[i] = str[i] - '0';
    }
    return num;
}


void destroyLongNum(LongNum *num) {
    free(num->digits);
    free(num);
}


void printLongNum(const LongNum *num) {
    for (int i = 0; i < num->length; i++) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

LongNum* add(const LongNum *a, const LongNum *b) {
    int maxLength = (a->length > b->length) ? a->length : b->length;
    LongNum *result = (LongNum*)malloc(sizeof(LongNum));
    result->digits = (int*)calloc(maxLength + 1, sizeof(int));
    result->length = maxLength + 1;

    int carry = 0;
    int i = a->length - 1;
    int j = b->length - 1;
    int k = result->length - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a->digits[i--];
        if (j >= 0) sum += b->digits[j--];
        carry = sum / 10;
        result->digits[k--] = sum % 10;
    }

    if (result->digits[0] == 0) {
        result->length--;
        for (int i = 0; i < result->length; i++) {
            result->digits[i] = result->digits[i + 1];
        }
    }

    return result;
}
LongNum* sub(const LongNum *a, const LongNum *b) {
    if (compare(a, b) < 0) {
        printf("Atimties klaida: pirmas skaicius turi buti didesnis nei antras\n");
        return NULL;
    }

    LongNum *result = (LongNum*)malloc(sizeof(LongNum));
    result->digits = (int*)malloc(a->length * sizeof(int));
    result->length = a->length;

    int borrow = 0;
    int i = a->length - 1;
    int j = b->length - 1;
    int k = result->length - 1;

    while (i >= 0 || j >= 0 || borrow) {
        int diff = a->digits[i--] - borrow;
        if (j >= 0) diff -= b->digits[j--];
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result->digits[k--] = diff;
    }
    while (result->length > 1 && result->digits[0] == 0) {
        result->length--;
        for (int i = 0; i < result->length; i++) {
            result->digits[i] = result->digits[i + 1];
        }
    }

    return result;
}
LongNum* mul(const LongNum *a, const LongNum *b) {
    LongNum *result = (LongNum*)malloc(sizeof(LongNum));
    result->length = a->length + b->length;
    result->digits = (int*)calloc(result->length, sizeof(int));

    for (int i = a->length - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = b->length - 1; j >= 0; j--) {
            int prod = a->digits[i] * b->digits[j] + result->digits[i + j + 1] + carry;
            carry = prod / 10;
            result->digits[i + j + 1] = prod % 10;
        }
        result->digits[i] += carry;
    }
    while (result->length > 1 && result->digits[0] == 0) {
        result->length--;
        for (int i = 0; i < result->length; i++) {
            result->digits[i] = result->digits[i + 1];
        }
    }

    return result;
}
LongNum* longNumDiv(const LongNum *a, const LongNum *b) {
    if (compare(b, &(LongNum){(int[]){0}, 1}) == 0) {
        printf("Dalinimas is nulio!\n");
        return NULL;
    }

    LongNum *result = (LongNum*)malloc(sizeof(LongNum));
    result->digits = (int*)calloc(a->length, sizeof(int));
    result->length = a->length;

    LongNum *remainder = createLongNum("0");

    for (int i = a->length - 1; i >= 0; i--) {
        remainder->digits[remainder->length - 1] = a->digits[i];

        int quotient = 0;
        while (compare(remainder, b) >= 0) {
            LongNum *temp = sub(remainder, b);
            destroyLongNum(remainder);
            remainder = temp;
            quotient++;
        }

        result->digits[i] = quotient;
    }
    while (result->length > 1 && result->digits[0] == 0) {
        result->length--;
        for (int i = 0; i < result->length; i++) {
            result->digits[i] = result->digits[i + 1];
        }
    }

    destroyLongNum(remainder);
    return result;
}
LongNum* mod(const LongNum *a, const LongNum *b) {
    LongNum *quotient = longNumDiv(a, b);
    LongNum *prod = mul(quotient, b);
    LongNum *remainder = sub(a, prod);

    destroyLongNum(quotient);
    destroyLongNum(prod);

    return remainder;
}
int compare(const LongNum *a, const LongNum *b) {
    if (a->length > b->length) return 1;
    if (a->length < b->length) return -1;
    for (int i = 0; i < a->length; i++) {
        if (a->digits[i] > b->digits[i]) return 1;
        if (a->digits[i] < b->digits[i]) return -1;
    }
    return 0;
}
