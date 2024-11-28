#ifndef LINKHOLDER_CONSOLE_DEFAULT_EXCEPTION_HANDLER_H
#define LINKHOLDER_CONSOLE_DEFAULT_EXCEPTION_HANDLER_H

#include "exceptions/handlers/ExceptionHandler.h"


class DefaultExceptionHandler : public ExceptionHandler {
public:
    void handle(BaseHandleException& ex) override;
};

#endif