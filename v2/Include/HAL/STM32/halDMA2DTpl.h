#ifndef __STM32_halDMA2DTpl__
#define __STM32_halDMA2DTpl__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halDMA2D.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	// Valors que depenen de format de color
	//
	template <ColorFormat FORMAT>
	struct DMA2DOptionsFor {
	};
	template<>
	struct DMA2DOptionsFor<ColorFormat::argb8888> {
		constexpr static const DMA2DOptions DFMT = HAL_DMA2D_DFMT_ARGB8888;
		constexpr static const DMA2DOptions SFMT = HAL_DMA2D_SFMT_ARGB8888;
	};
	template<>
	struct DMA2DOptionsFor<ColorFormat::rgb888> {
		constexpr static const DMA2DOptions DFMT = HAL_DMA2D_DFMT_RGB888;
		constexpr static const DMA2DOptions SFMT = HAL_DMA2D_SFMT_RGB888;
	};
	template<>
	struct DMA2DOptionsFor<ColorFormat::rgb565> {
		constexpr static const DMA2DOptions DFMT = HAL_DMA2D_DFMT_RGB565;
		constexpr static const DMA2DOptions SFMT = HAL_DMA2D_SFMT_RGB565;
	};
	template<>
	struct DMA2DOptionsFor<ColorFormat::l8> {
		constexpr static const DMA2DOptions SFMT = HAL_DMA2D_SFMT_L8;
	};
}


#endif // __STM32_halDMA2DTpl__
