#include "entrypoint.h"
#include "logic.h"

void doOperation(Operation operation, AppContext* context, AppParams* params) {
    switch(operation) {
    case Initialization:
        initialize(context);
        break;
    case InputOfInputNumSystem:
        inputOfInputNumSystem(context, params->inputNumSystem);
        break;
    case InputOfOutputNumSystem:
        inputOfOutputNumSystem(context, params->outputNumSystem);
        break;
    case InputOfValue:
        inputOfValue(context, params->newValue);
        break;
    case Validation:
        validate(context, params->newValue, 0);
        break;
    case Translate:
        translate(context, params->newValue);
        break;
    case Swap:
        swap(context, params->newValue, context->inputNumSystem, context->outputNumSystem);
        break;
    }
}
