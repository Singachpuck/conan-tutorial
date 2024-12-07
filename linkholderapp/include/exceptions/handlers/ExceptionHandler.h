#ifndef LINKHOLDER_CONSOLE_EXCEPTION_HANDLER_H
#define LINKHOLDER_CONSOLE_EXCEPTION_HANDLER_H

#include <memory>

#include "exceptions/BaseHandleException.h"

class ExceptionHandler {
public:
    virtual void handle(const BaseHandleException& ex) = 0;
};

#endif