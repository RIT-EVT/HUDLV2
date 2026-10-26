#include <NHDDriver.hpp>

#include <cmath>
#include <core/io/SDRAM.hpp>
#include <dev/NHD-7.0-800480EF-ASXN.hpp>
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

NHDDriver::NHDDriver(SDRAM& ram) : ram(ram), ltdc(polarity, horizontal, vertical) {
    ramPtr = reinterpret_cast<ScreenLibrary::RGB_24*>(ram.getSdramMemoryAddress());
}

uint16_t NHDDriver::getHeight() {
    return displayHeight;
}

uint16_t NHDDriver::getWidth() {
    return displayWidth;
}

void NHDDriver::setPixel(const ScreenLibrary::RGB_24 color, const uint16_t x, const uint16_t y) {
    const int start = y * displayWidth + x;
    ramPtr[start] = color;
}

void NHDDriver::fillRect(const ScreenLibrary::RGB_24 color, const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height) {
    const int maxX = max((x + width), displayWidth);
    const int maxY = max((y + height), displayHeight);

    for (uint32_t i = x; i < maxX; i ++) {
        for (uint32_t j = y; j < maxY; j++) {
            setPixel(color, i, j);
        }
    }
}

void NHDDriver::clear(uint16_t x, uint16_t y) {

}

void NHDDriver::clearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {

}

void NHDDriver::flush() {

}

void NHDDriver::enableBacklight() {
    // GPIOf4xx LTDC_BL = GPIOf4xx(Pin::PA_8, GPIO::Direction::OUTPUT, GPIO::Pull::NO_PULL);
    // LTDC_BL.writePin(GPIO::State::HIGH);
    //
    // ScreenLibrary::Square::gross();

}