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

        enum class PllPDivider {
        	div2,
			div4,
			div6,
			div8
        };

        enum class PllQDivider {
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
			div15
        };

        enum class SysClkSource {
            hsi,
            hse,
            pll
        };

        enum class HClkPrescaler {
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
		bool pllConfigure(PllSource source, unsigned multiplier, unsigned divider, PllPDivider divP, PllQDivider divQ);
		//bool pllSAIConfigure(unsigned divider, PllSAIQDivider divQ);
		//bool pllI2SConfigure(unsigned divider, PllI2SQDivider divQ);

		bool sysclkSetSource(SysClkSource source);
		void hclkSetPrescaler(HClkPrescaler value);
		void pclk1SetPrescaler(PClkPrescaler value);
		void pclk2SetPrescaler(PClkPrescaler value);

		unsigned getClockFrequency(ClockID clockId);
    }
}


#endif // __STM32F4_htlClock__
