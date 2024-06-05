//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_CIRCLE_H
#define FIRST_LAB_CIRCLE_H

#include "../Shape.h"
#include "../../Point/Point.h"

class Circle: public Shape {
private:
    Point centerCoordinate;
    double radius;
    double perimeterCircle = getPerimeter();
public:
    Circle(std::string n, Point &center, double r, double perimeter);
    std::string getParameters() override;
    std::string getPerimeters() override;
    double getPerimeter() override;
};

#endif //FIRST_LAB_CIRCLE_H
