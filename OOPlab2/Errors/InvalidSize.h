#ifndef SECOND_LAB_INVALIDSIZE_H
#define SECOND_LAB_INVALIDSIZE_H

#include <stdexcept>
#include <string>

#define INVALID_SIZE_ERROR "Invalid Size"

class InvalidSizeError : public std::exception {
private:
    std::string message;

public:
    explicit InvalidSizeError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //SECOND_LAB_INVALIDSIZE_H
