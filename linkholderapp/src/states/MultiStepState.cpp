#include "states/MultiStepState.h"
#include "exceptions/InvalidStateException.h"

Step::Step(const std::string &label, const std::function<std::unique_ptr<Parameters>(Parameters &&)> &handler) : label(label), handler(handler) {};

const std::string& Step::getLabel() const {
    return this->label;
}

const std::function<std::unique_ptr<Parameters>(Parameters&& params)>& Step::getHandler() const {
    return this->handler;
}

MultiStepState::MultiStepState(const StateName& name) : State(name) {}

void MultiStepState::onEnter(const Parameters&) {
    this->stepIndex = 0;
}

void MultiStepState::next() {
    std::cout << this->steps[this->stepIndex].getLabel() << ": ";
}

std::unique_ptr<Parameters> MultiStepState::getNextCandidate(Parameters&& params) {
    if (this->stepIndex >= this->steps.size()) {
        throw InvalidStateException();
    }

    auto result = this->steps[this->stepIndex].getHandler()(std::move(params));

    auto status = std::any_cast<Status>(result->at(RESULT_STATUS));
    switch (status) {
        case OK:
            this->stepIndex++;
            break;
        case ROLLBACK:
            this->stepIndex--;
            break;
        case CANCEL:
            this->stepIndex = 0;
            break;
    }
    return result;
}