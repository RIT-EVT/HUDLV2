#include <dev/IS42S16400J.hpp>
#include <core/utils/time.hpp>

namespace IS24S16400J {

    SDRAM::Status IS42S16400J::sendStartUpCommands(SDRAM& controller) {
        auto status = static_cast<uint8_t>(
            controller.SendCommand(SDRAM::SDRAMCommand::CLK_ENABLE, SDRAM::SDRAMCommandTarget::BANK1, 1, 0));
        core::time::wait(1);
        status += static_cast<uint8_t>(controller.SendCommand(SDRAM::SDRAMCommand::PRECHARGE_ALL, SDRAM::SDRAMCommandTarget::BANK1, 1, 0));
        status += static_cast<uint8_t>(
            controller.SendCommand(SDRAM::SDRAMCommand::AUTO_REFRESH, SDRAM::SDRAMCommandTarget::BANK1, 8, 0));
        core::time::wait(1);
        status += static_cast<uint8_t>(controller.SendCommand(SDRAM::SDRAMCommand::SET_OPERATION, SDRAM::SDRAMCommandTarget::BANK1, 1,
            LOAD_MODE_BURST_LENGTH_1 | LOAD_MODE_BURST_TYPE_SEQUENTIAL | LOAD_MODE_LATENCY_MODE_2
            | LOAD_MODE_OPERATING_MODE_STANDARD | LOAD_MODE_WRITE_BURST_MODE_PROGRAMMED));

        status += static_cast<uint8_t>(controller.ProgramRefreshRate(ROW_COUNT, REFRESH_TIME));
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