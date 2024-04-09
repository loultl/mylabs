//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_EMPTYLISTFORSORTING_H
#define FIRST_LAB_EMPTYLISTFORSORTING_H

#include <stdexcept>
#include <string>

#define EMPTY_LIST_FOR_SORTING "The list of shapes is empty. There is nothing to sort"

class EmptyListForSorting : public std::exception {
private:
    std::string message;

public:
    explicit EmptyListForSorting(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //FIRST_LAB_EMPTYLISTFORSORTING_H
