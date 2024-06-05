//
// Created by Home on 08.04.2024.
//

#include "Interface.h"

void Interface::runInterface() {
    interfaceRunningStatus = RUNNING_INTERFACE;
    do {
        showInterface();
        try {
            int choice;
            if (!checkForInt(choice)) {
                std::cin.clear();
                std::cin.ignore();
                throw InterfaceOptionException(INVALID_MENU_OPTION);
            }
            std::cout << "\n";
            callMethod(choice);
        } catch (const std::exception &error) {
            std::cerr << error.what() << "\n";
        }

    } while (interfaceRunningStatus);
}

void Interface::showInterface() {
    std::cout << "Interface:\n"
                 "1.Add the selected shape to the collection of shapes\n"
                 "2.Output a list of shapes with the shape type and its parameters\n"
                 "3.Output a list of shapes with the type of shape and its perimeter\n"
                 "4.Output the sum of the perimeters of all shapes\n"
                 "5.Sort the shapes by their perimeters\n"
                 "6.Delete a shape by its number\n"
                 "7.Delete shapes whose perimeters are larger than your number\n"
                 "8.Exit\n";
}

void Interface::addShape() {
    int choice;
    std::cout << "Choose a shape you want to add:\n"
                 "Triangle (1)\n"
                 "Rectangle (2)\n"
                 "Circle (3)\n";
    if (!checkForInt(choice)) {
        std::cin.clear();
        std::cin.ignore();
        throw BadShapeName(BAD_FIGURE_NAME);
    }
    std::cout << "\n";
    callShapeMethod(choice);
    std::cout << "Shape added successfully!\n";
}

void Interface::addTriangle() {
    Triangle *triangle = getTriangle();
    shapes.push_back(triangle);
}

Triangle *Interface::getTriangle() {
    std::string name;
    std::cout << "Enter a name for your shape:\n";
    std::cin >> name;
    std::cin.ignore();
    std::cout << "Enter first coordinate:\n";
    Point firstCoordinate(0, 0);
    std::cin >> firstCoordinate;
    std::cout << "Enter second coordinate:\n";
    Point secondCoordinate(0, 0);
    std::cin >> secondCoordinate;
    std::cout << "Enter third coordinate:\n";
    Point thirdCoordinate(0, 0);
    std::cin >> thirdCoordinate;
    double perimeter = INIT_PERIMETER;
    return new Triangle(name, firstCoordinate, secondCoordinate, thirdCoordinate, perimeter);
}

void Interface::addCircle() {
    Circle *circle = getCircle();
    shapes.push_back(circle);
}

Circle *Interface::getCircle() {
    std::string name;
    std::cout << "Enter a name for your shape:\n";
    std::cin >> name;
    std::cout << "Enter center coordinate:\n";
    Point centerCoordinate(0, 0);
    std::cin >> centerCoordinate;
    std::cout << "Enter radius:\n";
    auto radius = getValue<double>();
    std::cin.ignore();
    double perimeter = INIT_PERIMETER;
    return new Circle(name, centerCoordinate, radius, perimeter);
}

void Interface::addRectangle() {
    Rectangle *rectangle = getRectangle();
    shapes.push_back(rectangle);
}

Rectangle *Interface::getRectangle() {
    std::string name;
    std::cout << "Enter a name for your shape:\n";
    std::cin >> name;
    std::cout << "Enter left upper corner coordinate:\n";
    Point upperLeftCornerCoord(0, 0);
    std::cin >> upperLeftCornerCoord;
    std::cout << "Enter right lower corner coordinate:\n";
    Point lowerRightCornerCoord(0, 0);
    std::cin >> lowerRightCornerCoord;
    double perimeter = INIT_PERIMETER;
    return new Rectangle(name, upperLeftCornerCoord, lowerRightCornerCoord, perimeter);
}

void Interface::showShapes() {
    unsigned counter = 1;
    if (shapes.empty()) {
        throw EmptyList(EMPTY_LIST);
    }
    for (const auto &shape: shapes) {
        std::cout << counter << ". ";
        std::cout << shape->getParameters();
        counter++;
    }
}

void Interface::showPerimeters() {
    unsigned counter = 1;
    if (shapes.empty()) {
        throw EmptyList(EMPTY_LIST);
    }
    for (const auto &shape: shapes) {
        std::cout << counter << ". ";
        std::cout << shape->getPerimeters();
        counter++;
    }
}

void Interface::printSumOfPerimeters() {
    if (shapes.empty()) {
        throw EmptyList(EMPTY_LIST);
    }
    double sum = 0;
    for (const auto &shape: shapes) {
        sum += shape->getPerimeter();
    }
    std::cout << "Sum of Perimeters: " << sum << "\n";
}

void Interface::sortShapesByPerimeter() {
    if (shapes.empty()) {
        throw EmptyList(EMPTY_LIST);
    }
    std::sort(shapes.begin(), shapes.end(), comparePerimeter);
    std::cout << "Shapes have been sorted!: " << "\n";
}

bool Interface::comparePerimeter(Shape *f1, Shape *f2) {
    return (f1->getPerimeter() < f2->getPerimeter());
}

void Interface::deleteShapeByNumber() {
    if (shapes.empty()) {
        throw EmptyList(EMPTY_LIST);
    }
    std::cout << "Enter an number of a shape you want to delete: " << "\n";
    int number = getValue<int>();
    if (number <= 0 || number > shapes.size()) {
        throw BadShapeNumberForDeletion(BAD_SHAPE_NUMBER);
    }
    delete shapes[number - 1];
    shapes.erase(shapes.begin() + number - 1);
    std::cout << "Shape has been deleted!\n";
}

void Interface::deleteShapesByPerimeter() {
    if (shapes.empty()) {
        throw EmptyList(EMPTY_LIST);
    }
    std::cout << "Enter a value to delete shapes with larger perimeters: " << "\n";
    auto enteredValue = getValue<double>();
    for (unsigned i = 0; i < shapes.size(); i++) {
        if (shapes[i]->getPerimeter() > enteredValue) {
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
        }
    }
    std::cout << "Shapes have been deleted!\n";
}

void Interface::exitFromInterface() {
    interfaceRunningStatus = STOP_INTERFACE;
}

void Interface::callMethod(const int &methodName) {
    auto it = interfaceOptions.find(methodName);
    if (it != interfaceOptions.end()) {
        (this->*(it->second))();
    } else {
        throw InterfaceOptionException(INVALID_MENU_OPTION);
    }
}

void Interface::callShapeMethod(const int &methodName) {
    auto it = figuresOptions.find(methodName);
    if (it != figuresOptions.end()) {
        (this->*(it->second))();
    } else {
        throw BadShapeName(BAD_FIGURE_NAME);
    }
}

void Interface::initializeInterfaceOptions() {
    interfaceOptions[ADD_SHAPE_KEY] = &Interface::addShape;
    interfaceOptions[PRINT_SHAPES_WITH_PARAMETERS_KEY] = &Interface::showShapes;
    interfaceOptions[PRINT_SHAPES_WITH_PERIMETERS_KEY] = &Interface::showPerimeters;
    interfaceOptions[PRINT_SUM_OF_PERIMETERS_KEY] = &Interface::printSumOfPerimeters;
    interfaceOptions[SORT_SHAPES_KEY] = &Interface::sortShapesByPerimeter;
    interfaceOptions[DELETE_SHAPE_BY_NUMBER_KEY] = &Interface::deleteShapeByNumber;
    interfaceOptions[DELETE_SHAPE_BY_PERIMETER_KEY] = &Interface::deleteShapesByPerimeter;
    interfaceOptions[EXIT_INTERFACE_KEY] = &Interface::exitFromInterface;
}

void Interface::initializeShapesOptions() {
    figuresOptions[ADD_TRIANGLE_KEY] = &Interface::addTriangle;
    figuresOptions[ADD_RECTANGLE_KEY] = &Interface::addRectangle;
    figuresOptions[ADD_CIRCLE_KEY] = &Interface::addCircle;
}

int Interface::checkForInt(int &choice) {
    int correctInput = 1;
    std::string stringForCheck;
    std::cin >> stringForCheck;
    for (char i: stringForCheck) {
        if (!isdigit(i)) {
            correctInput = 0;
            break;
        }
    }
    choice = atoi(stringForCheck.c_str());
    return correctInput;

}

template<typename T>
T Interface::getValue() {
    T value;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        throw BadInputType(BAD_VALUE_TYPE);
    }
    return value;
}