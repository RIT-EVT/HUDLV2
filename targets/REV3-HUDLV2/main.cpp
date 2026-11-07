/**
 * This is a basic sample of using the UART module. The program provides a
 * basic echo functionality where the uart will write back whatever the user
 * enters.
 */


#include <core/io/UART.hpp>
#include <core/io/pin.hpp>
#include <core/manager.hpp>

#include <core/utils/log.hpp>

#include "NHDDriver.hpp"
#include "screen/shapes/Rectangle.hpp"

#include <screen/Color.hpp>
#include <screen/DisplayDriver.hpp>
#include <screen/test/TestPatterns.hpp>

#include <dev/IS42S16400J.hpp>

namespace log = core::log;
namespace io = core::io;
namespace screen = ScreenLibrary;

int main() {
    // Initialize system
    core::platform::init();

    UART& uart = io::getUART<Pin::UART_TX, Pin::UART_RX>(9600, false);

    log::LOGGER.setUART(&uart);

    IS24S16400J::IS42S16400J device{};
    SDRAM& ram = io::getSDRAM<IS24S16400J::IS42S16400J::getPinGroup()>(IS24S16400J::IS42S16400J::getSdramInitConfig(), IS24S16400J::IS42S16400J::getSdramTimingConfig(), device);

    // TODO: Arena.c, frame.c, and heap.c
    GPIOf4xx backlightPin = GPIOf4xx(Pin::PA_8, GPIO::Direction::OUTPUT, GPIO::Pull::NO_PULL);
    GPIOf4xx ltdcEnable = GPIOf4xx(Pin::PB_13, GPIO::Direction::OUTPUT, GPIO::Pull::NO_PULL);

    NHDDriver driver = NHDDriver(ram, backlightPin, ltdcEnable);

    driver.enableBacklight();
    driver.clear();

    // Setup test patterns to be drawn onto the screen.
    constexpr screen::BGR_24 black  = { .blue = 0,    .green = 0,   .red = 0   };
    constexpr screen::BGR_24 white   = { .blue = 255, .green = 255, .red = 255 };
    constexpr screen::BGR_24 yellow  = { .blue = 0,   .green = 255, .red = 255 };
    constexpr screen::BGR_24 cyan    = { .blue = 255, .green = 255, .red = 0   };
    constexpr screen::BGR_24 green   = { .blue = 0,   .green = 255, .red = 0   };
    constexpr screen::BGR_24 magenta = { .blue = 255, .green = 0,   .red = 255 };
    constexpr screen::BGR_24 red     = { .blue = 0,   .green = 0,   .red = 255 };
    constexpr screen::BGR_24 blue    = { .blue = 255, .green = 0,   .red = 0   };

    // screen::Rectangle<screen::BGR_24> testRectangle = screen::Rectangle<screen::BGR_24>(0, 0, 100, 100, black, white);

    // testRectangle.draw(driver);

    driver.clear();

    while (true) {

    }
}

/**
 * - Screen space coordinates (-1 to 1), (-1 to 1) with relative scaling
 * - Scenes that can contain scenes which contain primitives
 * - Scenes can be set to a z level that is supported by the device
 *      - Compile time definition
 * -
 */