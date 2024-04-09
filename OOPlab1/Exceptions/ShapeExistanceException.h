//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_SHAPEEXISTANCEEXCEPTION_H
#define FIRST_LAB_SHAPEEXISTANCEEXCEPTION_H

#include <stdexcept>
#include <string>

#define SHAPE_EXISTANCE_ERROR "Shape with these parameters cant be created"

class ShapeExistanceException : public std::exception {
private:
    std::string message;

public:
    explicit ShapeExistanceException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //FIRST_LAB_SHAPEEXISTANCEEXCEPTION_H
