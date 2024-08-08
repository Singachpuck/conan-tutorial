#ifndef LINKHOLDER_CONSOLE_STATE_H
#define LINKHOLDER_CONSOLE_STATE_H

#include <memory>

#include "util/utils.h"

enum StateName {
    IDLE, MAIN, MODIFY_URL, ADD_URL, UNKNOWN
};

class State {
private:
    StateName name {IDLE};

public:
    State(StateName name);

    virtual void init() = 0;
    virtual void onEnter() = 0;
    virtual void next() = 0;
    virtual std::unique_ptr<Parameters> getNextCandidate(Parameters& params) = 0;
    virtual void onExit() = 0;
    virtual void destroy() = 0;

    StateName getName();

    void setName(const StateName& name);
};

#endif