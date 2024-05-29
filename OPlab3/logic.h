
#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include "list.h"
#include "error.h"

#define INITIALIZE_METRICS_VALUE 0
#define INITIALIZE_METRICS_FOR_LAST_YEAR -10000
#define INITIALIZE_METRICS_FOR_FIRST_YEAR 10000

void initialize(AppContext* context);
void load(AppContext* context);
void calculate(AppContext* context);

void setFileName(AppContext* context, char* fileName);
void setRegion(AppContext* context, char* region);
void setIndex(AppContext* context, char* column);

int readline(FILE* stream, char* str);
int addLineToStruct(char* str, FileLine* line);

void calculateData(AppContext* context, List* table, char* region, int column, double* min, double* max, double* columnData);
double findMedian(double* columnData, int counter);

int countRegionAppear(List* table, char* region);
double returnField(Node* p, int column);
double findfirstAppearance(List* table, char* region, int column);

int isInt(char* str);
int isDouble(char* str);
int stringToInt(char* string);
double stringToDouble(char* string);
void swap(double *x, double *y);
void sort(double arr[], int n);

#endif // LOGIC_H
