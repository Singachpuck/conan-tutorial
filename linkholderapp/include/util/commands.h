#ifndef LINKHOLDER_CONSOLE_COMMANDS_H
#define LINKHOLDER_CONSOLE_COMMANDS_H

#include <functional>
#include <vector>
#include <string>

#include "util/utils.h"


enum CommandName {
    MAIN_LIST_URLS
};

struct Command {
    CommandName name;
    std::string description;
    std::function<std::unique_ptr<Parameters>(Parameters&)> handler;
};

using Commands = std::vector<Command>;

#endif