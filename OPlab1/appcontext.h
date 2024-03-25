#ifndef APPCONTEXT_H
#define APPCONTEXT_H

struct AppContext {
    const char* inputValue;
    int inputNumSystem;
    int outputNumSystem;
    int whichInputRadioButton;
    int whichOutputRadioButton;
    const char* translatedValue;
    char errorLine[200];
    int errorCode;
};

#endif // APPCONTEXT_H
