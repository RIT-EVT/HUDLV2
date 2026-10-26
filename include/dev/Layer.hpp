//
// Created by Taylor Lineman on 10/19/26.
//

#ifndef HUDLV2_LAYER_HPP
#define HUDLV2_LAYER_HPP
#include "HALf4/stm32f4xx.h"

#include <cstdint>

namespace NHD_ASXN {
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
}
#endif // HUDLV2_LAYER_HPP
