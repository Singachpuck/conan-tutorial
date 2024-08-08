#ifndef LINKHOLDER_CONSOLE_STATE_MACHINE_H
#define LINKHOLDER_CONSOLE_STATE_MACHINE_H

#include <map>
#include <cstdint>
#include "states/State.h"

const std::uint8_t STATE_SIZE = 5;

extern State* STATES[];

class StateMachine {
private:
    std::map<StateName, State*> states {};
    State* current = nullptr;

public:
    StateMachine();

    void init();

    void change(StateName newState);

    std::unique_ptr<Parameters> getNextCandidate(Parameters& params);

    void next();

    void destroy();
};

#endif