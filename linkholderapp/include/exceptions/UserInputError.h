#ifndef LINKHOLDER_CONSOLE_USER_INPUT_EXCEPTION_H
#define LINKHOLDER_CONSOLE_USER_INPUT_EXCEPTION_H

#include <exception>
#include <string>

class UserInputError : public std::exception {

private:
    std::string input;
    std::string message;

public:
    UserInputError(std::string input, std::string message) : input(input), message(message) {}

    const char* what() const noexcept override {
        return input.c_str();
    }
};

#endif