//
// Created by Taylor Lineman on 9/26/26.
//

#include <NHDDriver.hpp>
#include <dev/NHD-7.0-800480EF-ASXN.hpp>
#include <core/io/SDRAM.hpp>

NHDDriver::NHDDriver(SDRAM& ram) : ram(ram), ltdc(polarity, horizontal, vertical) {

}

uint16_t NHDDriver::getHeight() {
    return displayHeight;
}

uint16_t NHDDriver::getWidth() {
    return displayWidth;
}

void NHDDriver::setPixel(ScreenLibrary::RGBA color, uint16_t x, uint16_t y) {

}

void NHDDriver::fillRect(ScreenLibrary::RGBA color, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {

}