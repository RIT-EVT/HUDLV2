//
// Created by Taylor Lineman on 10/19/26.
//

#ifndef HUDLV2_POLARITY_HPP
#define HUDLV2_POLARITY_HPP
#include <cstdint>

namespace NHD_ASXN {
enum class Polarity : uint8_t {
    ACTIVE_LOW = 0,
    ACTIVE_HIGH = 1,

    FALLING_EDGE = ACTIVE_LOW, // On switching to low
    RISING_EDGE = ACTIVE_HIGH, // On switching to high
};

typedef struct {
    Polarity horizontalSyncEnable;
    Polarity verticalSyncEnable;
    Polarity dataEnable;
    Polarity pixelClock;
} ScreenSignalPolarity;
}

#endif // HUDLV2_POLARITY_HPP
