#include "errorslib.h"
#include "logic.h"
#include <cctype>
#include <cmath>
#include <cstring>

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
    if (!(strlen(input) < LEN_LIMIT_OCT || ((strlen(input) == LEN_LIMIT_OCT) && (input[0] == '0' || input[0] == '1' || input[0] == '2' || input[0] == '3'))))
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
    context->errorCode = 0;
    if (context->inputNumSystem == 10)
    {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if ((i == 0 && !(input[i] == '-' || isdigit(input[i]))) || (i > 0 && !isdigit(input[i])))
            {
                context->errorCode = 10;
            }
            else if (checkDecSize(input))
            {
                context->errorCode = 20;
            }        
        }
    }
    else if (context->inputNumSystem == 2)
    {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if (input[i] != '0' && input[i] != '1')
            {
                context->errorCode = 10;
            }
            else if (checkBinSize(input))
            {
                context->errorCode = 20;
            }
        }
    }
    else if (context->inputNumSystem == 8)
    {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if (input[i] < '0' || input[i] > '7')
            {
                context->errorCode = 10;
            }
            else if (checkOctSize(input))
            {
                context->errorCode = 20;
            }
        }
    }
    if (context->errorCode == 0)
    {
        if (context->inputNumSystem == 0 && context->outputNumSystem == 0)
            context->errorCode = 3;
        if (context->inputNumSystem != 0 && context->outputNumSystem == 0)
            context->errorCode = 2;
        if (context->inputNumSystem == 0 && context->outputNumSystem != 0)
            context->errorCode = 1;
    }
}


void setError(AppContext* context)
{
    switch(context->errorCode)
    {
    case(1):
        strcpy(context->errorLine, "Не выбрана входная система счисления");
        break;
    case(2):
        strcpy(context->errorLine, "Не выбрана выходная система счисления");
        break;
    case(3):
        strcpy(context->errorLine, "Не выбраны системы счисления");
        break;
    case(10):
        strcpy(context->errorLine, "Введена недопустимая комбинация символов для выбранной системы счисления");
        break;
    case(20):
        strcpy(context->errorLine, "Входное значение выходит за пределы диапазона 4-байтового знакового целого числа");
        break;
    }
}
