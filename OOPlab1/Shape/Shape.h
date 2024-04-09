//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_SHAPE_H
#define FIRST_LAB_SHAPE_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <utility>
#include "cmath"
#include "../Exceptions/ShapeExistanceException.h"
#include "../Point/Point.h"

class Shape {
protected:
    std::string name;
public:
    virtual ~Shape() = default;
    virtual double findPerimeter() = 0;
    virtual void showParams() = 0;
    virtual void showPerimeter() = 0;
};

#endif //FIRST_LAB_SHAPE_H
