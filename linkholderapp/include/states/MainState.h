#ifndef LINKHOLDER_CONSOLE_MAIN_STATE_H
#define LINKHOLDER_CONSOLE_MAIN_STATE_H

#include "IdleState.h"
#include "util/commands.h"

class MainState : public State {
private:
    Commands commands;

public:
    MainState();
    
    void init() override;
    void onEnter(const Parameters& params) override;
    std::unique_ptr<Parameters> getNextCandidate(Parameters&& params) override;
    void next() override;
    std::unique_ptr<Parameters> onExit() override;
    void destroy() override;

private:
    void print_main_menu();
};

#endif