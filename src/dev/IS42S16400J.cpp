#include <core/dev/RTCTimer.hpp>
#include <dev/IS42S16400J.hpp>

namespace IS24S16400J {
    // void IS42S16400J::SetGPIOToFMC() {
    //     __HAL_RCC_FMC_CLK_ENABLE();
    //
    //     Pin pins[] = {Pin::PF_0, Pin::PF_1, Pin::PF_2, Pin::PF_3, Pin::PF_4, Pin::PF_5, Pin::PF_11, Pin::PF_12,
    //                   Pin::PF_13, Pin::PF_14, Pin::PF_15, Pin::PC_2, Pin::PC_3, Pin::PH_5, Pin::PG_0, Pin::PG_1,
    //                   Pin::PG_4,Pin::PG_5,Pin::PG_8, Pin::PG_15, Pin::PE_0, Pin::PE_1, Pin::PE_7, Pin::PE_8,
    //                   Pin::PE_9, Pin::PE_10, Pin::PE_11, Pin::PE_12, Pin::PE_13, Pin::PE_14, Pin::PE_15,
    //                   Pin::PD_0, Pin::PD_1, Pin::PD_8, Pin::PD_9, Pin::PD_10, Pin::PD_14, Pin::PD_15};
    //
    //     GPIOf4xx::gpioInit(pins, sizeof(pins) / sizeof(pins[0]), GPIO_MODE_AF_PP, GPIO_NOPULL,
    //                        GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC);
    // }

    SDRAM::Status IS42S16400J::startupCommands(SDRAM& device) {
        auto status = static_cast<uint8_t>(device.SendCommand(SDRAM::SDRAMCommand::CLK_ENABLE, SDRAM::SDRAMCommandTarget::BANK1, 1, 0));
        time::wait(1);
        status += static_cast<uint8_t>(device.SendCommand(SDRAM::SDRAMCommand::PRECHARGE_ALL, SDRAM::SDRAMCommandTarget::BANK1, 1, 0));
        status += static_cast<uint8_t>(device.SendCommand(SDRAM::SDRAMCommand::AUTO_REFRESH, SDRAM::SDRAMCommandTarget::BANK1, 2, 0));
        time::wait(1);
        status += static_cast<uint8_t>(device.SendCommand(SDRAM::SDRAMCommand::SET_OPERATION, SDRAM::SDRAMCommandTarget::BANK1, 1,
            LOAD_MODE_BURST_LENGTH_1 | LOAD_MODE_BURST_TYPE_SEQUENTIAL | LOAD_MODE_LATENCY_MODE_2
            | LOAD_MODE_OPERATING_MODE_STANDARD | LOAD_MODE_WRITE_BURST_MODE_PROGRAMMED));

        status += static_cast<uint8_t>(device.ProgramRefreshRate(ROW_COUNT, REFRESH_TIME));
        if (status != 0) {
            return SDRAM::Status::ERROR;
        }
        return SDRAM::Status::OK;
    }

    const SDRAM::SDRAMTimingConfig& IS42S16400J::getSdramTimingConfig() {
        static SDRAM::SDRAMTimingConfig config{};

        config.loadToActiveDelay    = SDRAM::NSToSdramClockCycles(15);
        config.exitSelfRefreshDelay = SDRAM::NSToSdramClockCycles(15);
        config.selfRefreshTime      = 2; // Simply wants two SDRAM Clock cycles
        config.rowCycleDelay        = SDRAM::NSToSdramClockCycles(63);
        config.writeRecoveryTime    = SDRAM::NSToSdramClockCycles(42);
        config.rpDelay              = SDRAM::NSToSdramClockCycles(70);
        config.rcdDelay             = 2; // Simply wants two SDRAM Clock cycles

        return config;
    };

}