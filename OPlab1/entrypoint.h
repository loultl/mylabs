#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"

enum Operation
{
    Initialization,
    InputOfInputNumSystem,
    InputOfOutputNumSystem,
    InputOfValue,
    Validation,
    Translate,
    Swap
};

struct AppParams {
    char* newValue;
    int inputNumSystem;
    int outputNumSystem;
};

void doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
