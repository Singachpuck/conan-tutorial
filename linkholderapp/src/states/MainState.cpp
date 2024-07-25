#include "states/MainState.h"

#include <iostream>
#include <string>
#include <cstdint>

#include "states/MainState.h"
#include "exceptions/UserInputError.h"

MainState::MainState() : State(MAIN) {}

void MainState::init() {
    this->commands.push_back({
        MAIN_LIST_URLS, "List Urls", [this] (Parameters& params) -> std::unique_ptr<Parameters> {
            
        }
    });
}

void MainState::onEnter() {
    std::cout << "Link Holder Console App" << std::endl;
}

std::unique_ptr<Parameters> MainState::getNextCandidate(Parameters& params) {
    std::string input = std::any_cast<std::string>(params.at(USER_INPUT_PARAM_KEY));

    auto result = std::make_unique<Parameters>();
    try {
        std::uint32_t command_n = std::stoul(input);

        if (this->commands.size() >= command_n) {
            result->emplace(USER_INPUT_ERROR_PARAM_KEY, std::make_shared<UserInputError>(input, "Command not found"));
            return result;
        }

        return this->commands[command_n].handler(params);
    } catch (const std::exception& e) {
        result->emplace(USER_INPUT_ERROR_PARAM_KEY, std::make_shared<UserInputError>(input, "Invalid command"));
    }
    return result;
}

void MainState::next() {
    this->print_main_menu();
}

void MainState::onExit() {
    // Nothing to do
}

void MainState::destroy() {
    // Nothing to do
}

void MainState::print_main_menu() {
    std::cout << "Select an option:" << std::endl;
    std::cout << "1. List Urls" << std::endl;
    std::cout << "2. Add Url" << std::endl;
    std::cout << "3. Modify/View Url" << std::endl;
    std::cout << "4. Exit" << std::endl;
}
