#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"

enum Operation
{
    Initialization,
    InputOfInputNumSystem,
    InputOfOutputNumSystem,
    InputOfValue,
    Validation,
    FillErrorLine,
    Translate,
    Swap
};

struct AppParams {
    const char* newValue;
    int inputNumSystem;
    int outputNumSystem;
};

void doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
