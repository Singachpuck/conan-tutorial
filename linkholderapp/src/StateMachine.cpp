#include "StateMachine.h"

#include "states/IdleState.h"
#include "states/MainState.h"

IdleState idleState;

MainState mainState;

State* STATES[] = {
    &idleState,
    &mainState
};

StateMachine::StateMachine() {
	// std::cout << "Here" << std::endl;

    for (size_t i = 0; i < 2; i++) {
        this->states.insert({STATES[i]->getName(), STATES[i]});   
    }
}

void StateMachine::init() {
    for (auto it = states.begin(); it != states.end(); ++it) {
        it->second->init();
    }
}

void StateMachine::change(StateName newState) {
    if (this->current != nullptr) {
        this->current->onExit();
    }
    this->current = states.at(newState);
    this->current->onEnter();
}

std::unique_ptr<Parameters> StateMachine::getNextCandidate(Parameters &params) {
    return this->current->getNextCandidate(params);
}

void StateMachine::next() {
    this->current->next();
}

void StateMachine::destroy() {
    for (auto it = states.begin(); it != states.end(); ++it) {
        it->second->destroy();
    }
}