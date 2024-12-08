#ifndef LINKHOLDER_CONSOLE_EXIT_STATE_H
#define LINKHOLDER_CONSOLE_EXIT_STATE_H

#include "IdleState.h"
#include "util/commands.h"
#include "exceptions/ExitException.h"

class ExitState : public State {
private:
    ExitException ex;

public:
    ExitState();
    
    void init() override;
    void onEnter(const Parameters& params) override;
    std::unique_ptr<Parameters> getNextCandidate(Parameters&& params) override;
    void next() override;
    std::unique_ptr<Parameters> onExit() override;
    void destroy() override;
};

#endif