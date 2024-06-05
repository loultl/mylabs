cmake_minimum_required(VERSION 3.27)
project(first_lab)

set(CMAKE_CXX_STANDARD 23)

add_executable(first_lab main.cpp
        Interface/Interface.cpp
        Interface/Interface.h
        Shape/Shape.h
        Shape/Triangle/Triangle.cpp
        Shape/Triangle/Triangle.h
        Shape/Rectangle/Rectangle.cpp
        Shape/Rectangle/Rectangle.h
        Shape/Circle/Circle.cpp
        Shape/Circle/Circle.h
        Point/Point.cpp
        Point/Point.h
        Exceptions/ShapeExistanceException.h
        Exceptions/EmptyList.h
        Exceptions/BadShapeName.h
        Exceptions/BadShapeNumberForDeletion.h
        Exceptions/BadInputType.h
        Exceptions/InterfaceOptionException.h)
