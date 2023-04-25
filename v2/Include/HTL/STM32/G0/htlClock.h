#pragma once
#ifndef __STM32G0_htlClock__
#define __STM32G0_htlClock__


#include "HTL/htl.h"


#if !defined(EOS_PLATFORM_STM32G0)
	#error "Valid for STM32G0 platform only"
#endif


namespace htl {

	enum class ClockId {
		sysclk,
		pclk,
		hclk,
		hclk8,
		hse,
		hsi16,
		hsi48,
		lse,
		lsi,
		hsisys,
		pllpclk,
		pllqclk,
		pllrclk
	};

	enum class HseBypassMode {
		on,
		off,
		unchanged
	};

	enum class MCOOutput {
		_1,
		_2
	};

	enum class MCOSource {
		none,
		lsi,
		lse,
		sysclk,
		hsi16,
		hse,
		pllrclk
	};

	enum class PllSource {
		hsi16,
		hse
	};

	enum class SysClkSource {
		lsi,
		lse,
		hse,
		pllrclk,
		hsisys
	};

	enum class HsisysPrescaler {
		_1,
		_2,
		_4,
		_8,
		_16,
		_32,
		_64,
		_128
	};

	enum class HClkPrescaler {
		_1,
		_2,
		_4,
		_8,
		_16,
		_64,
		_128,
		_256,
		_512
	};

	enum class PClkPrescaler {
		_1,
		_2,
		_4,
		_8,
		_16
	};

	class Clock {
		public:
			static void hsi16Enable();
			static void hsi16Disable();
            static bool isHsi16Enabled();

            static void hseEnable(HseBypassMode bypass = HseBypassMode::off);
			static void hseDisable();
			static bool isHseEnabled();

			static void lsiEnable();
			static void lsiDisable();
			static bool isLsiEnabled();

            static void lseEnable();
            static void lseDisable();
            static bool isLseEnabled();

			static void pllEnable();
			static void pllDisable();
            static bool isPllEnabled();
			static bool configurePll(PllSource source, int multiplier, int divider);
			static bool configurePllP(int divider);
			static bool configurePllQ(int divider);
			static bool configurePllR(int divider);

			static void configureMCO(MCOOutput output, MCOSource source, int divider);

			static bool setSysClkSource(SysClkSource source);
			static void setHsisysPrescaler(HsisysPrescaler value);
			static void setHClkPrescaler(HClkPrescaler value);
			static void setPClkPrescaler(PClkPrescaler value);

			static unsigned getClockFrequency(ClockId clockId);
	};
}


#endif // __STM32G0_htlClock__
