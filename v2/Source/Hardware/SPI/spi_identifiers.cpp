module;


export module Eos.Hardware.SPI.Identifiers;


import Eos.Configuration.Platform;


namespace eos {
	namespace hardware::uart {
		namespace internal {

			template<PlatformID platformID_>
			struct PlatformTraits;

			template<>
			struct PlatformTraits<PlatformID::STM32_G031_K8> {
				enum class DeviceID { spi1, spi2 };
			};

			template<>
			struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
				enum class DeviceID { spi1, spi2, spi3 };
			};
		}

		export using SPIDeviceID = internal::PlatformTraits<Platform::id>::DeviceID;
	}

}
