#ifndef LINKHOLDER_CONSOLE_INVALID_RESPONSE_EXCEPTION_H
#define LINKHOLDER_CONSOLE_INVALID_RESPONSE_EXCEPTION_H

#include "exceptions/BaseHandleException.h"

/**
 * Exception in case if state returns unexpected response.
 */
class InvalidStateException : public BaseHandleException {

    const char* what() const noexcept override {
        return "InvalidStateException";
    }
};

#endif