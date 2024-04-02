#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>

#define DEFAULT_VALUE 0
#define EMPTY_LINE ""
#define BIT_LIMIT 32
#define LEN_LIMIT_OCT (BIT_LIMIT / 3) + 1
#define LEN_LIMIT_DEC (BIT_LIMIT / 3) + 1

long long stringToInt(const char *str);
char* toLower(const char* str);

void initialize(AppContext* context);
void inputOfInputNumSystem(AppContext* context, int inputNumSys);
void inputOfOutputNumSystem(AppContext* context, int outputNumSys);
void inputOfValue(AppContext* context, const char* newValue);
void translate(AppContext* context, const char* newValue);

int findIndexInAlphabet(char input, const char* alphabet);
char* decToSomething(const char* decimalStr, int base);
char* toDec(const char* inputStr, int inputNumSys);

int checkDecSize(const char* input);
int checkBinSize(const char* input);
int checkOtherSize(int inputNumSystem, const char* input);
int checkForSize(int inputNumSystem, const char* input);
int checkSymbol(int inputNumSystem, char sym);
int checkForSymbols(int inputNumSystem, const char* input);
void validate(AppContext* context, const char* input, int swapStatus);

void swap(AppContext* context, const char* inputValue, int inNumberSystem, int outNumberSystem);

#endif // LOGIC_H
