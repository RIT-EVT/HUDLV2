#pragma once

#include <HALf4/stm32f4xx_hal.h>
#include <core/io/SDRAM.hpp>
#include <core/io/platform/f4xx/GPIOf4xx.hpp>
#include <cstdint>

using namespace core::io;

/**
 * External SDRAM
 */
namespace IS24S16400J {
    class IS42S16400J: public SDRAMDevice {
        public:

        explicit IS42S16400J() = default;

        static constexpr const SDRAM::SDRAMInitConfig& getSdramInitConfig() {
            return config;
        }

        static const SDRAM::SDRAMTimingConfig& getSdramTimingConfig();

        static constexpr SDRAM::SDRAMPinGroup& getPinGroup() {
            return const_cast<SDRAM::SDRAMPinGroup&>(group);
        }

        SDRAM::Status sendStartUpCommands(SDRAM& controller) override;

    private:
        static constexpr SDRAM::SDRAMInitConfig config {
            .sdBank=FMC_SDRAM_BANK1, .columnBitsNumber=FMC_SDRAM_COLUMN_BITS_NUM_8,
            .rowBitsNumber=FMC_SDRAM_ROW_BITS_NUM_12, .memoryDataWidth=FMC_SDRAM_MEM_BUS_WIDTH_16,
            .internalBankNumber=FMC_SDRAM_INTERN_BANKS_NUM_4, .casLatency=FMC_SDRAM_CAS_LATENCY_2,
            .writeProtection=FMC_SDRAM_WRITE_PROTECTION_DISABLE, .sdClockPeriod=FMC_SDRAM_CLOCK_PERIOD_2,
            .readBurst=FMC_SDRAM_RBURST_DISABLE, .readPipeDelay=FMC_SDRAM_RPIPE_DELAY_0
        };

        static constexpr Pin ram_pins[] = {Pin::PF_0, Pin::PF_1, Pin::PF_2, Pin::PF_3, Pin::PF_4, Pin::PF_5, Pin::PF_11, Pin::PF_12,
                      Pin::PF_13, Pin::PF_14, Pin::PF_15, Pin::PC_2, Pin::PC_3, Pin::PH_5, Pin::PG_0, Pin::PG_1,
                      Pin::PG_4,Pin::PG_5,Pin::PG_8, Pin::PG_15, Pin::PE_0, Pin::PE_1, Pin::PE_7, Pin::PE_8,
                      Pin::PE_9, Pin::PE_10, Pin::PE_11, Pin::PE_12, Pin::PE_13, Pin::PE_14, Pin::PE_15,
                      Pin::PD_0, Pin::PD_1, Pin::PD_8, Pin::PD_9, Pin::PD_10, Pin::PD_14, Pin::PD_15};
        static constexpr uint8_t number_of_ram_pins = sizeof(ram_pins) / sizeof(ram_pins[0]);
        static constexpr SDRAM::SDRAMPinGroup group = {const_cast<Pin*>(ram_pins), number_of_ram_pins};

        // Mode Register Definition
        // // These can only be guaranteed to work with ISSI IS42S16400-series SDRAM, but other ISSI IS42 family ram
        // // should be quite similar

        // // Burst Length
        // // // Bit Definitions
        static constexpr uint32_t LOAD_MODE_BURST_LENGTH_MASK = 0x007;
        static constexpr uint32_t LOAD_MODE_BURST_LENGTH_POSITION = 0;
        // // // Valid Burst Length Commands
        static constexpr uint32_t LOAD_MODE_BURST_LENGTH_1 = 0b000 << LOAD_MODE_BURST_LENGTH_POSITION;
        static constexpr uint32_t LOAD_MODE_BURST_LENGTH_2 = 0b001 << LOAD_MODE_BURST_LENGTH_POSITION;
        static constexpr uint32_t LOAD_MODE_BURST_LENGTH_4 = 0b010 << LOAD_MODE_BURST_LENGTH_POSITION;
        static constexpr uint32_t LOAD_MODE_BURST_LENGTH_8 = 0b011 << LOAD_MODE_BURST_LENGTH_POSITION;
        static constexpr uint32_t LOAD_MODE_BURST_LENGTH_PAGE = 0b111 << LOAD_MODE_BURST_LENGTH_POSITION;

        // // Burst Type
        // // // Bit Definitions
        static constexpr uint32_t LOAD_MODE_BURST_TYPE_MASK = 0x008;
        static constexpr uint32_t LOAD_MODE_BURST_TYPE_POSITION = 3;
        // // // Valid Burst Type Commands
        static constexpr uint32_t LOAD_MODE_BURST_TYPE_SEQUENTIAL = 0x000;
        static constexpr uint32_t LOAD_MODE_BURST_TYPE_INTERLEAVE = LOAD_MODE_BURST_TYPE_MASK;

        // // Latency Mode (CAS LATENCY)
        // // // Bit Definitions
        static constexpr uint32_t LOAD_MODE_LATENCY_MODE_MASK = 0x070;
        static constexpr uint32_t LOAD_MODE_LATENCY_MODE_POSITION = 4;
        // // // Valid Latency Mode Commands
        static constexpr uint32_t LOAD_MODE_LATENCY_MODE_2 = 0b010 << LOAD_MODE_LATENCY_MODE_POSITION;
        static constexpr uint32_t LOAD_MODE_LATENCY_MODE_3 = 0b011 << LOAD_MODE_LATENCY_MODE_POSITION;

        // //  Operating Mode
        // // // Bit Definitions
        static constexpr uint32_t LOAD_MODE_OPERATING_MODE_MASK = 0x180;
        static constexpr uint32_t LOAD_MODE_OPERATING_MODE_POSITION = 7;
        // // // Valid Operating Mode Commands
        static constexpr uint32_t LOAD_MODE_OPERATING_MODE_STANDARD = 0b00 << LOAD_MODE_OPERATING_MODE_POSITION;

        // // Write Burst Mode
        // // // Bit Definitions
        static constexpr uint32_t LOAD_MODE_WRITE_BURST_MODE_MASK = 0x200;
        static constexpr uint32_t LOAD_MODE_WRITE_BURST_MODE_POSITION = 9;
        // // // Valid Write Burst Mode Commands
        static constexpr uint32_t LOAD_MODE_WRITE_BURST_MODE_PROGRAMMED = 0;
        static constexpr uint32_t LOAD_MODE_WRITE_BURST_MODE_SINGLE = LOAD_MODE_WRITE_BURST_MODE_MASK;

        // Refresh Count
        static constexpr uint32_t ROW_COUNT = 4096;	    // Rows
        static constexpr uint32_t REFRESH_TIME = 64;	    // ms

        static constexpr uint32_t RAM_SIZE_BITS = 0x4000000; // 64 Mb
        static constexpr uint32_t RAM_SIZE_BYTES = RAM_SIZE_BITS / 8; // 8 MB
    };
}