#ifndef LINKHOLDER_CONSOLE_USER_INPUT_EXCEPTION_H
#define LINKHOLDER_CONSOLE_USER_INPUT_EXCEPTION_H

#include <string>

#include "exceptions/BaseHandleException.h"


class UserInputError : public BaseHandleException {

private:
    std::string input;
    std::string message;

public:
    UserInputError(std::string&& input, std::string&& message) : input(input), message(message) {}

    const char* what() const noexcept override {
        return ("Input error: " + message + ". You entered: " + input + ".").c_str();
    }
};

#endif