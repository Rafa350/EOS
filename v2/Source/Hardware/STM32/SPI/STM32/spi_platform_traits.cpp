module;


export module Eos.Hardware.SPI.PlatformTraits;


import Eos.Configuration.Platform;


namespace eos::hardware::spi::internal {

	namespace hidden {

		template<PlatformID platformID_>
		struct Traits;

		// STM32F429ZI
		template<>
		struct Traits<PlatformID::STM32_F429_ZI> {
			enum class DeviceID { spi1, spi2 };
		};

		// STM32G031K8
		template<>
		struct Traits<PlatformID::STM32_G031_K8> {
			enum class DeviceID { spi1, spi2 };
		};

		// STM32G0B1RE
		template<>
		struct Traits<PlatformID::STM32_G0B1_RE> {
			enum class DeviceID { spi1, spi2, spi3 };
		};
	}

	export using PlatformTraits = hidden::Traits<Platform::id>;
}
