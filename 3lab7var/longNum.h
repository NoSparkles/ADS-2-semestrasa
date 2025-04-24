// sukurtas mokiniu airu1143 ir pamodifikuotas manimi

#ifndef LONGNUM_H
#define LONGNUM_H

typedef struct {
    int *digits;
    int length;
} LongNum;

LongNum* createLongNum(const char *str);
LongNum *createLongNumFromInt(int number);
void destroyLongNum(LongNum *num);
void printLongNum(const LongNum num);

LongNum* add(const LongNum *a, const LongNum *b);
LongNum* sub(const LongNum *a, const LongNum *b);
LongNum* mul(const LongNum *a, const LongNum *b);
LongNum* longNumDiv(const LongNum *a, const LongNum *b);
LongNum* mod(const LongNum *a, const LongNum *b);

int compare(const LongNum *a, const LongNum *b);

#endif

