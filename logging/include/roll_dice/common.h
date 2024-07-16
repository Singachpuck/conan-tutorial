#ifndef ROLL_DICE_COMMON
#define ROLL_DICE_COMMON

#include <cstdint>
#include <cstdlib>
#include <ctime>

#include "telemetry/logger_common.h"

const char* ROLL_DICE_HOST = "localhost";
const std::uint16_t ROLL_DICE_PORT = 8080;

inline void roll_dice_init() {
    auto logger = getLogger();
    logger->trace("Setting random seed for a dice...");
	srand((int)time(0));
}

inline std::uint16_t roll_dice() {
    auto logger = getLogger();
    logger->trace("Rolling the dice...");
    int low = 1;
    int high = 7;
    int random = rand() % (high - low) + low;
    logger->trace("Generated value: {}", random);
    return static_cast<std::uint16_t>(random);
}

#endif