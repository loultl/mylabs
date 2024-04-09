//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_POLYGON_H
#define FIRST_LAB_POLYGON_H

#include "../Shape.h"
#include "../../Point/Point.h"

class Polygon: public Shape {
private:
    std::vector<Point*> coords;
public:
    Polygon(std::string n, std::vector<Point*> coordinates);
    void showParams() override;
    void showPerimeter() override;
    double findPerimeter() override;
};

double orientation(Point* a, Point* b, Point* c);
bool isConvex(std::vector<Point*> coordinates);

#endif //FIRST_LAB_POLYGON_H
