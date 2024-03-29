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
#define BIT_LIMIT 32
#define LEN_LIMIT_OCT (BIT_LIMIT / 3) + 1
#define LEN_LIMIT_DEC (BIT_LIMIT / 3) + 1

long long stringToInt(const char *str);
void initialize(AppContext* context);
void inputOfInputNumSystem(AppContext* context, int inputNumSys, int whichRadioButtonChecked);
void inputOfOutputNumSystem(AppContext* context, int outputNumSys, int whichRadioButtonChecked);
void inputOfValue(AppContext* context, const char* newValue);
void translate(AppContext* context, const char* newValue);
void swap(AppContext* context);

char* decToSomething(const char* decimalStr, int base);
char* toDec(const char* inputStr, int inputNumSys);

int checkDecSize(const char* input);
int checkSize(AppContext* context, const char* input);

void setErrorCode(AppContext* context, const char* input);

#endif // LOGIC_H
