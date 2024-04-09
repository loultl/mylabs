//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_INTERFACEOPTIONEXCEPTION_H
#define FIRST_LAB_INTERFACEOPTIONEXCEPTION_H

#include <stdexcept>
#include <string>

#define INVALID_MENU_OPTION "Interface option not found"

class InterfaceOptionException : public std::exception {
private:
    std::string message;

public:
    explicit InterfaceOptionException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //FIRST_LAB_INTERFACEOPTIONEXCEPTION_H
