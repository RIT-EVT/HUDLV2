#pragma once

#include <HALf4/stm32f4xx_hal_sdram.h>
#include <HALf4/stm32f4xx_ll_fmc.h>

/**
 * External SDRAM
 */
namespace IS24S16400J {

    class IS42S16400J {
        public:
            IS42S16400J() {
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
                sdram.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_2;

                timing.RCDDelay = ns_to_SDRAM_cycles(15);
                timing.RPDelay = ns_to_SDRAM_cycles(15);
                timing.WriteRecoveryTime = 2; // Simply wants two SDRAM Clock cycles
                timing.RowCycleDelay = ns_to_SDRAM_cycles(63);
                timing.SelfRefreshTime = ns_to_SDRAM_cycles(42);
                timing.ExitSelfRefreshDelay = ns_to_SDRAM_cycles(70);
                timing.LoadToActiveDelay = 2; // Simply wants two SDRAM Clock cycles

                HAL_SDRAM_Init(&sdram, &timing);

                Setup_GPIO();
            };

        private:
            constexpr static uint32_t SDRAM_CLK_PERIOD_PS = 1000000000UL / ( (HAL_RCC_GetSysClockFreq() / 2) / 1000);

            bool initialized = false;

            SDRAM_HandleTypeDef sdram;
            FMC_SDRAM_TimingTypeDef timing;

            static uint32_t ns_to_SDRAM_cycles(uint32_t ns) {
                return (ns * 1000) / (SDRAM_CLK_PERIOD_PS + 1);
            }

            void Setup_GPIO() {
                GPIO_InitTypeDef GPIO_InitStruct = {0};
                if (initialized) {
                    return;
                }
                initialized = true;

                __HAL_RCC_FMC_CLK_ENABLE();

                // Use HAL-level GPIO Initializer to get Alternate functions (idk
                // if there is a better way to do this)
                GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
                GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
                GPIO_InitStruct.Pull = GPIO_NOPULL;
                GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
                GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

                HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

                GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
                GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
                GPIO_InitStruct.Pull = GPIO_NOPULL;
                GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
                GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

                HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

                GPIO_InitStruct.Pin = GPIO_PIN_5;
                GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
                GPIO_InitStruct.Pull = GPIO_NOPULL;
                GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
                GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

                HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

                GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_8|GPIO_PIN_15;
                GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
                GPIO_InitStruct.Pull = GPIO_NOPULL;
                GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
                GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

                HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

                GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
                GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
                GPIO_InitStruct.Pull = GPIO_NOPULL;
                GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
                GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

                HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

                GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
                GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
                GPIO_InitStruct.Pull = GPIO_NOPULL;
                GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
                GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

                HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
            }
    };
}