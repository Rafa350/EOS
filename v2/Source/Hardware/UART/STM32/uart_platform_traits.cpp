module;


export module Eos.Hardware.UART.__PLATFORM_TRAITS;


import Eos.Configuration.Platform;


namespace eos::hardware::uart {

	namespace internal {

		enum class DeviceID_Type1 { uart1, uart2 };
		enum class DeviceID_Type2 { uart1, uart2, uart3, uart4 };
		enum class DeviceID_Type3 { uart1, uart2, uart3, uart4, uart5, uart6 };

		enum class ClockSource_Type1 { pclk, sysclk, hsi16, lse };
		enum class ClockSource_Type2 { pclk, sysclk1, hsi, lse };

		template<PlatformID>
		struct PlatformTraits {
		};

		// STM32G031K8
		template<>
		struct PlatformTraits<PlatformID::STM32_G031_K8> {
			using DeviceID = DeviceID_Type1;
		};

		// STM32G071RB
		template<>
		struct PlatformTraits<PlatformID::STM32_G071_RB> {
			using DeviceID = DeviceID_Type2;
		};

		// STM32G0B1RE
		template<>
		struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
			using DeviceID = DeviceID_Type3;
			using ClockSource = ClockSource_Type1;
		};
	}

	export using UARTDeviceID = internal::PlatformTraits<Platform::id>::DeviceID;
	export using ClockSource = internal::PlatformTraits<Platform::id>::ClockSource;
}
