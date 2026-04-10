/**
 * This is a basic sample of using the UART module. The program provides a
 * basic echo functionality where the uart will write back whatever the user
 * enters.
 */

#include <HUDLV2.hpp>
#include <core/io/UART.hpp>
#include <core/io/pin.hpp>
#include <core/manager.hpp>

#include <core/utils/log.hpp>

#include <dev/IS42S16400J.hpp>

namespace log = core::log;
namespace io = core::io;

int main() {
    // Initialize system
    core::platform::init();

    io::UART& uart = io::getUART<io::Pin::UART_TX, io::Pin::UART_RX>(9600, false);

    log::LOGGER.setUART(&uart);

    SDRAM_HandleTypeDef hsdram{};
    FMC_SDRAM_TimingTypeDef timing{};
    auto ram = IS24S16400J::IS42S16400J(hsdram, timing);


}
