#include "states/State.h"

State::State(StateName name) : name(name) {}

StateName State::getName() {
    return this->name;
}

void State::setName(const StateName& name) {
    this->name = name;
}