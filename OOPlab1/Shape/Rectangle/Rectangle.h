//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_RECTANGLE_H
#define FIRST_LAB_RECTANGLE_H

#include "../Shape.h"
#include "../../Point/Point.h"

class Rectangle: public Shape {
private:
    Point upperLeftCornerCoord;
    Point lowerRightCornerCoord;
    double perimeterRectangle = getPerimeter();
public:
    Rectangle(std::string n, Point &c1, Point &c2, double perimeter);
    std::string getParameters() override;
    std::string getPerimeters() override;
    double getPerimeter() override;
};

#endif //FIRST_LAB_RECTANGLE_H
