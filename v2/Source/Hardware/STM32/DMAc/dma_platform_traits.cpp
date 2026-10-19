module;


#include "hardware.h"


export module Eos.Hardware.DMA:PlatformTraits;


import Eos.Platform;


namespace eos::hardware::dma::internal {

	namespace hidden {

		template<PlatformID platformID_>
		struct Traits;

		// STM32F429ZI
		template<>
		struct Traits<PlatformID::STM32_F429_ZI> {
			enum class DeviceID { dma11, dma12, dma13, dma14, dma15, dma16, dma17};
		};

		// STM32G0B1RE
		template<>
		struct Traits<PlatformID::STM32_G0B1_RE> {
			enum class DeviceID { dma11, dma12, dma13, dma14, dma15, dma16, dma17,
                dma21, dam22, dma23, dma24, dma25};
		};
    }

	using PlatformTraits = internal::hidden::Traits<Platform::id>;

}
