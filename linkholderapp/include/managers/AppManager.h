#ifndef LINKHOLDER_CONSOLE_APP_MANAGER_H
#define LINKHOLDER_CONSOLE_APP_MANAGER_H

#include "StateMachine.h"

class AppManager {
private:
    StateMachine* sm;
public:
    AppManager(StateMachine* sm);
    virtual void launch() = 0;
    virtual void step() = 0;
    virtual void stop() = 0;

    StateMachine* getStateMachine();
};

#endif