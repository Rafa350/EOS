#pragma once
#ifndef __STM32G0_htlClock__
#define __STM32G0_htlClock__


// HTL includes
//
#include "HTL/STM32/htl.h"


// Platform check
//
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
			out1,
			out2
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
			div1,
			div2,
			div4,
			div8,
			div16,
			div32,
			div64,
			div128
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
			div1,
			div2,
			div4,
			div8,
			div16,
			div32,
			div64,
			div128
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

		void hsi16Enable();
		void hsi16Disable();
		bool hsi16IsEnabled();

		void hseEnable(HseBypassMode bypass = HseBypassMode::off);
		void hseDisable();
		bool hseIsEnabled();

		void lsiEnable();
		void lsiDisable();
		bool lsiIsEnabled();

		void lseEnable();
		void lseDisable();
		bool lseIsEnabled();

		void pllEnable();
		void pllDisable();
		bool pllIsEnabled();
		bool pllConfigure(PllSource source, unsigned multiplier, unsigned divider);
		bool pllSetPDivider(unsigned divider);
		bool pllSetQDivider(unsigned divider);
		bool pllSetRDivider(unsigned divider);

		void mcoConfigure(MCOOutput output, MCOSource source, MCODivider divider);

		bool sysclkSetSource(SysClkSource source);
		void hsisysSetPrescaler(HsisysPrescaler value);
		void hclkSetPrescaler(HClkPrescaler value);
		void pclkSetPrescaler(PClkPrescaler value);

		unsigned getClockFrequency(ClockID clockId);
	}
}


#endif // __STM32G0_htlClock__
