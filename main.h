#include <stdio.h>

#define MAX_CHAR 50
#define MAX_PLACE MAX_CHAR * 4 + 2

void digitAddition(int a, int b, int c, int* result);
void add(const char* a, const char* b, char* dst);
void addition(char* a, const char* b);

void digitSubtraction(int a, int b, int c, int* result);
void subtract(const char* a, const char* b, char* dst);
void subtraction(char* a, const char* b);

void digitMultiplication(int a, int b, int c, int* result);
void multiply(const char* a, const char* b, char* dst);
void multiplication(char* a, const char* b);

void division(char* a, const char* b);

void initNumber(char* number, int max);
int bigNumMax(const char* a, const char* b);
void removeZero(char* number);
void addZero(char* number, int numberofzero, char* dst);
void addDecimal(char* number, int position);
int decimal2int(char* decimalNumber);
void addNegativeSign(char* number);
void removeNegativeSign(char* number);
int hasMultiplyOrDivide(const char* op);
void removeNumber(char number[][MAX_PLACE], int index, int numLength);
void removeOp(char* op, int index, int numLength);
void parse(char* input, int* numLength, int* opLength, char* dstnum, char* dstop);
void calculate(char number[][MAX_PLACE], char* op, int* numLength, int* opLength);