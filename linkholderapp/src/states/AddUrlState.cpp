#include "states/AddUrlState.h"

AddUrlState::AddUrlState() : MultiStepState(ADD_URL), urlItem(std::make_shared<dochkas::linkholder::UrlItem>(0)) {}

void AddUrlState::init()
{
    // Nothing to do
//    auto urlItem = dochkas::linkholder::UrlItem(0);
    auto registerUrlAddrHandler = std::bind(&AddUrlState::registerUrlAddr, this, std::placeholders::_1);
    this->steps.emplace_back("Enter url address", registerUrlAddrHandler);
    auto registerUrlDescHandler = std::bind(&AddUrlState::registerUrlDesc, this, std::placeholders::_1);
    this->steps.emplace_back("Enter url description", registerUrlDescHandler);
    this->steps.emplace_back("Enter space-separated tags", [this] (auto params) {
        auto result = this->registerUrlTags(std::move(params));
        result->emplace(CHANGE_STATE_PARAM_KEY, REGISTER_URL);
        return result;
    });
}

void AddUrlState::onEnter(const Parameters& params) {
    MultiStepState::onEnter(params);
}

std::unique_ptr<Parameters> AddUrlState::registerUrlAddr(Parameters &&params) {
    std::string input = std::any_cast<std::string>(params.at(USER_INPUT_PARAM_KEY));

    this->urlItem->setAddr(input);

    auto result = std::make_unique<Parameters>();
    result->emplace(RESULT_STATUS, OK);
    return result;
}

std::unique_ptr<Parameters> AddUrlState::registerUrlDesc(Parameters &&params) {
    std::string input = std::any_cast<std::string>(params.at(USER_INPUT_PARAM_KEY));

    this->urlItem->setDescription(input);

    auto result = std::make_unique<Parameters>();
    result->emplace(RESULT_STATUS, OK);
    return result;
}

std::unique_ptr<Parameters> AddUrlState::registerUrlTags(Parameters &&params) {
    auto result = std::make_unique<Parameters>();
    result->emplace(RESULT_STATUS, OK);
    return result;
}

//std::unique_ptr<Parameters> AddUrlState::getNextCandidate(Parameters &&params)
//{
//    throw std::exception();
//    // return std::unique_ptr<Parameters>();
//}

//void AddUrlState::next() {
//    // Nothing to do
//}

std::unique_ptr<Parameters> AddUrlState::onExit() {
    auto result = std::make_unique<Parameters>();
    result->emplace(ENTITY_URL_ITEM, this->urlItem);
    return result;
}

void AddUrlState::destroy() {
    // Nothing to do
}