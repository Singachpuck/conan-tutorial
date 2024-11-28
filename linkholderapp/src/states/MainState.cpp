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
            auto response = std::make_unique<Parameters>();
            return response;
        }
    });
    
    this->commands.push_back({
        MAIN_ADD_URL, "Add Url", [this] (Parameters& params) -> std::unique_ptr<Parameters> {
            auto response = std::make_unique<Parameters>();
            return response;
        }
    });

    this->commands.push_back({
        MAIN_UPDATE_URL, "Modify/View Url", [this] (Parameters& params) -> std::unique_ptr<Parameters> {
            auto response = std::make_unique<Parameters>();
            return response;
        }
    });

    this->commands.push_back({
        EXIT_COMMAND, "Exit", [this] (Parameters& params) -> std::unique_ptr<Parameters> {
            auto response = std::make_unique<Parameters>();
            response->emplace(CHANGE_STATE_PARAM_KEY, StateName::EXIT);
            return response;
        }
    });
}

void MainState::onEnter() {
    std::cout << "Link Holder Console App\n" << std::endl;
}

std::unique_ptr<Parameters> MainState::getNextCandidate(Parameters&& params) {
    std::string input = std::any_cast<std::string>(params.at(USER_INPUT_PARAM_KEY));

    auto result = std::make_unique<Parameters>();
    try {
        std::uint32_t command_n = std::stoul(input);

        if (this->commands.size() <= command_n) {
            result->emplace(USER_INPUT_ERROR_PARAM_KEY, std::make_shared<UserInputError>(std::move(input), "Command not found"));
            return result;
        }

        return this->commands[command_n].handler(params);
    } catch (const std::exception& e) {
        result->emplace(USER_INPUT_ERROR_PARAM_KEY, std::make_shared<UserInputError>(std::move(input), "Invalid command"));
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
    for (size_t i = 0; i < commands.size(); i++) {
        std::cout << i << ". " << commands[i].description << std::endl;
    }
    std::cout << "Enter command: ";
}
