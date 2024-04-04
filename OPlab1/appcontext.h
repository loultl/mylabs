#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#include "errors.h"

struct AppContext {
    char* inputValue;
    char* translatedValue;
    int inputNumSystem;
    int outputNumSystem;
    Error errorCode;
};

#endif // APPCONTEXT_H
