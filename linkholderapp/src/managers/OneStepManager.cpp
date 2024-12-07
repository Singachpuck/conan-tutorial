#include "managers/OneStepManager.h"

#include <iostream>
#include <utility>
#include "context.h"
#include "exceptions/ExitException.h"
#include "exceptions/UserInputError.h"
#include "util/utils.h"

OneStepManager::OneStepManager(std::shared_ptr<StateMachine> sm, std::shared_ptr<ExceptionHandler> ex)
    : AppManager(std::move(sm), std::move(ex)) {
}

void OneStepManager::launch() {
    // TODO: Figure out how to manage context

    this->getStateMachine()->init();
    this->getStateMachine()->change(MAIN);
    
    try {
        while (true) {
            try {
                this->step();
            } catch (BaseHandleException& e) {
                this->getExceptionHandler()->handle(e);
            }
        }
    } catch (ExitException& e) {}

    this->stop();
}

/**
 * Works like:
 * Step --> Read Input --> Process Input --> Go to the next State
 */
void OneStepManager::step() {
    this->getStateMachine()->next();

    // Create a service for this
    std::string s;
    std::cin >> s;

    std::unique_ptr<Parameters> nextState = this->getStateMachine()->getNextCandidate({
        {USER_INPUT_PARAM_KEY, s}
    });

    if (nextState->count(USER_INPUT_ERROR_PARAM_KEY) > 0) {
        auto err = std::any_cast<UserInputError>(nextState->at(USER_INPUT_ERROR_PARAM_KEY));
        throw std::move(err);
    }

    if (nextState->count(CHANGE_STATE_PARAM_KEY)) {
        this->getStateMachine()->change(std::any_cast<StateName>(nextState->at(CHANGE_STATE_PARAM_KEY)));
    }
}

void OneStepManager::stop() {
    std::cout << "Stopping the app..." << std::endl;
}
