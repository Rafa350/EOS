#pragma once
#ifndef __STM32F4_htlClock__
#define __STM32F4_htlClock__

#include "HTL/htl.h"


#if !defined(EOS_PLATFORM_STM32F4)
	#error "Valid for STM32F4 platform only"
#endif


namespace htl {

    namespace clock {

        enum class ClockID {
            sysclk,
            pclk1,
			pclk2,
			timpclk,
            hclk,
            hse,
            hsi,
            lse,
            lsi
        };

        enum class HseBypassMode {
            on,
            off,
            unchanged
        };

        enum class PllSource {
            hsi,
            hse
        };

        enum class PllHseDivider {
            _1,
            _2,
            _3,
            _4,
            _5,
            _6,
            _7,
            _8,
            _9,
            _10,
            _11,
            _12,
            _13,
            _14,
            _15,
            _16
        };

        enum class PllMultiplier {
            _2,
            _3,
            _4,
            _5,
            _6,
            _7,
            _8,
            _9,
            _10,
            _11,
            _12,
            _13,
            _14,
            _15,
            _16
        };

        enum class SysClkSource {
            hsi,
            hse,
            pll
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

		void hsiEnable();
		void hsiDisable();
		bool isHsiEnabled();

		void hseEnable(HseBypassMode bypass = HseBypassMode::off);
		void hseDisable();
		bool isHseEnabled();

		void pllEnable();
		void pllDisable();
		bool isPllEnabled();
		bool setPllSource(PllSource value);
		void setPllMultiplier(PllMultiplier value);
		void setPllHseDivider(PllHseDivider value);

		bool setSysClkSource(SysClkSource source);
		void setHClkPrescaler(HClkPrescaler value);
		void setPClk1Prescaler(PClkPrescaler value);
		void setPClk2Prescaler(PClkPrescaler value);

		unsigned getClockFrequency(ClockID clockId);
    }
}


#endif // __STM32F4_htlClock__
