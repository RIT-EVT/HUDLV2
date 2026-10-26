#pragma once

#include "Layer.hpp"
#include "Polarity.hpp"
#include "ScreenTiming.hpp"
#include "core/io/pin.hpp"

using namespace core::io;

/**
 * LCD Screen
 */
namespace NHD_ASXN {

    class NHD_ASXN {
        public:
        NHD_ASXN(const ScreenSignalPolarity& pol, const ScreenTiming& horizontal, const ScreenTiming& vertical);

        void attachLayer(Layer layer);

        private:
        static constexpr Pin ltdc_pin_af14[] = {Pin::PE_4, Pin::PE_5, Pin::PE_6, Pin::PI_4, Pin::PI_9, Pin::PI_10,
                                                Pin::PF_10, Pin::PC_0, Pin::PC_10, Pin::PA_2, Pin::PA_3, Pin::PA_5,
                                                Pin::PA_6, Pin::PH_2, Pin::PH_4, Pin::PB_8, Pin::PB_9, Pin::PB_11,
                                                Pin::PG_6, Pin::PG_7, Pin::PG_11, Pin::PG_12, Pin::PD_3, Pin::PD_6};
        static constexpr uint8_t ltdc_pin_af14_size = sizeof(ltdc_pin_af14) / sizeof(ltdc_pin_af14[0]);
        static constexpr Pin ltdc_pin_af9[] = {Pin::PG_10, Pin::PI_11, Pin::PB_0, Pin::PB_1};
        static constexpr uint8_t ltdc_pin_af9_size = sizeof(ltdc_pin_af9) / sizeof(ltdc_pin_af9[0]);

        LTDC_HandleTypeDef hltdc;
        ScreenTiming horizontal;
        ScreenTiming vertical;
        ScreenSignalPolarity pol;

        static void setHardware();
        void setPolarity();
        void setTimings();
    };

}