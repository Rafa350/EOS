module;


#include "hardware.h"


export module Eos.Hardware.UART.PlatformTraits;


import Eos.Configuration.Platform;


namespace eos::hardware::uart::internal {

	namespace hidden {

		enum class DeviceID_Type1 { uart1, uart2 };
		enum class DeviceID_Type2 { uart1, uart2, uart3, uart4 };
		enum class DeviceID_Type3 { uart1, uart2, uart3, uart4, uart5, uart6, uart7, uart8 };

		enum class ClockSource_Type1 { pclk, sysclk, hsi16, lse };
		enum class ClockSource_Type2 { pclk, sysclk1, hsi, lse };

		enum class WordBits_Type1 {wb7, wb8, wb9};
		enum class WordBits_Type2 {w8, w9};

		template<PlatformID>
		struct Traits {
		};

		// STM32F429ZI
		template<>
		struct Traits<PlatformID::STM32_F429_ZI> {
			using DeviceID = DeviceID_Type3;
			using WordBits = WordBits_Type1;
		};

		// STM32G031K8
		template<>
		struct Traits<PlatformID::STM32_G031_K8> {
			using DeviceID = DeviceID_Type1;
			using WordBits = WordBits_Type1;
		};

		// STM32G071RB
		template<>
		struct Traits<PlatformID::STM32_G071_RB> {
			using DeviceID = DeviceID_Type2;
			using WordBits = WordBits_Type1;
		};

		// STM32G0B1RE
		template<>
		struct Traits<PlatformID::STM32_G0B1_RE> {
			using DeviceID = DeviceID_Type3;
			using ClockSource = ClockSource_Type1;
			using WordBits = WordBits_Type1;
		};
	}

	export using PlatformTraits = hidden::Traits<Platform::id>;
}
