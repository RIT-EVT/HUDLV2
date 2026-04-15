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
#include <dev/NHD-7.0-800480EF-ASXN.hpp>

namespace log = core::log;
namespace io = core::io;

int main() {
    // Initialize system
    core::platform::init();

    UART& uart = io::getUART<Pin::UART_TX, Pin::UART_RX>(9600, false);

    log::LOGGER.setUART(&uart);

    volatile auto ram = IS24S16400J::IS42S16400J();

    // NHD_ASXN::ScreenSignalPolarity polarity = { .dataEnable = NHD_ASXN::Polarity::ACTIVE_LOW,
    //                                             .pixelClock = NHD_ASXN::Polarity::ACTIVE_LOW,
    //                                             .horizontalSyncEnable = NHD_ASXN::Polarity::ACTIVE_LOW,
    //                                             .verticalSyncEnable = NHD_ASXN::Polarity::ACTIVE_LOW};
    // NHD_ASXN::ScreenTiming horizontal = {.active_length = 800, .front_porch = 40, .sync = 48, .back_porch = 40};
    // NHD_ASXN::ScreenTiming vertical = {.active_length = 480, .front_porch = 13, .sync = 1, .back_porch = 31};
    // volatile auto ltdc = NHD_ASXN::NHD_ASXN(polarity, horizontal, vertical);



}
