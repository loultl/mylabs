//
// Created by Home on 08.04.2024.
//

#include "Triangle.h"

Triangle::Triangle(std::string n, Point c1, Point c2, Point c3): firstCoord(c1), secondCoord(c2), thirdCoord(c3) {
    if (((thirdCoord.getX() - firstCoord.getX()) * (secondCoord.getY() - firstCoord.getY())) == ((secondCoord.getX() - firstCoord.getX()) * (thirdCoord.getY() - firstCoord.getY()))) {
        throw ShapeExistanceException(SHAPE_EXISTANCE_ERROR);
    }
    name = std::move(n);
}

void Triangle::showParams() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Triangle\n";
    std::cout << "First point coordinate: (" << firstCoord.getX() << "," << firstCoord.getY() << ")\n";
    std::cout << "Second point coordinate: (" << secondCoord.getX() << "," << secondCoord.getY() << ")\n";
    std::cout << "Third point coordinate: (" << thirdCoord.getX() << "," << thirdCoord.getY() << ")\n";
}

double Triangle::findPerimeter() {
    double lenOfFirstLine = sqrt(pow((firstCoord.getX() - secondCoord.getX()), 2) + pow((firstCoord.getY() - secondCoord.getY()), 2));
    double lenOfSecondLine = sqrt(pow((firstCoord.getX() - thirdCoord.getX()), 2) + pow((firstCoord.getY() - thirdCoord.getY()), 2));
    double lenOfThirdLine = sqrt(pow((secondCoord.getX() - thirdCoord.getX()), 2) + pow((secondCoord.getY() - thirdCoord.getY()), 2));
    return lenOfFirstLine + lenOfSecondLine + lenOfThirdLine;
}

void Triangle::showPerimeter() {
    std::cout << "Name: " << name << "\n";
    std::cout << "Type: Triangle\n";
    std::cout << "Perimeter: " << findPerimeter() << "\n";
}