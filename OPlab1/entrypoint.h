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

enum Errors
{
    ExitFromInt,
    IncorrectCombibationOfSymbols,
    NotCheckedInputNumSystem,
    NotCheckedOutputNumSystem,
    NotCheckedNumSystems,
    NoErrors
};

enum CheckedInputRadioButton
{
    CheckedInputBinRadioButton,
    CheckedInputOctRadioButton,
    CheckedInputDecRadioButton
};

enum CheckedOutputRadioButton
{
    CheckedOutputBinRadioButton,
    CheckedOutputOctRadioButton,
    CheckedOutputDecRadioButton
};

struct AppParams {
    const char* newValue;
    int inputNumSystem;
    int outputNumSystem;
    int whichInputRadioButton;
    int whichOutputRadioButton;
};

void doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
