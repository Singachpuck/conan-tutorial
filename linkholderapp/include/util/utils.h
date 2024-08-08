#ifndef LINKHOLDER_CONSOLE_UTILS_H
#define LINKHOLDER_CONSOLE_UTILS_H

#include <unordered_map>
#include <any>

#define USER_INPUT_PARAM_KEY "user.input"
#define USER_INPUT_ERROR_PARAM_KEY "user.input.error"


using Parameters = std::unordered_map<std::string, std::any>;

// class Attributes : public std::unordered_map<std::string, void*> {


// };

#endif