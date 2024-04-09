//
// Created by Home on 08.04.2024.
//

#ifndef FIRST_LAB_BADAMOUNTOFVERTICES_H
#define FIRST_LAB_BADAMOUNTOFVERTICES_H

#include <stdexcept>
#include <string>

#define BAD_AMOUNT_OF_VERTICES "Polygon can not have that amount of vertices"

class BadAmountOfVertices : public std::exception {
private:
    std::string message;

public:
    explicit BadAmountOfVertices(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //FIRST_LAB_BADAMOUNTOFVERTICES_H
