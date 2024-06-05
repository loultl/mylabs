//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_TRIANGLE_H
#define FIRST_LAB_TRIANGLE_H

#include "../Shape.h"
#include "../../Point/Point.h"

class Triangle: public Shape {
private:
    Point firstCoord;
    Point secondCoord;
    Point thirdCoord;
    double perimeterTriangle;
public:
    Triangle(std::string n, Point &c1, Point &c2, Point &c3, double perimeter);
    std::string getParameters() override;
    std::string getPerimeters() override;
    double getPerimeter() override;
};

#endif //FIRST_LAB_TRIANGLE_H
