cmake_minimum_required(VERSION 3.27)
project(second_lab)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(googletest)
add_executable(second_lab main.cpp
        Errors/EmptyListError.h
        Errors/IndexError.h
        Errors/InvalidSize.h
        Iterator/Iterator.h
        List/List.h
        Node/Node.h
        OldTesting/OldTesting.cpp
        OldTesting/OldTesting.h
        Errors/Errors.h
        Testing/Testing.h
)
target_link_libraries(second_lab gtest_main gmock_main)
