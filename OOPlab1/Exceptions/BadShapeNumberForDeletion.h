//
// Created by Home on 08.04.2024.


#ifndef FIRST_LAB_BADSHAPENUMBERFORDELETION_H
#define FIRST_LAB_BADSHAPENUMBERFORDELETION_H

#include <stdexcept>
#include <string>

#define BAD_SHAPE_NUMBER "There is no such number"

class BadShapeNumberForDeletion : public std::exception {
private:
    std::string message;

public:
    explicit BadShapeNumberForDeletion(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //FIRST_LAB_BADSHAPENUMBERFORDELETION_H
