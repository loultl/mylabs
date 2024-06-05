//
// Created by Home on 08.04.2024.
//

#include "Rectangle.h"

Rectangle::Rectangle(std::string n, Point &c1, Point &c2, double perimeter): upperLeftCornerCoord(c1), lowerRightCornerCoord(c2), perimeterRectangle(perimeter) {
    if (upperLeftCornerCoord.getX() == lowerRightCornerCoord.getX() || upperLeftCornerCoord.getY() == lowerRightCornerCoord.getY()) {
        throw ShapeExistanceException(SHAPE_EXISTANCE_ERROR);
    }
    double width = fabs(lowerRightCornerCoord.getX() - upperLeftCornerCoord.getX());
    double height = fabs(lowerRightCornerCoord.getY() - upperLeftCornerCoord.getY());
    perimeterRectangle = 2 * (width + height);
    name = std::move(n);
}

std::string Rectangle::getParameters() {
    std::string stringForParameters;
    stringForParameters += "Name: " + name + "\n" + "Type: Rectangle\n";
    stringForParameters += "Lower left corner coordinate: (" + std::to_string(upperLeftCornerCoord.getX()) + "," + std::to_string(upperLeftCornerCoord.getY()) + ")\n";
    stringForParameters += "Lower left corner coordinate: (" + std::to_string(lowerRightCornerCoord.getX()) + "," + std::to_string(lowerRightCornerCoord.getY()) + ")\n";
    return stringForParameters;
}

double Rectangle::getPerimeter() {
    return perimeterRectangle;
}

std::string Rectangle::getPerimeters() {
    std::string stringForPerimeters;
    stringForPerimeters += "Name: " + name + "\n" + "Type: Rectangle\n";
    stringForPerimeters += "Perimeter: " + std::to_string(getPerimeter()) + "\n";
    return stringForPerimeters;
}