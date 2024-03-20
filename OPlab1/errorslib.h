#ifndef ERRORSLIB_H
#define ERRORSLIB_H

#include "appcontext.h"

int checkDecSize(const char* input);
int checkOctSize(const char* input);
int checkBinSize(const char* input);

void setErrorCode(AppContext* context, const char* input);
void setError(AppContext* context);

#endif // ERRORSLIB_H
