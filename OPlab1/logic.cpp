#include "logic.h"

int stringToInt(const char *str)
{
    return atoi(str);
}

void initialize(AppContext* context)
{
    context->translatedValue = DEFAULT_VALUE;
    context->inputNumSystem = 0;
    context->outputNumSystem = 0;
    context->errorCode = DEFAULT_VALUE;
    strcpy(context->errorLine, ERROR_LINE);
}

void inputOfInputNumSystem(AppContext* context, int inputNumSys)
{
    context->inputNumSystem = inputNumSys;
}

void inputOfOutputNumSystem(AppContext* context, int outputNumSys)
{
    context->outputNumSystem = outputNumSys;
}

void inputOfValue(AppContext* context, const char* newValue)
{
    context->inputValue = newValue;
}

void translate(AppContext* context, const char* newValue)
{
    context->errorLine[0] = '\0';

    if (context->inputNumSystem == context->outputNumSystem)
    {
        context->translatedValue = newValue;
    }
    else if (context->inputNumSystem == 10 && context->outputNumSystem == 2)
    {
        context->translatedValue = decToBin(newValue);
    }
    else if (context->inputNumSystem == 10 && context->outputNumSystem == 8)
    {
        context->translatedValue = decToOct(newValue);
    }
    else if (context->inputNumSystem == 2 && context->outputNumSystem == 10)
    {
        context->translatedValue = toDec(newValue, context->inputNumSystem);
    }
    else if (context->inputNumSystem == 2 && context->outputNumSystem == 8)
    {
        context->translatedValue = binToOct(newValue);
    }
    else if (context->inputNumSystem == 8 && context->outputNumSystem == 10)
    {
        context->translatedValue = toDec(newValue, context->inputNumSystem);
    }
    else if (context->inputNumSystem == 8 && context->outputNumSystem == 2)
    {
        context->translatedValue = octToBin(newValue);
    }
}

void swap(AppContext* context)
{
    const char* test = context->translatedValue;
    context->translatedValue = context->inputValue;
    context->inputValue = test;
}

char* decToBin(const char* decimalStr)
{
    long long decimal = stringToInt(decimalStr);
    unsigned int num = decimal;
    char binaryValue[BIT_LIMIT + 1];
    int index = 0;
    while (num > 0 && index < BIT_LIMIT)
    {
        binaryValue[index++] = (num % 2) + '0';
        num /= 2;
    }
    if (decimal >= 0)
    {
        while (index < BIT_LIMIT)
        {
            binaryValue[index++] = '0';
        }
    }
    binaryValue[BIT_LIMIT] = '\0';
    char* result = (char*)malloc(BIT_LIMIT + 1);
    for (int i = 0; i < BIT_LIMIT; ++i)
    {
        result[i] = binaryValue[BIT_LIMIT - 1 - i];
    }
    result[BIT_LIMIT] = '\0';
    return result;
}

char* decToOct(const char* decimalStr)
{
    int decimal = stringToInt(decimalStr);
    unsigned int num = decimal;
    char octalValue[LEN_LIMIT_OCT +1];
    int index = 0;
    while (num > 0 && index < LEN_LIMIT_OCT)
    {
        octalValue[index++] = (num % 8) + '0';
        num /= 8;
    }
    if (decimal >= 0)
    {
        while (index < LEN_LIMIT_OCT)
        {
            octalValue[index++] = '0';
        }
    }
    octalValue[LEN_LIMIT_OCT] = '\0';
    char* result = (char*)malloc(LEN_LIMIT_OCT + 1);
    for (int i = 0; i < LEN_LIMIT_OCT; ++i)
    {
        result[i] = octalValue[LEN_LIMIT_OCT - 1 - i];
    }
    result[LEN_LIMIT_OCT] = '\0';
    return result;
}

char* toDec(const char* inputStr, int inputNumSys)
{
    int decimal = 0;
    int base = 1;
    int length = strlen(inputStr);

    for (int i = length - 1; i >= 0; --i)
    {
        decimal += (inputStr[i] - '0') * base;
        base *= inputNumSys;
    }
    char* result = (char*)malloc(LEN_LIMIT_DEC + 1);
    snprintf(result, LEN_LIMIT_DEC + 1, "%d", decimal);
    result[LEN_LIMIT_DEC] = '\0';
    return result;
}

char* binToOct(const char* binaryStr)
{
    char* decimal = toDec(binaryStr, 2);
    char* result = decToOct(decimal);
    free(decimal);
    return result;
}

char* octToBin(const char* octalStr)
{
    char* decimal = toDec(octalStr, 8);
    char* result = decToBin(decimal);
    free(decimal);
    return result;
}
