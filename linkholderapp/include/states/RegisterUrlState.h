#ifndef LINKHOLDERAPP_REGISTERURLSTATE_H
#define LINKHOLDERAPP_REGISTERURLSTATE_H

#include "State.h"
#include "ITransitState.h"

class RegisterUrlState : public State, public ITransitState {
private:
    std::shared_ptr<dochkas::linkholder::UrlItem> urlItem;
public:
    RegisterUrlState();

    void init() override;
    void onEnter(const Parameters& params) override;
    std::unique_ptr<Parameters> getNextCandidate(Parameters&& params) override;
    void next() override;
    std::unique_ptr<Parameters> onExit() override;
    void destroy() override;
};


#endif //LINKHOLDERAPP_REGISTERURLSTATE_H
