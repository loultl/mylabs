#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#include "errors.h"

struct AppContext {
    const char* inputValue;
    const char* translatedValue;
    int inputNumSystem;
    int outputNumSystem;
    Errors errorCode;
};

#endif // APPCONTEXT_H
