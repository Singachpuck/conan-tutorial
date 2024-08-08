#include "states/IdleState.h"

IdleState::IdleState() : State(IDLE) {}

void IdleState::init()
{
    // Nothing to do
}

void IdleState::onEnter() {
    // Nothing to do
}

std::unique_ptr<Parameters> IdleState::getNextCandidate(Parameters &params)
{
    throw std::exception();
    // return std::unique_ptr<Parameters>();
}

void IdleState::next() {
    // Nothing to do
}

void IdleState::onExit() {
    // Nothing to do
}

void IdleState::destroy() {
    // Nothing to do
}