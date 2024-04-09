//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_EMPTYLISTFORSHOWING_H
#define FIRST_LAB_EMPTYLISTFORSHOWING_H

#include <stdexcept>
#include <string>

#define EMPTY_LIST_FOR_SHOWING "The list of shapes is empty. There is nothing to show"

class EmptyListForShowing : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForShowing(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};


#endif //FIRST_LAB_EMPTYLISTFORSHOWING_H
