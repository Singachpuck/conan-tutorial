#ifndef LINKHOLDERAPP_ADDURLSTATE_H
#define LINKHOLDERAPP_ADDURLSTATE_H

#include "MultiStepState.h"

class AddUrlState : public MultiStepState {
private:
    std::shared_ptr<dochkas::linkholder::UrlItem> urlItem;
public:
    AddUrlState();

    void init() override;
    void onEnter(const Parameters& params) override;
    std::unique_ptr<Parameters> onExit() override;
    void destroy() override;

    std::unique_ptr<Parameters> AddUrlState::registerUrlAddr(Parameters &&params);
    std::unique_ptr<Parameters> AddUrlState::registerUrlDesc(Parameters &&params);
    std::unique_ptr<Parameters> AddUrlState::registerUrlTags(Parameters &&params);
};

#endif //LINKHOLDERAPP_ADDURLSTATE_H
