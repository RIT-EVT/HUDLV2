#pragma once

#include <HALf4/stm32f4xx_hal.h>
#include <core/io/GPIO.hpp>

using namespace core::io;

/**
 * LCD Screen
 */
namespace NHD_ASXN {
    enum class Polarity : uint8_t {
        ACTIVE_LOW = 0,
        ACTIVE_HIGH = 1,

        FALLING_EDGE = ACTIVE_LOW, // On switching to low
        RISING_EDGE = ACTIVE_HIGH, // On switching to high
    };

    typedef struct {
        uint16_t active_length;
        uint8_t front_porch;
        uint8_t sync;
        uint8_t back_porch;
    } ScreenTiming;

    typedef struct {
        Polarity horizontalSyncEnable;
        Polarity verticalSyncEnable;
        Polarity dataEnable;
        Polarity pixelClock;
    } ScreenSignalPolarity;

    class Layer {
        public:
        Layer(uint16_t horizontal, uint16_t vertical, void* starting_address) : layer_config(), horizontal(horizontal),
            vertical(vertical) {
            layer_config.WindowX0 = 0;
            layer_config.WindowY0 = 0;
            layer_config.WindowX1 = horizontal;
            layer_config.WindowY1 = vertical;
            layer_config.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
            layer_config.FBStartAdress = reinterpret_cast<uint32_t>(starting_address);
        }
        private:
        LTDC_LayerCfgTypeDef layer_config;
        uint16_t horizontal;
        uint16_t vertical;
    };

    class NHD_ASXN {
        public:
        NHD_ASXN(const ScreenSignalPolarity& pol, const ScreenTiming& horizontal, const ScreenTiming& vertical);

        void attach_layer(Layer layer);

        private:
        LTDC_HandleTypeDef hltdc;
        ScreenTiming horizontal;
        ScreenTiming vertical;
        ScreenSignalPolarity pol;

        void setPolarity();
        void setTimings();
    };

}