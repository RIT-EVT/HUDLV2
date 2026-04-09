#pragma once

#include <HALf4/stm32f4xx_hal.h>
#include <core/io/pin.hpp>
#include <core/io/platform/f4xx/GPIOf4xx.hpp>

using namespace core::io;

/**
 * External SDRAM
 */
namespace IS24S16400J {
    // Mode Register Definition
    // // These can only be guaranteed to work with ISSI IS42S16400-series SDRAM
    // // Burst Length
    // // // Bit Definitions
    constexpr static uint32_t LOAD_MODE_BURST_LENGTH_MASK = 0x007;
    constexpr static uint32_t LOAD_MODE_BURST_LENGTH_POSITION = 0;
    // // // Valid Burst Length Commands
    constexpr static uint32_t LOAD_MODE_BURST_LENGTH_1 = 0b000 << LOAD_MODE_BURST_LENGTH_POSITION;
    constexpr static uint32_t LOAD_MODE_BURST_LENGTH_2 = 0b001 << LOAD_MODE_BURST_LENGTH_POSITION;
    constexpr static uint32_t LOAD_MODE_BURST_LENGTH_4 = 0b010 << LOAD_MODE_BURST_LENGTH_POSITION;
    constexpr static uint32_t LOAD_MODE_BURST_LENGTH_8 = 0b011 << LOAD_MODE_BURST_LENGTH_POSITION;
    constexpr static uint32_t LOAD_MODE_BURST_LENGTH_PAGE = 0b111 << LOAD_MODE_BURST_LENGTH_POSITION; // Only Works with

    // // Burst Type
    // // // Bit Definitions
    constexpr static uint32_t LOAD_MODE_BURST_TYPE_MASK = 0x008;
    constexpr static uint32_t LOAD_MODE_BURST_TYPE_POSITION = 3;
    // // // Valid Burst Type Commands
    constexpr static uint32_t LOAD_MODE_BURST_TYPE_SEQUENTIAL = 0x000;
    constexpr static uint32_t LOAD_MODE_BURST_TYPE_INTERLEAVE = LOAD_MODE_BURST_TYPE_MASK;

    // // Latency Mode (CAS LATENCY)
    // // // Bit Definitions
    constexpr static uint32_t LOAD_MODE_LATENCY_MODE_MASK = 0x070;
    constexpr static uint32_t LOAD_MODE_LATENCY_MODE_POSITION = 4;
    // // // Valid Latency Mode Commands
    constexpr static uint32_t LOAD_MODE_LATENCY_MODE_2 = 0b010 << LOAD_MODE_LATENCY_MODE_POSITION;
    constexpr static uint32_t LOAD_MODE_LATENCY_MODE_3 = 0b011 << LOAD_MODE_LATENCY_MODE_POSITION;

    // //  Operating Mode
    // // // Bit Definitions
    constexpr static uint32_t LOAD_MODE_OPERATING_MODE_MASK = 0x180;
    constexpr static uint32_t LOAD_MODE_OPERATING_MODE_POSITION = 7;
    // // // Valid Operating Mode Commands
    constexpr static uint32_t LOAD_MODE_OPERATING_MODE_STANDARD = 0b00 << LOAD_MODE_OPERATING_MODE_POSITION;

    // // Write Burst Mode
    // // // Bit Definitions
    constexpr static uint32_t LOAD_MODE_WRITE_BURST_MODE_MASK = 0x200;
    constexpr static uint32_t LOAD_MODE_WRITE_BURST_MODE_POSITION = 9;
    // // // Valid Write Burst Mode Commands
    constexpr static uint32_t LOAD_MODE_WRITE_BURST_MODE_PROGRAMMED = 0;
    constexpr static uint32_t LOAD_MODE_WRITE_BURST_MODE_SINGLE = LOAD_MODE_WRITE_BURST_MODE_MASK;

    // Refresh Count
    constexpr static uint32_t ROW_COUNT = 4096;	    // Rows
    constexpr static uint32_t REFRESH_TIME = 64;	    // ms
    constexpr static uint32_t REFRESH_TIME_PER_ROW = REFRESH_TIME * 1000 / ROW_COUNT; // us

    constexpr static uint32_t RAM_SIZE_BITS = 0x4000000; // 64 Mb
    constexpr static uint32_t RAM_SIZE_BYTES = RAM_SIZE_BITS / 8; // 8 MB

    class IS42S16400J {
        public:
            IS42S16400J();

            static uint32_t SDRAM_CLK_PERIOD_PS;
            static uint32_t SDRAM_CLK_PER_REFRESH;

            static uint32_t ns_to_SDRAM_cycles(uint32_t ns) {
                return (ns * 1000) / (SDRAM_CLK_PERIOD_PS + 1);
            }


        private:

            void Setup_Communication() {
                FMC_SDRAM_CommandTypeDef Command;
                __IO uint32_t tmpmrd =0;

                /* Step 1: Configure a clock configuration enable command */
                Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
                Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
                Command.AutoRefreshNumber      = 1;
                Command.ModeRegisterDefinition = 0;

                /* Send the command */
                HAL_SDRAM_SendCommand(&sdram, &Command, 0xFFFF);

                HAL_Delay(1);

                Command.CommandMode = FMC_SDRAM_CMD_PALL;
                Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
                Command.AutoRefreshNumber = 1;
                Command.ModeRegisterDefinition = 0;

                HAL_SDRAM_SendCommand(&sdram, &Command, 0xFFFF);

                Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
                Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
                Command.AutoRefreshNumber = 2;
                Command.ModeRegisterDefinition = 0;

                HAL_SDRAM_SendCommand(&sdram, &Command, 0xFFFF);

                HAL_Delay(1);

                /* Step 7: Program the external memory mode register */
                tmpmrd = (uint32_t) LOAD_MODE_BURST_LENGTH_1 |
                                    LOAD_MODE_BURST_TYPE_SEQUENTIAL |
                                    LOAD_MODE_LATENCY_MODE_2 |
                                    LOAD_MODE_OPERATING_MODE_STANDARD |
                                    LOAD_MODE_WRITE_BURST_MODE_PROGRAMMED;

                Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
                Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
                Command.AutoRefreshNumber = 1;
                Command.ModeRegisterDefinition = tmpmrd;

                /* Send the command */
                HAL_SDRAM_SendCommand(&sdram, &Command, 0xFFFF);

                HAL_SDRAM_ProgramRefreshRate(&sdram, SDRAM_CLK_PER_REFRESH);
            }


    };
}