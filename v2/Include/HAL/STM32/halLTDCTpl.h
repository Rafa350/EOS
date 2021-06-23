#ifndef __STM32_halLTDCTpl__
#define __STM32_halLTDCTpl__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halLTDC.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    // Valors que depenen del format de color
    //
	template <ColorFormat FORMAT>
	struct LTDCPixelFormatFor {
	};
	template<>
	struct LTDCPixelFormatFor<ColorFormat::rgb565> {
		constexpr static const LTDCPixelFormat value = HAL_LTDC_FORMAT_RGB565;
	};
	template<>
	struct LTDCPixelFormatFor<ColorFormat::rgb888> {
		constexpr static const LTDCPixelFormat value = HAL_LTDC_FORMAT_RGB888;
	};
	template<>
	struct LTDCPixelFormatFor<ColorFormat::argb8888> {
		constexpr static const LTDCPixelFormat value = HAL_LTDC_FORMAT_RGB888;
	};

}


#endif
