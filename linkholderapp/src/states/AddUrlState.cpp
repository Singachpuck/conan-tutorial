#include "states/AddUrlState.h"

AddUrlState::AddUrlState() : State(ADD_URL) {}

void AddUrlState::init()
{
    // Nothing to do
}

void AddUrlState::onEnter() {
    // Nothing to do
}

std::unique_ptr<Parameters> AddUrlState::getNextCandidate(Parameters &&params)
{
    throw std::exception();
    // return std::unique_ptr<Parameters>();
}

void AddUrlState::next() {
    // Nothing to do
}

void AddUrlState::onExit() {
    // Nothing to do
}

void AddUrlState::destroy() {
    // Nothing to do
}