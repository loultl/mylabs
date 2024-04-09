//
// Created by Home on 08.04.2024.
//

#include "Point.h"

double Point::getX() {
    return x;
}

double Point::getY() {
    return y;
}

Point::Point(double cX, double cY): x(cX) , y(cY) {}