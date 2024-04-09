//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_BADSHAPENAME_H
#define FIRST_LAB_BADSHAPENAME_H

#include <stdexcept>
#include <string>

#define BAD_FIGURE_NAME "There is no such shape for your choice"

class BadShapeName : public std::exception {
private:
    std::string message;

public:
    explicit BadShapeName(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //FIRST_LAB_BADSHAPENAME_H
