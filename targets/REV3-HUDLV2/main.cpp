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
#include <dev/NHD-7.0-800480EF-ASXN.hpp>

namespace log = core::log;
namespace io = core::io;

int main() {
    // Initialize system
    core::platform::init();

    UART& uart = io::getUART<Pin::UART_TX, Pin::UART_RX>(9600, false);

    log::LOGGER.setUART(&uart);

    IS24S16400J::IS42S16400J device{};
    SDRAM& ram = io::getSDRAM<IS24S16400J::IS42S16400J::getPinGroup()>(IS24S16400J::IS42S16400J::getSdramInitConfig(),
        IS24S16400J::IS42S16400J::getSdramTimingConfig(), device);
    // ^^^ Not a real error ^^^

    volatile auto ram_Ptr = reinterpret_cast<uint16_t*>(ram.getSdramMemoryAddress());
    uint32_t num = 0;


    GPIOf4xx LTDC_En = GPIOf4xx(Pin::PB_13, GPIO::Direction::OUTPUT, GPIO::Pull::NO_PULL);
    LTDC_En.writePin(GPIO::State::HIGH);

    for (uint32_t i = 0; i < 480 * 600 * 3; i++) {
        ram_Ptr[i] = 0xFF;
        // log::LOGGER.log(log::Logger::LogLevel::DEBUG, "ram_ptr: %p, value %d", ram_Ptr, ram_Ptr[i]);
    }

    GPIOf4xx LTDC_BL = GPIOf4xx(Pin::PA_8, GPIO::Direction::OUTPUT, GPIO::Pull::NO_PULL);
    LTDC_BL.writePin(GPIO::State::HIGH);

    // ScreenLibrary::Square::gross();
}
