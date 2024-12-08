#include "StateMachine.h"

#include "states/IdleState.h"
#include "states/MainState.h"
#include "states/ExitState.h"
#include "states/AddUrlState.h"
#include "states/RegisterUrlState.h"

//IdleState idleState;
//
//MainState mainState;
//
//ExitState exitState;
//
//State* STATES[] = {
//    &idleState,
//    &mainState,
//    &exitState
//};

std::vector<std::shared_ptr<State>> STATES {
    std::make_shared<IdleState>(),
    std::make_shared<MainState>(),
    std::make_shared<AddUrlState>(),
    std::make_shared<RegisterUrlState>(),
    std::make_shared<ExitState>()
};

StateMachine::StateMachine() {
    for (auto & i : STATES) {
        this->states.insert({i->getName(), i});
    }
}

void StateMachine::init() {
    for (auto it = states.begin(); it != states.end(); ++it) {
        it->second->init();
    }
}

void StateMachine::change(StateName newState) {
    if (this->current != nullptr && this->current->getName() == newState) {
        return;
    }

    std::unique_ptr<Parameters> params = this->current != nullptr ? this->current->onExit()
            : std::make_unique<Parameters>();
    this->current = states.at(newState);
    this->current->onEnter(*params);
}

std::unique_ptr<Parameters> StateMachine::getNextCandidate(Parameters&& params) {
    return this->current->getNextCandidate(std::move(params));
}

void StateMachine::next() {
    this->current->next();
}

void StateMachine::destroy() {
    for (auto it = states.begin(); it != states.end(); ++it) {
        it->second->destroy();
    }
}