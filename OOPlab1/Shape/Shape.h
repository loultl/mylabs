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

#define INIT_PERIMETER 0

class Shape {
protected:
    std::string name;
public:
    virtual ~Shape() = default;
    virtual double getPerimeter() = 0;
    virtual std::string getParameters() = 0;
    virtual std::string getPerimeters() = 0;
};

#endif //FIRST_LAB_SHAPE_H
