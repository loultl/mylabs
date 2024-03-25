#include "logic.h"
#include "entrypoint.h"

long long stringToInt(const char *str)
{
    return atoll(str);
}

void initialize(AppContext* context)
{
    context->translatedValue = DEFAULT_VALUE;
    context->inputNumSystem = 0;
    context->outputNumSystem = 0;
    context->errorCode = DEFAULT_VALUE;
    strcpy(context->errorLine, ERROR_LINE);
}

void inputOfInputNumSystem(AppContext* context, int inputNumSys, int whichRadioButtonChecked)
{
    context->inputNumSystem = inputNumSys;
    context->whichInputRadioButton = whichRadioButtonChecked;
}

void inputOfOutputNumSystem(AppContext* context, int outputNumSys, int whichRadioButtonChecked)
{
    context->outputNumSystem = outputNumSys;
    context->whichOutputRadioButton = whichRadioButtonChecked;
}

void inputOfValue(AppContext* context, const char* newValue)
{
    context->inputValue = newValue;
}

void translate(AppContext* context, const char* newValue)
{
    if (context->inputNumSystem == context->outputNumSystem)
    {
        context->translatedValue = newValue;
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

void swap(AppContext* context)
{
    int newNumSys = context->inputNumSystem;
    context->inputNumSystem = context->outputNumSystem;
    context->outputNumSystem = newNumSys;
    int newCheckedRadioButton = context->whichInputRadioButton;
    context->whichInputRadioButton = context->whichOutputRadioButton;
    context->whichOutputRadioButton = newCheckedRadioButton;
    context->inputValue = context->translatedValue;
}

char* decToSomething(const char* decimalStr, int base)
{
    int decimal = stringToInt(decimalStr);
    unsigned int num = decimal;
    char newValue[BIT_LIMIT + 1];
    int index = 0;
    while (num > 0 && index < BIT_LIMIT)
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
            context->errorCode = NotCheckedOutputNumSystem;
        if (context->inputNumSystem == 0 && context->outputNumSystem != 0)
            context->errorCode = NotCheckedInputNumSystem;
    }
}

