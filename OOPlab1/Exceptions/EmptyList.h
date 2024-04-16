//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_EMPTYLIST_H
#define FIRST_LAB_EMPTYLIST_H

#include <stdexcept>
#include <string>

#define EMPTY_LIST "The list of shapes is empty."

class EmptyList : public std::exception {
private:
    std::string message;

public:
    explicit EmptyList(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};


#endif //FIRST_LAB_EMPTYLIST_H
