//
// Created by Home on 08.04.2024.
//

#include "Triangle.h"

Triangle::Triangle(std::string n, Point &c1, Point &c2, Point &c3, double perimeter): firstCoord(c1), secondCoord(c2), thirdCoord(c3), perimeterTriangle(perimeter) {
    if (((thirdCoord.getX() - firstCoord.getX()) * (secondCoord.getY() - firstCoord.getY())) == ((secondCoord.getX() - firstCoord.getX()) * (thirdCoord.getY() - firstCoord.getY()))) {
        throw ShapeExistanceException(SHAPE_EXISTANCE_ERROR);
    }
    double lenOfFirstSide = sqrt(pow(firstCoord.getX() - secondCoord.getX(), 2) + pow(firstCoord.getY() - secondCoord.getY(),2));
    double lenOfSecondSide = sqrt(pow(firstCoord.getX() - thirdCoord.getX(), 2) + pow(firstCoord.getY() - thirdCoord.getY(),2));
    double lenOfThirdSide = sqrt(pow(secondCoord.getX() - thirdCoord.getX(), 2) + pow(secondCoord.getY() - thirdCoord.getY(),2));
    perimeterTriangle = lenOfFirstSide + lenOfSecondSide + lenOfThirdSide;
    name = std::move(n);
}

std::string Triangle::getParameters() {
    std::string stringForParameters;
    stringForParameters += "Name: " + name + "\n" + "Type: Triangle\n";
    stringForParameters += "First point coordinate: (" + std::to_string(firstCoord.getX()) + "," + std::to_string(firstCoord.getY()) + ")\n";
    stringForParameters += "Second point coordinate: (" + std::to_string(secondCoord.getX()) + "," + std::to_string(secondCoord.getY()) + ")\n";
    stringForParameters += "Third point coordinate: (" + std::to_string(thirdCoord.getX()) + "," + std::to_string(thirdCoord.getY()) + ")\n";
    return stringForParameters;
}

double Triangle::getPerimeter() {
    return perimeterTriangle;
}

std::string Triangle::getPerimeters() {
    std::string stringForPerimeters;
    stringForPerimeters += "Name: " + name + "\n" + "Type: Triangle\n";
    stringForPerimeters += "Perimeter: " + std::to_string(getPerimeter()) + "\n";
    return stringForPerimeters;
}