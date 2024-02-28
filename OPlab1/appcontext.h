#ifndef APPCONTEXT_H
#define APPCONTEXT_H

struct AppContext {
    const char* inputValue;
    int inputNumSystem;
    int outputNumSystem;
    const char* translatedValue;
    char errorLine[100];
};

#endif // APPCONTEXT_H
