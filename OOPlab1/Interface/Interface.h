//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_INTERFACE_H
#define FIRST_LAB_INTERFACE_H

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <utility>
#include "../Point/Point.h"
#include "../Shape/Shape.h"
#include "../Shape/Triangle/Triangle.h"
#include "../Shape/Rectangle/Rectangle.h"
#include "../Shape/Circle/Circle.h"
#include "../Exceptions/ShapeExistanceException.h"
#include "../Exceptions/InterfaceOptionException.h"
#include "../Exceptions/BadShapeName.h"
#include "../Exceptions/BadShapeNumberForDeletion.h"
#include "../Exceptions/BadInputType.h"
#include "../Exceptions/EmptyList.h"

#define RUNNING_INTERFACE 1
#define STOP_INTERFACE 0

#define ADD_TRIANGLE_KEY 1
#define ADD_RECTANGLE_KEY 2
#define ADD_CIRCLE_KEY 3

#define ADD_SHAPE_KEY 1
#define PRINT_SHAPES_WITH_PARAMETERS_KEY 2
#define PRINT_SHAPES_WITH_PERIMETERS_KEY 3
#define PRINT_SUM_OF_PERIMETERS_KEY 4
#define SORT_SHAPES_KEY 5
#define DELETE_SHAPE_BY_NUMBER_KEY 6
#define DELETE_SHAPE_BY_PERIMETER_KEY 7
#define EXIT_INTERFACE_KEY 8

class Interface {
private:

    using MethodPtr = void (Interface::*)();
    void callMethod(const int& methodName);
    void callShapeMethod(const int& methodName);

    std::vector<Shape*> shapes;
    std::map<int, MethodPtr> interfaceOptions;
    std::map<int, MethodPtr> figuresOptions;

    void showInterface();
    void addShape();
    void showShapes();
    void showPerimeters();
    void printSumOfPerimeters();
    void sortShapesByPerimeter();
    void deleteShapeByNumber();
    void deleteShapesByPerimeter();
    void initializeInterfaceOptions();
    void initializeShapesOptions();
    void exitFromInterface();

    void addTriangle();
    void addCircle();
    void addRectangle();

    Circle* getCircle();
    Triangle* getTriangle();
    Rectangle* getRectangle();

    int checkForInt(int &choice);
    static bool comparePerimeter(Shape* f1, Shape* f2);

    void runInterface();
    int interfaceRunningStatus;

    template<typename T>
    T getValue();

public:
    Interface() : interfaceRunningStatus(RUNNING_INTERFACE) {
        initializeInterfaceOptions();
        initializeShapesOptions();
        runInterface();
    }
};

#endif //FIRST_LAB_INTERFACE_H
