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
		private:
			static bool _updated;
			static SysClkSource _sysClkSource;
			static PClkPrescaler _pclkPrescaler;
			static HClkPrescaler _hclkPrescaler;
			static PllSource _pllSource;
			static PllMultiplier _pllMultiplier;
			static PllHseDivider _pllHseDivider;

		public:
			static void hsiEnable();
			static void hsiDisable();

			static void hseEnable();
			static void hseDisable();

			static void pllEnable();
			static void pllDisable();
			static void pllSource(PllSource value);
			static void pllMultiplier(PllMultiplier value);
			static void pllHseDivider(PllHseDivider value);

			static bool SysClkSource(SysClkSource source);
			static void HClkPrescaler(HClkPrescaler value);
			static void PClkPrescaler(PClkPrescaler value);

			static void setSysClkSource(SysClkSource value);
			static void setHClkPrescaler(HClkPrescaler value);
			static void setPClkPrescaler(PClkPrescaler value);

			static void reset();
			static bool update();
			static bool isUpdated() { return _updated; }

			static unsigned getClockFrequency(ClockId clockId);
	};
}


#endif // __htlClock__
