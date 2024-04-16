//
// Created by Home on 08.04.2024.
//

#include "Interface.h"

void Interface::runInterface() {
    interfaceRunningStatus = 1;
    initializeInterfaceOptions();
    initializeShapesOptions();

    do {
        showInterface();
        try {
            int choice;
            if (!checkForInt(choice)) {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                throw InterfaceOptionException(INVALID_MENU_OPTION);
            }
            std::cout << "\n";
            callMethod(choice);
        } catch (const BadInputType &error) {
            std::cerr << error.what() << "\n";
        } catch (const ShapeExistanceException &error) {
            std::cerr << error.what() << "\n";
        } catch (const BadShapeName &error) {
            std::cerr << error.what() << "\n";
        } catch (const EmptyList &error) {
            std::cerr << error.what() << "\n";
        } catch (const BadIndexForDeletion &error) {
            std::cerr << error.what() << "\n";
        } catch (const InterfaceOptionException &error) {
            std::cerr << error.what() << "\n";
        }

    } while (interfaceRunningStatus == 1);
}

void Interface::showInterface() {
    std::cout << "Interface:\n"
                 "1.Add the selected shape to the collection of shapes\n"
                 "2.Output a list of shapes with the shape type and its parameters\n"
                 "3.Output a list of shapes with the type of shape and its perimeter\n"
                 "4.Output the sum of the perimeters of all shapes\n"
                 "5.Sort the shapes by their perimeters\n"
                 "6.Delete a shape from the collection by its number\n"
                 "7.Delete shapes whose perimeters are larger than your number\n"
                 "8.Exit\n";
}

void Interface::addShape() {
    int choice;
    std::cout << "Choose a shape you want to add:\n"
                 "Triangle (1)\n"
                 "Rectangle (2)\n"
                 "Polygon (3)\n"
                 "Circle (4)\n";
    if (!checkForInt(choice)) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
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
    std::cout << "Enter coordinates of three points:\n";
    auto xOfFirstPoint = getValue<double>();
    auto yOfFirstPoint = getValue<double>();
    auto xOfSecondPoint = getValue<double>();
    auto yOfSecondPoint = getValue<double>();
    auto xOfThirdPoint = getValue<double>();
    auto yOfThirdPoint = getValue<double>();
    Point firstPoint(xOfFirstPoint, yOfFirstPoint);
    Point secondPoint(xOfSecondPoint, yOfSecondPoint);
    Point thirdPoint(xOfThirdPoint, yOfThirdPoint);
    std::cin.ignore(32767, '\n');
    return new Triangle(name, firstPoint, secondPoint, thirdPoint);
}

void Interface::addCircle() {
    Circle *circle = getCircle();
    shapes.push_back(circle);
}

Circle *Interface::getCircle() {
    std::string name;
    std::cout << "Enter a name for your shape:\n";
    std::cin >> name;
    std::cout << "Enter coordinates of centre and radius:\n";
    auto xOfCenter = getValue<double>();
    auto yOfCenter = getValue<double>();
    Point centerCoordinate(xOfCenter, yOfCenter);
    auto radius = getValue<double>();
    std::cin.ignore(32767, '\n');
    return new Circle(name, centerCoordinate, radius);
}

void Interface::addRectangle() {
    Rectangle *rectangle = getRectangle();
    shapes.push_back(rectangle);
}

Rectangle *Interface::getRectangle() {
    std::string name;
    std::cout << "Enter a name for your shape:\n";
    std::cin >> name;
    std::cout << "Enter coordinates of two points:\n";
    auto xOfUpperLeftCorner = getValue<double>();
    auto yOfUpperLeftCorner = getValue<double>();
    auto xOfLowerRightCorner = getValue<double>();
    auto yOfLowerRightCorner = getValue<double>();
    Point upperLeftCornerCoord(xOfUpperLeftCorner, yOfUpperLeftCorner);
    Point lowerRightCornerCoord(xOfLowerRightCorner, yOfLowerRightCorner);
    std::cin.ignore(32767, '\n');
    return new Rectangle(name, upperLeftCornerCoord, lowerRightCornerCoord);
}


void Interface::addPolygon() {
    Polygon *polygon = getPolygon();
    shapes.push_back(polygon);
}

Polygon *Interface::getPolygon() {
    std::string name;
    std::cout << "Enter a name for your shape:\n";
    std::cin >> name;
    std::cout << "Enter how many vertices your shape will have:\n";
    int amountOfVertices = getValue<int>();
    if (amountOfVertices < 3) {
        throw ShapeExistanceException(SHAPE_EXISTANCE_ERROR);
    }
    std::cout << "Enter coordinates of " << amountOfVertices << " points:\n";
    std::vector<Point *> coordinates;
    for (int i = 0; i < amountOfVertices; i++) {
        auto xOfPoint = getValue<double>();
        auto yOfPoint = getValue<double>();
        auto p = new Point(xOfPoint, yOfPoint);
        coordinates.push_back(p);
    }
    std::cin.ignore(32767, '\n');
    return new Polygon(name, coordinates);
}

void Interface::showShapes() {
    unsigned counter = 1;
    if (shapes.empty()) {
        throw EmptyList(EMPTY_LIST);
    }
    for (const auto &shape: shapes) {
        std::cout << counter << ". ";
        shape->showParams();
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
        shape->showPerimeter();
        counter++;
    }
}

void Interface::printSumOfPerimeters() {
    if (shapes.empty()) {
        throw EmptyList(EMPTY_LIST);
    }
    double sum = 0;
    for (const auto &shape: shapes) {
        sum += shape->findPerimeter();
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
    return (f1->findPerimeter() < f2->findPerimeter());
}

void Interface::deleteShapeByIndex() {
    if (shapes.empty()) {
        throw EmptyList(EMPTY_LIST);
    }
    std::cout << "Enter an index of a shape you want to delete: " << "\n";
    int index = getValue<int>();
    if (index < 0 || index > shapes.size()) {
        throw BadIndexForDeletion(BAD_LIST_INDEX);
    }
    delete shapes[index];
    shapes.erase(shapes.begin() + index);
    std::cout << "Shape has been deleted!\n";
}

void Interface::deleteShapesByPerimeter() {
    if (shapes.empty()) {
        throw EmptyList(EMPTY_LIST);
    }
    std::cout << "Enter a value to delete shapes with larger perimeters: " << "\n";
    auto enteredValue = getValue<double>();
    for (unsigned i = 0; i < shapes.size(); i++) {
        if (shapes[i]->findPerimeter() > enteredValue) {
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
        }
    }
    std::cout << "Shapes have been deleted!\n";
}

void Interface::exitFromInterface() {
    interfaceRunningStatus = 0;
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
    interfaceOptions[1] = &Interface::addShape;
    interfaceOptions[2] = &Interface::showShapes;
    interfaceOptions[3] = &Interface::showPerimeters;
    interfaceOptions[4] = &Interface::printSumOfPerimeters;
    interfaceOptions[5] = &Interface::sortShapesByPerimeter;
    interfaceOptions[6] = &Interface::deleteShapeByIndex;
    interfaceOptions[7] = &Interface::deleteShapesByPerimeter;
    interfaceOptions[8] = &Interface::exitFromInterface;
}

void Interface::initializeShapesOptions() {
    figuresOptions[1] = &Interface::addTriangle;
    figuresOptions[2] = &Interface::addRectangle;
    figuresOptions[3] = &Interface::addPolygon;
    figuresOptions[4] = &Interface::addCircle;
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
        std::cin.ignore(32767, '\n');
        throw BadInputType(BAD_VALUE_TYPE);
    }
    return value;
}