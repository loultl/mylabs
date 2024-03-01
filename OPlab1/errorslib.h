#ifndef ERRORSLIB_H
#define ERRORSLIB_H

#include "appcontext.h"

void setErrorCode(AppContext* context, const char* input, int inputNumSystem);
void setError(AppContext* context);

#endif // ERRORSLIB_H
