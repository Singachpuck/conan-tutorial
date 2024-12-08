#ifndef LINKHOLDER_CONSOLE_IDLE_STATE_H
#define LINKHOLDER_CONSOLE_IDLE_STATE_H

#include "State.h"

class IdleState : public State {
public:
    IdleState();

    void init() override;
    void onEnter(const Parameters& params) override;
    std::unique_ptr<Parameters> getNextCandidate(Parameters&& params) override;
    void next() override;
    std::unique_ptr<Parameters> onExit() override;
    void destroy() override;
};

#endif