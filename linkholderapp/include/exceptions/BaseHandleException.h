#ifndef LINKHOLDER_CONSOLE_BASE_HANDLE_EXCEPTION_H
#define LINKHOLDER_CONSOLE_BASE_HANDLE_EXCEPTION_H

#include <exception>

/**
 * This exception is caught inside the main loop and is handled by the defined handler.
 * Should be inherited by all the project exceptions but ExitException.
 */
class BaseHandleException : public std::exception {
public:
    BaseHandleException() = default;
    explicit BaseHandleException(const char* const message) : std::exception(message) {}
};

#endif