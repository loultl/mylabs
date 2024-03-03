#include "errorslib.h"
#include "logic.h"
#include <cctype>
#include <cmath>
#include <cstring>

void setErrorCode(AppContext* context, const char* input)
{
    if (context->inputNumSystem == 10)
    {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if ((i == 0 && !(input[i] == '-' || isdigit(input[i]))) || (i > 0 && !isdigit(input[i])))
            {
                context->errorCode = 10;
            }
            else if (stringToInt(input) > pow(2, BIT_LIMIT) || stringToInt(input) < -pow(2, BIT_LIMIT))
            {
                context->errorCode = 20;
            }
            else
            {
                context->errorCode = 0;
            }
        }
    }
    if (context->inputNumSystem == 2)
    {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if (input[i] != '0' && input[i] != '1')
            {
                context->errorCode = 10;
            }
            else if (strlen(input) > BIT_LIMIT + 1)
            {
                context->errorCode = 20;
            }
            else
            {
                context->errorCode = 0;
            }
        }
    }
    if (context->inputNumSystem == 8)
    {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if (input[i] < '0' || input[i] > '7')
            {
                context->errorCode = 10;
            }
            else if (strlen(input) > (BIT_LIMIT + 1) / 3 + 1)
            {
                context->errorCode = 20;
            }
            else
            {
                context->errorCode = 0;
            }
        }
    }
}

void setError(AppContext* context)
{
    switch(context->errorCode)
    {
    case(10):
        strcpy(context->errorLine, "Введена недопустимая комбинация символов для выбранной системы счисления");
        break;
    case(20):
        strcpy(context->errorLine, "Входное значение выходит за пределы диапазона 4-байтового знакового целого числа");
        break;
    }
}
