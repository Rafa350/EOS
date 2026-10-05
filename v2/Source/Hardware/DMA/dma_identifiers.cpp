module;


export module Eos.Hardware.DMA.Identifiers;


import Eos.Configuration.Platform;


namespace eos::hardware::dma {

    namespace internal {

		template<PlatformID platformID_>
		struct PlatformTraits;

		// STM32G0B1RE
		template<>
		struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
			enum class DeviceID { dma11, dma12, dma13, dma14, dma15, dma16, dma17,
                dma21, dam22, dma23, dma24, dma25};
		};
    }

	export using DMADeviceID = internal::PlatformTraits<Platform::id>::DeviceID;

}
