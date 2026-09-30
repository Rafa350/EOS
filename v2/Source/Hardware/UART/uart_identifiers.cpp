module;


export module Eos.Hardware.UART.Identifiers;


import Eos.Configuration.Platform;


namespace eos::hardware::uart {

	namespace internal {

		template<PlatformID platformID_>
		struct PlatformTraits;

		// STM32G031K8
		template<>
		struct PlatformTraits<PlatformID::STM32_G031_K8> {
			enum class DeviceID { uart1, uart2 };
		};

		// STM32G0B1RE
		template<>
		struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
			enum class DeviceID { uart1, uart2, uart3, uart4, uart5, uart6 };
		};
	}

	export using UARTDeviceID = internal::PlatformTraits<Platform::id>::DeviceID;
}
