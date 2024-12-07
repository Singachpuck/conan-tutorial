#ifndef LINKHOLDER_CONSOLE_APP_MANAGER_H
#define LINKHOLDER_CONSOLE_APP_MANAGER_H

#include "StateMachine.h"
#include "exceptions/handlers/ExceptionHandler.h"
#include "linkholder/core.h"

using UrlManager = dochkas::linkholder::UrlAppManager;

class AppManager {
private:
    std::shared_ptr<UrlManager> urlManager;
    std::shared_ptr<StateMachine> sm;
    std::shared_ptr<ExceptionHandler> exHandler;

public:
    AppManager(std::shared_ptr<StateMachine>, std::shared_ptr<ExceptionHandler>);
    ~AppManager();
    virtual void launch() = 0;
    virtual void step() = 0;
    virtual void stop() = 0;

    std::shared_ptr<StateMachine> getStateMachine();
    std::shared_ptr<ExceptionHandler> getExceptionHandler();
    std::shared_ptr<UrlManager> getUrlManager();
};

#endif