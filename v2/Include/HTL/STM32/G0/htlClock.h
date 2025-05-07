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
		bool configurePll(PllSource source, unsigned multiplier, unsigned divider);
		bool configurePllP(unsigned divider);
		bool configurePllQ(unsigned divider);
		bool configurePllR(unsigned divider);

		void configureMCO(MCOOutput output, MCOSource source, MCODivider divider);

		bool setSysClkSource(SysClkSource source);
		void setHsisysPrescaler(HsisysPrescaler value);
		void setHClkPrescaler(HClkPrescaler value);
		void setPClkPrescaler(PClkPrescaler value);

		unsigned getClockFrequency(ClockID clockId);
	}
}


#endif // __STM32G0_htlClock__
