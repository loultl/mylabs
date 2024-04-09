//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_BADINPUTTYPE_H
#define FIRST_LAB_BADINPUTTYPE_H

#include <stdexcept>
#include <string>

#define BAD_VALUE_TYPE "Incorrect value type"

class BadInputType : public std::exception {
private:
    std::string message;

public:
    explicit BadInputType(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //FIRST_LAB_BADINPUTTYPE_H
