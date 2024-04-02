#include "logic.h"

long long stringToInt(const char *str)
{
    return atoll(str);
}

char* toLower(const char* str)
{
    char* result = (char*)malloc(strlen(str) + 1);
    result[strlen(str)] = '\0';
    for(int i = 0; str[i]; i++)
    {
        result[i] = tolower(str[i]);
    }
    return result;
}

void initialize(AppContext* context)
{
    context->translatedValue = EMPTY_LINE;
    context->inputValue = EMPTY_LINE;
    context->inputNumSystem = 0;
    context->outputNumSystem = 0;
    context->errorCode = NoErrors;
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
    if (context->inputNumSystem == context->outputNumSystem)
    {
        context->translatedValue = toLower(newValue);
    }
    else if (context->inputNumSystem == 10)
    {
        context->translatedValue = decToSomething(newValue, context->outputNumSystem);
    }
    else if (context->outputNumSystem == 10)
    {
        context->translatedValue = toDec(newValue, context->inputNumSystem);
    }
    else
    {
        context->translatedValue = decToSomething(toDec(newValue, context->inputNumSystem), context->outputNumSystem);
    }
}

int findIndexInAlphabet(char input, const char* alphabet)
{
    for (unsigned i = 0;i < strlen(alphabet);i++)
    {
        if (input == alphabet[i])
        {
            return i;
        }
    }
    return -1;
}

char* decToSomething(const char* decimalStr, int base)
{
    int decimal = stringToInt(decimalStr);
    unsigned int num = decimal;
    char newValue[BIT_LIMIT + 1];
    int index = 0;
    char alphabet[] = "0123456789abcdef";
    while (num > 0 && index < BIT_LIMIT)
    {
        newValue[index++] = alphabet[num % base];
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
    char alphabet[] = "0123456789abcdef";
    char* lowInputStr = toLower(inputStr);
    int decimal = 0;
    int base = 1;
    int length = strlen(inputStr);
    for (int i = length - 1; i >= 0; --i)
    {
        decimal += findIndexInAlphabet(lowInputStr[i], alphabet) * base;
        base *= inputNumSys;
    }
    free(lowInputStr);
    char* result = (char*)malloc(LEN_LIMIT_DEC + 1);
    snprintf(result, LEN_LIMIT_DEC + 1, "%d", decimal);
    result[LEN_LIMIT_DEC] = '\0';
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

int checkBinSize(const char* input)
{
    return strlen(input) > BIT_LIMIT;
}

int checkOtherSize(int inputNumSystem, const char* input)
{
    int checkState = 0;
    char* newInput = decToSomething(toDec(input, inputNumSystem), inputNumSystem);
    if (strcmp(input, newInput) != 0)
    {
        checkState = 1;
    }
    free(newInput);
    return checkState;
}

int checkForSize(int inputNumSystem, const char* input)
{
    int sizeCheckState = 0;
    switch(inputNumSystem)
    {
    case 2:
        if (checkBinSize(input))
            sizeCheckState = 1;
        break;
    case 10:
        if (checkDecSize(input))
            sizeCheckState = 1;
        break;
    default:
        if (checkOtherSize(inputNumSystem, input))
            sizeCheckState = 1;
        break;
    }
    return sizeCheckState;
}

int checkSymbol(int inputNumSystem, char sym)
{
    int symbolCheckState = 0;
    char alphabet[] = "0123456789abcdef";
    if (!(findIndexInAlphabet(sym, alphabet) >= 0 && findIndexInAlphabet(sym, alphabet) < inputNumSystem))
    {
        symbolCheckState = 1;
    }
    return symbolCheckState;
}

int checkForSymbols(int inputNumSystem, const char* input)
{
    int symbolsCheckState = 0;
    for (int i = 0; input[i] != '\0'; ++i)
    {
        if (input[i] == '-' && i == 0 && inputNumSystem == 10)
        {
            symbolsCheckState = 0;
        }
        else if (checkSymbol(inputNumSystem, input[i]))
        {
            symbolsCheckState = 1;
        }
    }
    return symbolsCheckState;
}

void validate(AppContext* context, const char* input, int swapStatus)
{
    context->errorCode = NoErrors;
    char* lowInputStr = toLower(input);

    if (checkForSymbols(context->inputNumSystem, lowInputStr))
    {
        context->errorCode = IncorrectCombibationOfSymbols;
    }
    else if (checkForSize(context->inputNumSystem, lowInputStr))
    {
        context->errorCode = ExitFromInt;
    }
    free(lowInputStr);

    if (context->errorCode == NoErrors)
    {
        if (context->inputNumSystem == 0 && context->outputNumSystem == 0)
            context->errorCode = NotCheckedNumSystems;
        if (context->inputNumSystem != 0 && context->outputNumSystem == 0)
            context->errorCode = NotCheckedOutputNumSystem;
        if (context->inputNumSystem == 0 && context->outputNumSystem != 0)
            context->errorCode = NotCheckedInputNumSystem;
    }

    if (swapStatus && context->errorCode == NoErrors)
    {
        char* newOutput = decToSomething(toDec(input, context->inputNumSystem), context->outputNumSystem);
        if (strcmp(context->translatedValue, newOutput) != 0)
        {
            context->errorCode = NoInputOrOutput;
        }
        free(newOutput);
    }
}

void swap(AppContext* context, const char* inputValue, int inNumberSystem, int outNumberSystem) {
    validate(context ,inputValue, 1);
    if (context->errorCode == NoErrors) {
        context->inputValue = context->translatedValue;
        context->inputNumSystem = outNumberSystem;
        context->outputNumSystem = inNumberSystem;
        translate(context, context->inputValue);
    }
}
