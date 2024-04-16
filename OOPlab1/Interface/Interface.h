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
#include "../Shape/Polygon/Polygon.h"
#include "../Shape/Circle/Circle.h"
#include "../Exceptions/ShapeExistanceException.h"
#include "../Exceptions/InterfaceOptionException.h"
#include "../Exceptions/BadShapeName.h"
#include "../Exceptions/BadIndexForDeletion.h"
#include "../Exceptions/BadInputType.h"
#include "../Exceptions/EmptyList.h"

class Interface {
private:

    using MethodPtr = void (Interface::*)();
    void callMethod(const int& methodName);
    void callShapeMethod(const int& methodName);

    int interfaceRunningStatus;
    std::vector<Shape*> shapes;
    std::map<int, MethodPtr> interfaceOptions;
    std::map<int, MethodPtr> figuresOptions;

    void showInterface();
    void addShape();
    void showShapes();
    void showPerimeters();
    void printSumOfPerimeters();
    void sortShapesByPerimeter();
    void deleteShapeByIndex();
    void deleteShapesByPerimeter();
    void initializeInterfaceOptions();
    void initializeShapesOptions();
    void exitFromInterface();

    void addTriangle();
    void addCircle();
    void addRectangle();
    void addPolygon();

    Circle* getCircle();
    Triangle* getTriangle();
    Rectangle* getRectangle();
    Polygon* getPolygon();

    template<typename T>
    T getValue();
    int checkForInt(int &choice);
    static bool comparePerimeter(Shape* f1, Shape* f2);

public:
    void runInterface();
};

#endif //FIRST_LAB_INTERFACE_H
