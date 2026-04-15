#include <dev/NHD-7.0-800480EF-ASXN.hpp>

namespace NHD_ASXN {
    // How this works is mildly gross. Boils down to if the POLARITY enum is enabled, then set the value to be
    // the hal's active high value, otherwise set to hal's active low value (0)
    void NHD_ASXN::setPolarity() {
        this->hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AH   * static_cast<uint32_t>(this->pol.horizontalSyncEnable);
        this->hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AH   * static_cast<uint32_t>(this->pol.verticalSyncEnable);
        this->hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AH   * static_cast<uint32_t>(this->pol.dataEnable);
        this->hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IIPC * static_cast<uint32_t>(this->pol.pixelClock);
    }

    void NHD_ASXN::setTimings() {
        this->hltdc.Init.HorizontalSync = this->horizontal.sync - 1;
        this->hltdc.Init.AccumulatedHBP = this->horizontal.back_porch + this->hltdc.Init.HorizontalSync;
        this->hltdc.Init.AccumulatedActiveW = this->horizontal.active_length + this->hltdc.Init.AccumulatedHBP;
        this->hltdc.Init.TotalWidth = this->horizontal.front_porch + this->hltdc.Init.AccumulatedActiveW;

        this->hltdc.Init.VerticalSync = this->vertical.sync - 1;;
        this->hltdc.Init.AccumulatedVBP = this->vertical.back_porch + this->hltdc.Init.VerticalSync;
        this->hltdc.Init.AccumulatedActiveH = this->vertical.active_length + this->hltdc.Init.AccumulatedVBP;
        this->hltdc.Init.TotalHeigh = this->vertical.front_porch + this->hltdc.Init.AccumulatedActiveH;
    }

    NHD_ASXN::NHD_ASXN(const ScreenSignalPolarity& pol, const ScreenTiming& horizontal, const ScreenTiming& vertical) :
             hltdc(), horizontal(horizontal), vertical(vertical), pol(pol) {
        this->hltdc.Instance = LTDC;

        setPolarity();
        setTimings();

        // EVT Colors
        this->hltdc.Init.Backcolor.Blue = 0x02;
        this->hltdc.Init.Backcolor.Green = 0x69;
        this->hltdc.Init.Backcolor.Red = 0xF7;
        HAL_LTDC_Init(&this->hltdc);
    };

}