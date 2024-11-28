#ifndef LINKHOLDER_CONSOLE_ONE_STEP_MANAGER_H
#define LINKHOLDER_CONSOLE_ONE_STEP_MANAGER_H

#include "managers/AppManager.h"

class OneStepManager : public AppManager {
private:

public:
    OneStepManager(std::shared_ptr<UrlManager>, std::shared_ptr<StateMachine> sm, std::shared_ptr<ExceptionHandler> ex);

    void launch();
    void step();
    void stop();
};

#endif