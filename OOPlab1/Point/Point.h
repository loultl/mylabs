//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_POINT_H
#define FIRST_LAB_POINT_H

#include <istream>
#include "../Exceptions/BadInputType.h"

class Point {
private:
    double x;
    double y;
    friend std::istream& operator >> (std::istream& cin, Point& p) {
        cin >> p.x >> p.y;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            throw BadInputType(BAD_VALUE_TYPE);
        }
        return cin;
    }
public:
    Point(double coorX, double coorY);
    double getX();
    double getY();
};


#endif //FIRST_LAB_POINT_H
