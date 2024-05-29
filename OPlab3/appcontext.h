#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "list.h"
#include "error.h"

struct AppContext {
    char tableHeader[LINE_MAX_LENGHT];
    double min;
    double max;
    double median;
    Error errorData;
    int numberOfLines;
    int numberOfErrorLines;
    int numberOfSuccessLines;
    int lastYear;
    int firstYear;
    List* table;
    char fileName[LINE_MAX_LENGHT];
    char region[LINE_MAX_LENGHT];
    char column[LINE_MAX_LENGHT];
};

#endif // APPCONTEXT_H
