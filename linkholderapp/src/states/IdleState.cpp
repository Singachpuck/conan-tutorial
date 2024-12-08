#include "states/IdleState.h"

IdleState::IdleState() : State(IDLE) {}

void IdleState::init()
{
    // Nothing to do
}

void IdleState::onEnter(const Parameters&) {
    // Nothing to do
}

std::unique_ptr<Parameters> IdleState::getNextCandidate(Parameters &&params)
{
    throw std::exception();
    // return std::unique_ptr<Parameters>();
}

void IdleState::next() {
    // Nothing to do
}

std::unique_ptr<Parameters> IdleState::onExit() {
    // Nothing to do
    return std::make_unique<Parameters>();
}

void IdleState::destroy() {
    // Nothing to do
}