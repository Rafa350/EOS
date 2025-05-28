#pragma once


#include "HTL/htl.h"


#if !defined(EOS_PLATFORM_STM32F7)
	#error Solo es valido para la plataforma STM32F7
#endif


namespace htl {
    namespace clock {

        enum class ClockID {
            sysclk,
            pclk1,
            pclk2,
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
        	div1,
			div2,
			div3,
			div4,
			div5,
			div6,
			div7,
			div8,
			div9,
			div10,
			div11,
			div12,
			div13,
			div14,
			div15,
			div16
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
            div1,
			div2,
			div4,
			div8,
			div16,
			div64,
			div128,
			div256,
			div512
        };

        enum class PClkPrescaler {
			div1,
			div2,
			div4,
			div8,
			div16
        };

		void hsiEnable();
		void hsiDisable();
		bool hsiIsEnabled();

		void hseEnable(HseBypassMode bypass = HseBypassMode::off);
		void hseDisable();
		bool hseIsEnabled();

		void pllEnable();
		void pllDisable();
		bool pllIsEnabled();
		bool pllSetSource(PllSource value);
		void pllSetMultiplier(PllMultiplier value);
		void pllSetHSEDivider(PllHseDivider value);

		bool sysclkSetSource(SysClkSource source);
		void hclkSetPrescaler(HClkPrescaler value);
		void pclkSetPrescaler(PClkPrescaler value);

		unsigned getClockFrequency(ClockID clockId);
    }
}
