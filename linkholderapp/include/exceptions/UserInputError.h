#ifndef LINKHOLDER_CONSOLE_USER_INPUT_EXCEPTION_H
#define LINKHOLDER_CONSOLE_USER_INPUT_EXCEPTION_H

#include <string>

#include "exceptions/BaseHandleException.h"


class UserInputError : public BaseHandleException {

public:
    UserInputError(std::string&& input, std::string&& message)
        : BaseHandleException(("Input error: " + message + ". You entered: " + input + ".").c_str()) {}
};

#endif