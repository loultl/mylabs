#include "logic.h"

long long stringToInt(const char *str)
{
    return atoll(str);
}

char* intToString(long long value)
{
    char* buffer = (char*)malloc(64);
    if (buffer != NULL)
    {
        snprintf(buffer, 64, "%lld", value);
    }
    return buffer;
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
    context->translatedValue = newValue;
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
        context->translatedValue = decimalToBinary(newValue);
    }
    else if (context->inputNumSystem == 10 && context->outputNumSystem == 8)
    {
        context->translatedValue = decimalToOctal(newValue);
    }
    else if (context->inputNumSystem == 2 && context->outputNumSystem == 10)
    {
        context->translatedValue = binaryToDecimal(newValue);
    }
    else if (context->inputNumSystem == 2 && context->outputNumSystem == 8)
    {
        context->translatedValue = binaryToOctal(newValue);
    }
    else if (context->inputNumSystem == 8 && context->outputNumSystem == 10)
    {
        context->translatedValue = octalToDecimal(newValue);
    }
    else if (context->inputNumSystem == 8 && context->outputNumSystem == 2)
    {
        context->translatedValue = octalToBinary(newValue);
    }
}

void swap(AppContext* context)
{
    char* test = (char*)malloc(strlen(context->translatedValue));
    strcpy(test, context->translatedValue);
    context->translatedValue = context->inputValue;
    context->inputValue = test;
    free(test);
}


char* decimalToBinary(const char* decimalStr)
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

char* decimalToOctal(const char* decimalStr)
{
    long long decimal = stringToInt(decimalStr);
    unsigned int num = decimal;
    char octalValue[BIT_LIMIT_OCTAL +1];
    int index = 0;
    while (num > 0 && index < BIT_LIMIT_OCTAL)
    {
        octalValue[index++] = (num % 8) + '0';
        num /= 8;
    }
    if (decimal >= 0)
    {
        while (index < BIT_LIMIT_OCTAL)
        {
            octalValue[index++] = '0';
        }
    }
    octalValue[BIT_LIMIT_OCTAL] = '\0';
    char* result = (char*)malloc(BIT_LIMIT_OCTAL + 1);
    for (int i = 0; i < BIT_LIMIT_OCTAL; ++i)
    {
        result[i] = octalValue[BIT_LIMIT_OCTAL - 1 - i];
    }
    result[BIT_LIMIT_OCTAL] = '\0';
    return result;
}

char* binaryToDecimal(const char* binaryStr)
{
    long long decimal = 0;
    int base = 1;
    int length = strlen(binaryStr);
    for (int i = length - 1; i >= 0; i--)
    {
        if (binaryStr[i] == '1')
        {
            decimal += base;
        }
        base *= 2;
    }
    char* result = (char*)malloc(BIT_LIMIT + 1);
    snprintf(result, BIT_LIMIT + 1, "%lld", decimal);
    return result;
}

char* binaryToOctal(const char* binaryStr)
{
    char* decimal = binaryToDecimal(binaryStr);
    char* result = decimalToOctal(decimal);
    free(decimal);
    return result;
}

char* octalToDecimal(const char* octalStr)
{
    long long decimal = 0;
    int base = 1;
    int length = strlen(octalStr);

    for (int i = length - 1; i >= 0; --i)
    {
        decimal += (octalStr[i] - '0') * base;
        base *= 8;
    }
    char* result = (char*)malloc(BIT_LIMIT + 1);
    snprintf(result, BIT_LIMIT + 1, "%lld", decimal);
    return result;
}

char* octalToBinary(const char* octalStr)
{
    char* decimal = octalToDecimal(octalStr);
    char* result = decimalToBinary(decimal);
    free(decimal);
    return result;
}
