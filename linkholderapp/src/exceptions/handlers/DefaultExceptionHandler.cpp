#include "exceptions/handlers/DefaultExceptionHandler.h"

#include <iostream>


void DefaultExceptionHandler::handle(const BaseHandleException& ex) {
    std::cout << ex.what() << '\n' << std::endl;
}