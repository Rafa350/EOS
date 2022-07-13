#ifndef __STM32_htlDMA2D__
#define __STM32_htlDMA2D__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halDMA2D.h"
#include "System/Graphics/eosColor.h"


namespace htl {

	// Valors que depenen de format de color
	//
	template <eos::ColorFormat format_>
	struct DMA2DOptionsFor {
	};
	template<>
	struct DMA2DOptionsFor<eos::ColorFormat::argb8888> {
		constexpr static const halDMA2DOptions DFMT = HAL_DMA2D_DFMT_ARGB8888;
		constexpr static const halDMA2DOptions SFMT = HAL_DMA2D_SFMT_ARGB8888;
	};
	template<>
	struct DMA2DOptionsFor<eos::ColorFormat::rgb888> {
		constexpr static const halDMA2DOptions DFMT = HAL_DMA2D_DFMT_RGB888;
		constexpr static const halDMA2DOptions SFMT = HAL_DMA2D_SFMT_RGB888;
	};
	template<>
	struct DMA2DOptionsFor<eos::ColorFormat::rgb565> {
		constexpr static const halDMA2DOptions DFMT = HAL_DMA2D_DFMT_RGB565;
		constexpr static const halDMA2DOptions SFMT = HAL_DMA2D_SFMT_RGB565;
	};
	template<>
	struct DMA2DOptionsFor<eos::ColorFormat::l8> {
		constexpr static const halDMA2DOptions SFMT = HAL_DMA2D_SFMT_L8;
	};
}


#endif // __STM32_htlDMA2D__
