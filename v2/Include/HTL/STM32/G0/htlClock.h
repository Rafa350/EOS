#pragma once
#ifndef __STM32_G0_htlClock__
#define __STM32_G0_htlClock__


#include "HTL/STM32/htl.h"


#if !defined(EOS_PLATFORM_STM32G0)
	#error "Valid for STM32G0 platform only"
#endif


namespace htl {

	namespace clock {

		enum class ClockID {
			sysclk,
			pclk,
			timpclk,
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

		enum class MCODivider {
			_1,
			_2,
			_4,
			_8,
			_16,
			_32,
			_64,
			_128
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
                static bool configurePll(PllSource source, unsigned multiplier, unsigned divider);
                static bool configurePllP(unsigned divider);
                static bool configurePllQ(unsigned divider);
                static bool configurePllR(unsigned divider);

                static void configureMCO(MCOOutput output, MCOSource source, MCODivider divider);

                static bool setSysClkSource(SysClkSource source);
                static void setHsisysPrescaler(HsisysPrescaler value);
                static void setHClkPrescaler(HClkPrescaler value);
                static void setPClkPrescaler(PClkPrescaler value);

                static unsigned getClockFrequency(ClockID clockId);
        };
	}
}


#endif // __STM32_G0_htlClock__
