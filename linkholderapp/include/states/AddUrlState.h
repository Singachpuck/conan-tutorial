#ifndef LINKHOLDERAPP_ADDURLSTATE_H
#define LINKHOLDERAPP_ADDURLSTATE_H

#include "State.h"

class AddUrlState : public State {
    AddUrlState();

    void init() override;
    void onEnter() override;
    std::unique_ptr<Parameters> getNextCandidate(Parameters&& params) override;
    void next() override;
    void onExit() override;
    void destroy() override;
};

#endif //LINKHOLDERAPP_ADDURLSTATE_H
