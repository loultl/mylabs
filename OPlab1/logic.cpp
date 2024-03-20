#include "logic.h"
#include "entrypoint.h"

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
        context->translatedValue = decToSomething(newValue, LEN_LIMIT_BIN, context->outputNumSystem);
    }
    else if (context->inputNumSystem == 10 && context->outputNumSystem == 8)
    {
        context->translatedValue = decToSomething(newValue, LEN_LIMIT_OCT, context->outputNumSystem);
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

char* decToSomething(const char* decimalStr, int lenghtLimit, int base)
{
    int decimal = stringToInt(decimalStr);
    unsigned int num = decimal;
    char newValue[lenghtLimit + 1];
    int index = 0;
    while (num > 0 && index < lenghtLimit)
    {
        newValue[index++] = (num % base) + '0';
        num /= base;
    }
    newValue[index] = '\0';
    char* result = (char*)malloc(index + 1);
    for (int i = 0; i < index; ++i)
    {
        result[i] = newValue[index - 1 - i];
    }
    result[index] = '\0';
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
    char* result = decToSomething(decimal, LEN_LIMIT_OCT, 8);
    free(decimal);
    return result;
}

char* octToBin(const char* octalStr)
{
    char* decimal = toDec(octalStr, 8);
    char* result = decToSomething(decimal, LEN_LIMIT_BIN, 2);
    free(decimal);
    return result;
}

int checkDecSize(const char* input)
{
    int checkState = 0;
    if (stringToInt(input) > (pow(2, BIT_LIMIT - 1) - 1) || stringToInt(input) < (-pow(2, BIT_LIMIT - 1)))
    {
        checkState = 1;
    }
    return checkState;
}

int checkOctSize(const char* input)
{
    int checkState = 0;
    if (!(strlen(input) < LEN_LIMIT_OCT || ((strlen(input) == LEN_LIMIT_OCT) && (input[0] >= 0 && input[0] <= '3'))))
    {
        checkState = 1;
    }
    return checkState;
}

int checkBinSize(const char* input)
{
    return strlen(input) > BIT_LIMIT;
}

void setErrorCode(AppContext* context, const char* input)
{
    context->errorCode = NoErrors;
    if (context->inputNumSystem == 10)
    {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if ((i == 0 && !(input[i] == '-' || isdigit(input[i]))) || (i > 0 && !isdigit(input[i])))
            {
                context->errorCode = IncorrectCombibationOfSymbols;
                break;

            }
            else if (checkDecSize(input))
            {
                context->errorCode = ExitFromInt;
                break;
            }
        }
    }
    else if (context->inputNumSystem == 2)
    {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if (input[i] != '0' && input[i] != '1')
            {
                context->errorCode = IncorrectCombibationOfSymbols;
                break;
            }
            else if (checkBinSize(input))
            {
                context->errorCode = ExitFromInt;
                break;
            }
        }
    }
    else if (context->inputNumSystem == 8)
    {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if (input[i] < '0' || input[i] > '7')
            {
                context->errorCode = IncorrectCombibationOfSymbols;
                break;
            }
            else if (checkOctSize(input))
            {
                context->errorCode = ExitFromInt;
                break;
            }
        }
    }
    if (context->errorCode == NoErrors)
    {
        if (context->inputNumSystem == 0 && context->outputNumSystem == 0)
            context->errorCode = NotCheckedNumSystems;
        if (context->inputNumSystem != 0 && context->outputNumSystem == 0)
            context->errorCode = NotCheckedInputNumSystem;
        if (context->inputNumSystem == 0 && context->outputNumSystem != 0)
            context->errorCode = NotCheckedOutputNumSystem;
    }
}

