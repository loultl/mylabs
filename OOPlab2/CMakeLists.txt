cmake_minimum_required(VERSION 3.27)
project(second_lab)

set(CMAKE_CXX_STANDARD 20)

add_executable(second_lab main.cpp
        Errors/EmptyListError.h
        Errors/IndexError.h
        Errors/InvalidSize.h
        Iterator/Iterator.h
        List/List.h
        Node/Node.h
        Testing/Testing.cpp
        Testing/Testing.h
        Errors/Errors.h
)
