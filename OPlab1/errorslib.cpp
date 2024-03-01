#include "errorslib.h"
#include "logic.h"
#include <cctype>
#include <cmath>
#include <cstring>

void setErrorCode(AppContext* context, const char* input, int inputNumSystem)
{
    if (inputNumSystem == 10)
    {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if ((i == 0 && !(input[i] == '-' || isdigit(input[i]))) || (i > 0 && !isdigit(input[i])))
            {
                context->errorCode = 1;
            }
            else if (stringToInt(input) > pow(2, BIT_LIMIT) || stringToInt(input) < -pow(2, BIT_LIMIT))
            {
                context->errorCode = 2;
            }
        }
    } else if (inputNumSystem == 2) {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if (input[i] != '0' && input[i] != '1')
            {
                context->errorCode = 1;
            }
            else if (strlen(input) > BIT_LIMIT + 1)
            {
                context->errorCode = 2;
            }
        }
    } else if (inputNumSystem == 8) {
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if (input[i] < '0' || input[i] > '7')
            {
                context->errorCode = 1;
            }
            else if (strlen(input) > (BIT_LIMIT + 1) / 3 + 1)
            {
                context->errorCode = 2;
            }
        }
    }
}

void setError(AppContext* context)
{
    switch(context->errorCode)
    {
    case(1):
        strcpy(context->errorLine, "Недопустимый ввод для выбранной системы счисления");
        break;
    case(2):
        strcpy(context->errorLine, "Входное значение выходит за пределы 4-байтового знакового числа");
        break;
    }
}
