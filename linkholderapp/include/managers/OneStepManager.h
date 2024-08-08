#ifndef LINKHOLDER_CONSOLE_ONE_STEP_MANAGER_H
#define LINKHOLDER_CONSOLE_ONE_STEP_MANAGER_H

#include "AppManager.h"

class OneStepManager : public AppManager {
private:

public:
    OneStepManager(StateMachine* sm);

    void launch();
    void step();
    void stop();
};

#endif