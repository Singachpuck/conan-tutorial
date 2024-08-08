#include "OneStepManager.h"

#include <iostream>
#include "exceptions/ExitException.h"
#include "util/utils.h"

OneStepManager::OneStepManager(StateMachine *sm) : AppManager(sm) {
}

void OneStepManager::launch() {
    this->getStateMachine()->init();
    this->getStateMachine()->change(MAIN);
    
    try {
        while (true) {
            this->step();
        }
    } catch (ExitException& e) {}

    this->stop();
}

void OneStepManager::step() {
    this->getStateMachine()->next();

    std::string s;
    std::cin >> s;

    Parameters nextState = this->getStateMachine()->getNextCandidate({
        {USER_INPUT_PARAM_KEY, s}
    });

    

    this->getStateMachine()->change();
}

void OneStepManager::stop() {
    std::cout << "Stopping the app..." << std::endl;
}
