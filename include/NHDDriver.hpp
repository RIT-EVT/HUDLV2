//
// Created by Taylor Lineman on 9/26/26.
//

#ifndef HUDLV2_NHDDRIVER_HPP
#define HUDLV2_NHDDRIVER_HPP

#include "core/io/GPIO.hpp"
#include "dev/NHD-7.0-800480EF-ASXN.hpp"

#include <DisplayDriver.hpp>
#include <core/io/SDRAM.hpp>

class NHDDriver : ScreenLibrary::Driver::BufferedDisplayDriver<ScreenLibrary::BGR_24>, ScreenLibrary::Driver::BacklightDriver {
public:
    explicit NHDDriver(core::io::SDRAM& ram, core::io::GPIO& backlightPin, core::io::GPIO& ltdcEnable);

    uint16_t getWidth() override;
    uint16_t getHeight() override;

    void setPixel(ScreenLibrary::BGR_24 color, uint16_t x, uint16_t y) override;
    void fillRect(ScreenLibrary::BGR_24 color, uint16_t x, uint16_t y, uint16_t width, uint16_t height) override;

    void clear(uint16_t x, uint16_t y) override;
    void clearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height) override;

    void flush() override;

    void enableBacklight() override;
    void disableBacklight() override;
private:
    core::io::SDRAM& ram;
    ScreenLibrary::RGB_24* ramPtr;
    // uint16_t* ramPtr;

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
    core::io::GPIO& ltdcEnable;

    core::io::GPIO& backlightPin;
};


#endif // HUDLV2_NHDDRIVER_HPP
