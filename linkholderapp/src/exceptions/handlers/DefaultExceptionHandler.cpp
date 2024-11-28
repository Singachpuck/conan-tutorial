#include "exceptions/handlers/DefaultExceptionHandler.h"

#include <iostream>


void DefaultExceptionHandler::handle(BaseHandleException& ex) {
    std::cerr << ex.what() << std::endl << std::endl;
}