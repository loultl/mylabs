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
public:
    Rectangle(std::string n, Point c1, Point c2);
    void showParams() override;
    void showPerimeter() override;
    double findPerimeter() override;
};

#endif //FIRST_LAB_RECTANGLE_H
