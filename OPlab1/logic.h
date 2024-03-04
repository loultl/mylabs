#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>

#define DEFAULT_VALUE 0
#define ERROR_LINE ""
#define BYTE_LIMIT 4
#define BIT_LIMIT (BYTE_LIMIT * 8)
#define BIT_LIMIT_OCTAL (BIT_LIMIT / 3 + 1)

long long stringToInt(const char *str);
char* intToString(long long value);
void initialize(AppContext* context);
void inputOfInputNumSystem(AppContext* context, int inputNumSys);
void inputOfOutputNumSystem(AppContext* context, int ouputNumSys);
void inputOfValue(AppContext* context, const char* newValue);
void translate(AppContext* context, const char* newValue);
void swap(AppContext* context);

char* decimalToBinary(const char* decimalStr);
char* decimalToOctal(const char* decimalStr);
char* binaryToDecimal(const char* binaryStr);
char* binaryToOctal(const char* binaryStr);
char* octalToDecimal(const char* octalStr);
char* octalToBinary(const char* octalStr);


#endif // LOGIC_H
