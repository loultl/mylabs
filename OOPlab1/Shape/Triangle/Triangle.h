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
public:
    Triangle(std::string n, Point c1, Point c2, Point c3);
    void showParams() override;
    void showPerimeter() override;
    double findPerimeter() override;
};

#endif //FIRST_LAB_TRIANGLE_H
