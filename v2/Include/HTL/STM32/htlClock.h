#pragma once
#ifndef __htlClock__
#define __htlClock__


#include "htl.h"


namespace htl {

	enum class ClockId {
		sysclk,
		pclk,
		hclk,
		hse,
		hsi,
		hsi14,
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

	class Clock {
		public:
			static void hsiEnable();
			static void hsiDisable();
            static bool isHsiEnabled();

			static void hseEnable(HseBypassMode bypass = HseBypassMode::off);
			static void hseDisable();
            static bool isHseEnabled();

			static void pllEnable();
			static void pllDisable();
            static bool isPllEnabled();
			static bool setPllSource(PllSource value);
			static void setPllMultiplier(PllMultiplier value);
			static void setPllHseDivider(PllHseDivider value);

			static bool setSysClkSource(SysClkSource source);
			static void setHClkPrescaler(HClkPrescaler value);
			static void setPClkPrescaler(PClkPrescaler value);

			static unsigned getClockFrequency(ClockId clockId);
	};
}


#endif // __htlClock__
