#include <dev/IS42S16400J.hpp>

namespace IS24S16400J {
    uint32_t IS42S16400J::ns_to_SDRAM_cycles(uint32_t ns) {
        return (ns * 1000) / (SDRAM_CLK_PERIOD_PS + 1);
    }

    void IS42S16400J::SetGPIOToFMC() {
        __HAL_RCC_FMC_CLK_ENABLE();

        Pin pins[] = {Pin::PF_0, Pin::PF_1, Pin::PF_2, Pin::PF_3, Pin::PF_4, Pin::PF_5, Pin::PF_11, Pin::PF_12,
                      Pin::PF_13, Pin::PF_14, Pin::PF_15, Pin::PC_2, Pin::PC_3, Pin::PH_5, Pin::PG_0, Pin::PG_1,
                      Pin::PG_4,Pin::PG_5,Pin::PG_8, Pin::PG_15, Pin::PE_0, Pin::PE_1, Pin::PE_7, Pin::PE_8,
                      Pin::PE_9, Pin::PE_10, Pin::PE_11, Pin::PE_12, Pin::PE_13, Pin::PE_14, Pin::PE_15,
                      Pin::PD_0, Pin::PD_1, Pin::PD_8, Pin::PD_9, Pin::PD_10, Pin::PD_14, Pin::PD_15};

        GPIOf4xx::gpioInit(pins, sizeof(pins) / sizeof(pins[0]), GPIO_MODE_AF_PP, GPIO_NOPULL,
                           GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC);
    }

    void IS42S16400J::Setup_Sequence() {
        FMC_SDRAM_CommandTypeDef Command;
        uint32_t tmpmrd = 0;

        Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
        Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
        Command.AutoRefreshNumber      = 1;
        Command.ModeRegisterDefinition = 0;

        HAL_SDRAM_SendCommand(&sdram, &Command, 0xFFFF);

        HAL_Delay(1);

        Command.CommandMode            = FMC_SDRAM_CMD_PALL;
        Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
        Command.AutoRefreshNumber      = 1;
        Command.ModeRegisterDefinition = 0;

        HAL_SDRAM_SendCommand(&sdram, &Command, 0xFFFF);

        Command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
        Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
        Command.AutoRefreshNumber      = 2;
        Command.ModeRegisterDefinition = 0;

        HAL_SDRAM_SendCommand(&sdram, &Command, 0xFFFF);

        HAL_Delay(1);

        tmpmrd = LOAD_MODE_BURST_LENGTH_1 | LOAD_MODE_BURST_TYPE_SEQUENTIAL | LOAD_MODE_LATENCY_MODE_2
            | LOAD_MODE_OPERATING_MODE_STANDARD | LOAD_MODE_WRITE_BURST_MODE_PROGRAMMED;

        Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
        Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
        Command.AutoRefreshNumber      = 1;
        Command.ModeRegisterDefinition = tmpmrd;

        HAL_SDRAM_SendCommand(&sdram, &Command, 0xFFFF);

        HAL_SDRAM_ProgramRefreshRate(&sdram, SDRAM_CLK_PER_REFRESH);
    }

    IS42S16400J::IS42S16400J() : sdram(), timing() {
        IS42S16400J::SDRAM_CLK_PERIOD_PS = (1000000000 / ((HAL_RCC_GetSysClockFreq() / 2) / 1000));
        IS42S16400J::SDRAM_CLK_PER_REFRESH = (REFRESH_TIME_PER_ROW * (HAL_RCC_GetSysClockFreq() / 2) >> 20) - 20; // Take 20 for a little cushioning (recommended by reference manual)

        sdram.Instance = FMC_SDRAM_DEVICE;

        sdram.Init.SDBank = FMC_SDRAM_BANK1;
        sdram.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
        sdram.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
        sdram.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
        sdram.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
        sdram.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2;
        sdram.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
        sdram.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
        sdram.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
        sdram.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;

        this->timing.RCDDelay = ns_to_SDRAM_cycles(15);
        this->timing.RPDelay = ns_to_SDRAM_cycles(15);
        this->timing.WriteRecoveryTime = 2; // Simply wants two SDRAM Clock cycles
        this->timing.RowCycleDelay = ns_to_SDRAM_cycles(63);
        this->timing.SelfRefreshTime = ns_to_SDRAM_cycles(42);
        this->timing.ExitSelfRefreshDelay = ns_to_SDRAM_cycles(70);
        this->timing.LoadToActiveDelay = 2; // Simply wants two SDRAM Clock cycles

        HAL_SDRAM_Init(&sdram, &this->timing);

        SetGPIOToFMC();

        Setup_Sequence();
    }
}