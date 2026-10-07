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

		enum class WordBits_Type1 {wb7, wb8, wb9};
		enum class WordBits_Type2 {w8, w9};

		template<PlatformID>
		struct PlatformTraits {
		};

		// STM32G031K8
		template<>
		struct PlatformTraits<PlatformID::STM32_G031_K8> {
			using DeviceID = DeviceID_Type1;
			using WordBits = WordBits_Type1;
		};

		// STM32G071RB
		template<>
		struct PlatformTraits<PlatformID::STM32_G071_RB> {
			using DeviceID = DeviceID_Type2;
			using WordBits = WordBits_Type1;
		};

		// STM32G0B1RE
		template<>
		struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
			using DeviceID = DeviceID_Type3;
			using ClockSource = ClockSource_Type1;
			using WordBits = WordBits_Type1;
		};
	}

	export using PlatformTraits = internal::PlatformTraits<Platform::id>;
}
