//
// Created by Taylor Lineman on 9/26/26.
//

#ifndef HUDLV2_NHDDRIVER_HPP
#define HUDLV2_NHDDRIVER_HPP
#include <core/io/SDRAM.hpp>

#include <DisplayDriver.hpp>
#include <dev/NHD-7.0-800480EF-ASXN.hpp>

class NHDDriver: ScreenLibrary::Driver::BufferedDisplayDriver {
public:
    NHDDriver(SDRAM& ram);

    uint16_t getWidth();
    uint16_t getHeight();

    void setPixel(ScreenLibrary::RGBA color, uint16_t x, uint16_t y);
    void fillRect(ScreenLibrary::RGBA color, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

    void clear(uint16_t x, uint16_t y);
    void clearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
private:
    SDRAM& ram;

    uint16_t displayWidth = 800;
    uint16_t displayHeight = 480;

    NHD_ASXN::ScreenSignalPolarity polarity = {
        .horizontalSyncEnable = NHD_ASXN::Polarity::ACTIVE_LOW,
        .verticalSyncEnable = NHD_ASXN::Polarity::ACTIVE_LOW,
        .dataEnable = NHD_ASXN::Polarity::ACTIVE_LOW,
        .pixelClock = NHD_ASXN::Polarity::ACTIVE_LOW
    };

    NHD_ASXN::ScreenTiming horizontal = {
        .active_length = 800,
        .front_porch = 40,
        .sync = 48,
        .back_porch = 40
    };

    NHD_ASXN::ScreenTiming vertical = {
        .active_length = 480,
        .front_porch = 13,
        .sync = 1,
        .back_porch = 31
    };

    NHD_ASXN::NHD_ASXN ltdc;
};

#endif // HUDLV2_NHDDRIVER_HPP
