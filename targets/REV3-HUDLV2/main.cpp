/**
 * This is a basic sample of using the UART module. The program provides a
 * basic echo functionality where the uart will write back whatever the user
 * enters.
 */


#include <core/io/UART.hpp>
#include <core/io/pin.hpp>
#include <core/manager.hpp>

#include <core/utils/log.hpp>

#include <dev/IS42S16400J.hpp>
#include "NHDDriver.hpp"

namespace log = core::log;
namespace io = core::io;

int main() {
    // Initialize system
    core::platform::init();

    UART& uart = io::getUART<Pin::UART_TX, Pin::UART_RX>(9600, false);

    log::LOGGER.setUART(&uart);

    IS24S16400J::IS42S16400J device{};
    // SDRAM& ram = io::getSDRAM<IS24S16400J::IS42S16400J::getPinGroup()>(IS24S16400J::IS42S16400J::getSdramInitConfig(),
        // IS24S16400J::IS42S16400J::getSdramTimingConfig(), device);
    SDRAM& ram = io::getSDRAM<IS24S16400J::IS42S16400J::getPinGroup()>(IS24S16400J::IS42S16400J::getSdramInitConfig(), IS24S16400J::IS42S16400J::getSdramTimingConfig(), device);

    // TODO: Arena.c, frame.c, and heap.c
    GPIOf4xx backlightPin = GPIOf4xx(Pin::PA_8, GPIO::Direction::OUTPUT, GPIO::Pull::NO_PULL);
    GPIOf4xx ltdcEnable = GPIOf4xx(Pin::PB_13, GPIO::Direction::OUTPUT, GPIO::Pull::NO_PULL);

    log::LOGGER.log(log::Logger::LogLevel::INFO, "Starting");
    NHDDriver driver = NHDDriver(ram, backlightPin, ltdcEnable);
    log::LOGGER.log(log::Logger::LogLevel::INFO, "Inited driver");

    driver.enableBacklight();
    log::LOGGER.log(log::Logger::LogLevel::INFO, "Enabled backlioght");

    constexpr ScreenLibrary::BGR_24 red = { .blue = 0, .green = 0, .red = 255 };
    driver.fillRect(red, 50, 50, 100, 100);
    driver.fillRect(red, 200, 50, 100, 100);
    driver.fillRect(red, 100, 50, 100, 100);

    log::LOGGER.log(log::Logger::LogLevel::INFO, "Drew Red");

    while (true) {
    }
    // Initialize system
    // core::platform::init();
    //
    // UART& uart = io::getUART<Pin::UART_TX, Pin::UART_RX>(9600, false);
    //
    // log::LOGGER.setUART(&uart);
    //
    // IS24S16400J::IS42S16400J device{};
    // const SDRAM& ram = io::getSDRAM<IS24S16400J::IS42S16400J::getPinGroup()>(IS24S16400J::IS42S16400J::getSdramInitConfig(),
    //     IS24S16400J::IS42S16400J::getSdramTimingConfig(), device);
    // // ^^^ Not a real error ^^^
    //
    // volatile auto ram_Ptr = reinterpret_cast<uint16_t*>(ram.getSdramMemoryAddress());
    // uint32_t num = 0;
    //
    // NHD_ASXN::ScreenSignalPolarity polarity = {.horizontalSyncEnable = NHD_ASXN::Polarity::ACTIVE_LOW,
    //                                            .verticalSyncEnable = NHD_ASXN::Polarity::ACTIVE_LOW,
    //                                            .dataEnable = NHD_ASXN::Polarity::ACTIVE_LOW,
    //                                            .pixelClock = NHD_ASXN::Polarity::ACTIVE_LOW};
    // NHD_ASXN::ScreenTiming horizontal = {.active_length = 800, .front_porch = 40, .sync = 48, .back_porch = 40};
    // NHD_ASXN::ScreenTiming vertical = {.active_length = 480, .front_porch = 13, .sync = 1, .back_porch = 31};
    // volatile auto ltdc = NHD_ASXN::NHD_ASXN(polarity, horizontal, vertical);
    //
    // GPIOf4xx LTDC_En = GPIOf4xx(Pin::PB_13, GPIO::Direction::OUTPUT, GPIO::Pull::NO_PULL);
    // LTDC_En.writePin(GPIO::State::HIGH);
    //
    // for (uint32_t i = 0; i < 480 * 800 * 3; i++) {
    //     // ram_Ptr[i] = 0xFF;
    //     // log::LOGGER.log(log::Logger::LogLevel::DEBUG, "ram_ptr: %p, value %d", ram_Ptr + i, ram_Ptr[i]);
    // }
    //
    // GPIOf4xx LTDC_BL = GPIOf4xx(Pin::PA_8, GPIO::Direction::OUTPUT, GPIO::Pull::NO_PULL);
    // LTDC_BL.writePin(GPIO::State::HIGH);
}
