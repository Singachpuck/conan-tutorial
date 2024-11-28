#include <iostream>

#include "states/ExitState.h"

ExitState::ExitState() : State(StateName::EXIT) {}

void ExitState::init() {}

void ExitState::onEnter() {
    std::cout << "Exiting application..." << std::endl;
}

std::unique_ptr<Parameters> ExitState::getNextCandidate(Parameters &&params) {
    return std::unique_ptr<Parameters>();
}

void ExitState::next() {
    throw this->ex;
}

void ExitState::onExit() {}

void ExitState::destroy() {}
