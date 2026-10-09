module;


export module Eos.Hardware.SPI.Identifiers;


import Eos.Configuration.Platform;


namespace eos::hardware::spi {

	namespace internal {

		template<PlatformID platformID_>
		struct PlatformTraits;

		// STM32G031K8
		template<>
		struct PlatformTraits<PlatformID::STM32_G031_K8> {
			enum class DeviceID { spi1, spi2 };
		};

		// STM32G0B1RE
		template<>
		struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
			enum class DeviceID { spi1, spi2, spi3 };
		};
	}

	export using SPIDeviceID = internal::PlatformTraits<Platform::id>::DeviceID;
}
