#ifndef LINKHOLDERAPP_MULTISTEPSTATE_H
#define LINKHOLDERAPP_MULTISTEPSTATE_H

#include "State.h"

class Step {
private:
    std::string label;
    std::function<std::unique_ptr<Parameters>(Parameters&& params)> handler;
public:
    Step(const std::string& label, const std::function<std::unique_ptr<Parameters>(Parameters&& params)>& handler);

    const std::string& getLabel() const;
    const std::function<std::unique_ptr<Parameters>(Parameters&& params)>& getHandler() const;
};

class MultiStepState : public State {
protected:
    std::uint32_t stepIndex{};
    std::vector<Step> steps;
public:
    explicit MultiStepState(const StateName& name);
    void onEnter(const Parameters&) override;
    void next() override;
    std::unique_ptr<Parameters> getNextCandidate(Parameters&& params) override;
};


#endif //LINKHOLDERAPP_MULTISTEPSTATE_H
