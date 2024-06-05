//
// Created by Home on 08.04.2024.
//

#include "Circle.h"

Circle::Circle(std::string n, Point &center, double r, double perimeter): centerCoordinate(center), radius(r), perimeterCircle(perimeter) {
    if (r <= 0) {
        throw ShapeExistanceException(SHAPE_EXISTANCE_ERROR);
    }
    perimeterCircle = 2 * M_PI * radius;
    name = std::move(n);
}

std::string Circle::getParameters() {
    std::string stringForParameters;
    stringForParameters += "Name: " + name + "\n" + "Type: Circle\n";
    stringForParameters += "Center coordinate: (" + std::to_string(centerCoordinate.getX()) + "," + std::to_string(centerCoordinate.getY()) + ")\n";
    stringForParameters += "Radius: " + std::to_string(radius) + "\n";
    return stringForParameters;
}

double Circle::getPerimeter() {
    return perimeterCircle;
}

std::string Circle::getPerimeters() {
    std::string stringForPerimeters;
    stringForPerimeters += "Name: " + name + "\n" + "Type: Circle\n";
    stringForPerimeters += "Perimeter: " + std::to_string(getPerimeter()) + "\n";
    return stringForPerimeters;
}