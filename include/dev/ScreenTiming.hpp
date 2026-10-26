#ifndef HUDLV2_SCREENTIMING_HPP
#define HUDLV2_SCREENTIMING_HPP
#include <cstdint>

namespace NHD_ASXN {
typedef struct {
    uint16_t active_length;
    uint8_t front_porch;
    uint8_t sync;
    uint8_t back_porch;
} ScreenTiming;
}

#endif // HUDLV2_SCREENTIMING_HPP
