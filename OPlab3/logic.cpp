#include "logic.h"

void initialize(AppContext* context) {
    context->min = INITIALIZE_METRICS_VALUE;
    context->max = INITIALIZE_METRICS_VALUE;
    context->median = INITIALIZE_METRICS_VALUE;
    context->errorData = NoErrors;
    context->numberOfLines = INITIALIZE_METRICS_VALUE;
    context->numberOfErrorLines = INITIALIZE_METRICS_VALUE;
    context->numberOfSuccessLines = INITIALIZE_METRICS_VALUE;
    context->lastYear = INITIALIZE_METRICS_FOR_LAST_YEAR;
    context->firstYear = INITIALIZE_METRICS_FOR_FIRST_YEAR;
    context->table = NULL;
    strcpy(context->fileName,"");   
}

void setFileName(AppContext* context,char* fileName) {
    strcpy(context->fileName, fileName);
    context->numberOfErrorLines = INITIALIZE_METRICS_VALUE;
    context->numberOfSuccessLines = INITIALIZE_METRICS_VALUE;
    context->numberOfLines = INITIALIZE_METRICS_VALUE;
}

void setRegion(AppContext* context, char* region) {
    strcpy(context->region, region);
}

void setIndex(AppContext* context, char* column) {
    strcpy(context->column, column);
}

void load(AppContext* context) {

    if (!strcmp(context->fileName, "")) {
        context->errorData = EmptyFileNameError;
    } else {
        FILE *file;
        file = fopen(context->fileName, "r");

        if (file) {
            char* fline = (char*)malloc(LINE_MAX_LENGHT);

            readline(file, fline);
            strcpy(context->tableHeader, fline);
            free(fline);

            char* line = (char*)malloc(LINE_MAX_LENGHT);
            int successRead = readline(file, line);
            FileLine firstLine;
            int numberOfLines = 0;
            int numberOfErrorLines = 0;
            int numberOfSuccessLines = 0;
            if (successRead && addLineToStruct(line, &firstLine)) {
                numberOfSuccessLines++;
            } else {
                numberOfErrorLines++;
            }
            numberOfLines++;
            free(line);
            int freeList = 0;
            List* list = init(firstLine);
            while (!feof(file)) {
                FileLine currentLine;
                char* line = (char*)malloc(LINE_MAX_LENGHT);
                if (line == NULL) {
                    context->errorData = MemoryAllocationError;
                    freeList = 1;
                    break;
                } else {
                    int successRead = readline(file, line);
                    if (successRead && addLineToStruct(line, &currentLine)) {
                        numberOfSuccessLines+=1;
                        pushEnd(list, currentLine);
                    } else {
                        numberOfErrorLines+=1;
                    }
                    numberOfLines+=1;
                    free(line);
                }
            }
            if (!freeList) {
                context->table = list;
                context->numberOfErrorLines = numberOfErrorLines;
                context->numberOfLines = numberOfLines;
                context->numberOfSuccessLines = numberOfSuccessLines;
                context->errorData = NoErrors;
            } else {
                deleteList(list);
            }
            fclose(file);
        } else {
            context->errorData = FileError;
        }
    }

}

void calculate(AppContext* context) {

    if (strcmp(context->fileName,"")) {
        if (context->table != NULL ) {
            int doCalculate = 1;
            if (!isInt(context->column) || (isInt(context->column) && (stringToInt(context->column) > 7 || (stringToInt(context->column) < 3 && stringToInt(context->column) != 1)))){
                doCalculate = 0;
                context->errorData = ColumnError;
                context->min = INITIALIZE_METRICS_VALUE;
                context->max = INITIALIZE_METRICS_VALUE;
                context->median = INITIALIZE_METRICS_VALUE;
            }
            if (doCalculate) {
                if (!strcmp(context->region,"")) {
                    double* columnData = (double*)malloc(sizeof(double) * context->numberOfSuccessLines);
                    double min = returnField(context->table->first, stringToInt(context->column));
                    double max = min;
                    calculateData(context, context->table, context->region, stringToInt(context->column), &min, &max, columnData);
                    double median = findMedian(columnData, context->numberOfSuccessLines);
                    free(columnData);
                    context->median = median;
                    context->max = max;
                    context->min = min;
                    context->errorData = NoErrors;
                } else {
                    int counter = countRegionAppear(context->table, context->region);
                    if (!counter) {
                        context->errorData = RegionError;
                        context->min = INITIALIZE_METRICS_VALUE;
                        context->max = INITIALIZE_METRICS_VALUE;
                        context->median = INITIALIZE_METRICS_VALUE;
                    } else {
                        double min = findfirstAppearance(context->table, context->region, stringToInt(context->column));
                        double max = findfirstAppearance(context->table, context->region, stringToInt(context->column));
                        double* columnData = (double*)malloc(sizeof(double) * counter);
                        calculateData(context, context->table, context->region, stringToInt(context->column), &min, &max, columnData);
                        double median = findMedian(columnData, counter);
                        free(columnData);
                        context->median = median;
                        context->max = max;
                        context->min = min;
                        context->errorData = NoErrors;
                    }
                }
            }
        } else {
            context->errorData = EmptyTableError;
            context->min = INITIALIZE_METRICS_VALUE;
            context->max = INITIALIZE_METRICS_VALUE;
            context->median = INITIALIZE_METRICS_VALUE;
        }
    } else {
        context->errorData = EmptyFileNameError;
        context->min = INITIALIZE_METRICS_VALUE;
        context->max = INITIALIZE_METRICS_VALUE;
        context->median = INITIALIZE_METRICS_VALUE;
    }
}

int readline(FILE* stream, char* str) {
    int isSuccess = 0;
    isSuccess += fgets(str, LINE_MAX_LENGHT, stream) == NULL ? 0: 1;
    int len = strlen(str);
    if (str[len - 1] == '\n')
        str[len - 1] = '\0';
    return isSuccess;
}

int addLineToStruct(char* str, FileLine* line) {
    int isSuccess = 1;
    char* token = strtok(str, ",");
    if (token != NULL && isInt(token)) {
        line->year = stringToInt(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess) {
        strcpy(line->region, token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess && isDouble(token)) {
        line->naturalPopulationGrowth = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess && isDouble(token)) {
        line->birthRate = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess && isDouble(token)) {
        line->deathRate = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess && isDouble(token)) {
        line->generalDemographicWeight = stringToDouble(token);
    } else {
        isSuccess = 0;
    }

    token = strtok(NULL, ",");
    if (token != NULL && isSuccess && isDouble(token)) {
        line->urbanisation = stringToDouble(token);
    } else {
        isSuccess = 0;
    }
    return isSuccess;
}

int isInt(char* str) {
    char* endptr;
    int isInt = 0;
    strtol(str, &endptr, 10);

    if (*endptr == '\0') {
        isInt = 1;
    }
    return isInt;
}

int isDouble(char* str) {
    char* endptr;
    int isDouble = 0;
    strtod(str, &endptr);

    if (*endptr == '\0') {
        isDouble = 1;
    }

    return isDouble;
}

int stringToInt(char* string) {
    return atoi(string);
}

double stringToDouble(char* string) {
    return atof(string);
}

int countRegionAppear(List* table, char* region) {
    Node* p = table->first;
    int counter = 0;

    do {
        if (!strcmp(p->data.region, region)) {
            counter++;
        }
        p = p->next;
    } while (p != NULL);
    return counter;
}

double findfirstAppearance(List* table, char* region, int column) {
    Node* p = table->first;
    double metric = 0;

    do {
        if (strcmp(p->data.region, region) == 0) {
            metric = returnField(p, column);
        }
        p = p->next;
    } while (p != NULL);
    return metric;
}


double returnField(Node* p, int column) {
    double field = 0;
    switch(column) {
    case 1:
        field = p->data.year;
        break;
    case 3:
        field = p->data.naturalPopulationGrowth;
        break;
    case 4:
        field = p->data.birthRate;
        break;
    case 5:
        field = p->data.deathRate;
        break;
    case 6:
        field = p->data.generalDemographicWeight;
        break;
    case 7:
        field = p->data.urbanisation;
        break;
    }
    return field;
}

void calculateData(AppContext* context, List* table,char* region, int column, double* min, double* max, double* columnData) {
    Node* p = table->first;
    int counter = 0;

    do {
        if (strcmp(p->data.region, region) == 0 || strcmp("", region) == 0) {
            double metric = returnField(p, column);
            if (metric > *max) {
                *max = metric;
            } else if (metric < *min) {
                *min = metric;
            }
            if (p->data.year > context->lastYear) {
                context->lastYear = p->data.year;
            }
            if (p->data.year < context->firstYear) {
                context->firstYear = p->data.year;
            }
            columnData[counter] = metric;
            counter++;
        }
        p = p->next;
    } while (p != NULL);
}


double findMedian(double* columnData, int counter) {
    sort(columnData, counter);
    double median;

    if (counter % 2 != 0) {
        median = columnData[counter/2];
    } else {
        median = (columnData[counter/2 - 1]+columnData[counter/2]) / 2;
    }
    return median;
}

void swap(double* x, double* y) {
    double temp = *x;
    *x = *y;
    *y = temp;
}

void sort(double arr[], int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (*(arr + i) > *(arr + j))
                swap(arr + i, arr + j);
}
