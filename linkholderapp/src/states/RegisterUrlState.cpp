#include "states/RegisterUrlState.h"

RegisterUrlState::RegisterUrlState() : State(REGISTER_URL) {}

void RegisterUrlState::init()
{
    // Nothing to do
}

void RegisterUrlState::onEnter(const Parameters& params) {
    this->urlItem = std::any_cast<std::shared_ptr<dochkas::linkholder::UrlItem>>(params.at(ENTITY_URL_ITEM));
}

std::unique_ptr<Parameters> RegisterUrlState::getNextCandidate(Parameters &&params)
{
    auto response = std::make_unique<Parameters>();
    response->emplace(CHANGE_STATE_PARAM_KEY, MAIN);
    return response;
}

void RegisterUrlState::next() {
    auto context = context::get();

    context->getUrlManager()->registerUrl(this->urlItem->getAddr(), this->urlItem->getDescription(), {});
}

std::unique_ptr<Parameters> RegisterUrlState::onExit() {
    // Nothing to do
    std::cout << "Url added successfully!\n" << std::endl;
    return std::make_unique<Parameters>();
}

void RegisterUrlState::destroy() {
    // Nothing to do
}