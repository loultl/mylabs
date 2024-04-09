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
        Shape/Polygon/Polygon.cpp
        Shape/Polygon/Polygon.h
        Shape/Circle/Circle.cpp
        Shape/Circle/Circle.h
        Point/Point.cpp
        Point/Point.h
        Exceptions/ShapeExistanceException.h
        Exceptions/EmptyListForDeletion.h
        Exceptions/EmptyListForShowing.h
        Exceptions/EmptyListForSorting.h
        Exceptions/EmptyListForSumming.h
        Exceptions/BadAmountOfVertices.h
        Exceptions/BadShapeName.h
        Exceptions/BadIndexForDeletion.h
        Exceptions/BadInputType.h
        Exceptions/InterfaceOptionException.h)
