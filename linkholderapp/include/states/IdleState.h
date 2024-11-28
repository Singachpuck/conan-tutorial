#ifndef LINKHOLDER_CONSOLE_IDLE_STATE_H
#define LINKHOLDER_CONSOLE_IDLE_STATE_H

#include "State.h"

class IdleState : public State {
public:
    IdleState();

    void init() override;
    void onEnter() override;
    std::unique_ptr<Parameters> getNextCandidate(Parameters&& params) override;
    void next() override;
    void onExit() override;
    void destroy() override;
};

#endif