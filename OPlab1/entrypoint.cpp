#include "entrypoint.h"
#include "logic.h"

void doOperation(Operation operation, AppContext* context, AppParams* params) {
    switch(operation) {
    case Initialization:
        initialize(context);
        break;
    case InputOfInputNumSystem:
        inputOfInputNumSystem(context, params->inputNumSystem, params->whichInputRadioButton);
        break;
    case InputOfOutputNumSystem:
        inputOfOutputNumSystem(context, params->outputNumSystem, params->whichOutputRadioButton);
        break;
    case InputOfValue:
        inputOfValue(context, params->newValue);
        break;
    case Validation:
        setErrorCode(context, params->newValue);
        break;
    case Translate:
        translate(context, params->newValue);
        break;
    case TranslateForSwap:
        translate(context, context->inputValue);
        break;
    case Swap:
        swap(context);
        break;
    }
}
