#pragma once
#ifndef __STM32_htlClock__
#define __STM32_htlCLock__


#include "HTL/STM32/htl.h"


#if defined(EOS_PLATFORM_STM32F0)
    #include "HTL/STM32/F0/htlClock.h"

#elif defined(EOS_PLATFORM_STM32F1)
    #include "HTL/STM32/F1/htlClock.h"

#elif defined(EOS_PLATFORM_STM32F4)
    #include "HTL/STM32/F4/htlClock.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "HTL/STM32/F7/htlClock.h"

#elif defined(EOS_PLATFORM_STM32G0)
    #include "HTL/STM32/G0/htlClock.h"

#else
	#error "Unknown platform"
#endif


namespace htl {
	namespace clock {

#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		enum class SystemClockSource {
			hsi,
			hse,
			pll
		};
#elif defined(EOS_PLATFORM_STM32G0)
		enum class SystemClockSource {
			lsi,
			lse,
			hse,
			pllrclk,
			hsisys
		};
#else
	#error "Unknown platform"
#endif

#if defined(EOS_PLATFORM_STM32F4)
		enum class PLLsource {
			hsi,
			hse
		};
#elif defined(EOS_PLATFORM_STM32G0)
		enum class PLLsource {
			hsi16,
			hse
		};

		enum class PLLPdivider {
			/*** Valors critics ***/
			disabled,
			div2, div3, div4, div5, div6, div7, div8, div9,
			div10, div11, div12, div13, div14, div15, div16, div17, div18, div19,
			div20, div21, div22, div23, div24, div25, div26, div27, div28, div29,
			div30, div31, div32
		};

		enum class PLLQdivider {
			/*** Valors critics ***/
			disabled,
			div2, div3, div4, div5, div6, div7, div8
		};

		enum class PLLRdivider {
			/*** Valors critics ***/
			disabled,
			div2, div3, div4, div5, div6, div7, div8
		};
#else
#error "Unknown platform"
#endif

		class ClockDevice {
			private:
				static ClockDevice _instance;

			public:
				static constexpr ClockDevice *pInst = &_instance;
				static constexpr ClockDevice &rInst = _instance;
				static constexpr unsigned clockLSIfrequency = CLOCK_LSI_FREQUENCY;
				static constexpr unsigned clockLSEfrequency = CLOCK_LSE_FREQUENCY;
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr unsigned clockHSIfrequency = CLOCK_HSI_FREQUENCY;
#elif defined(EOS_PLATFORM_STM32G0)
				static constexpr unsigned clockHSI16frequency = CLOCK_HSI16_FREQUENCY;
#if defined(EOS_PLATFORM_STM32G0B1)
				static constexpr unsigned clockHSI48frequency = CLOCK_HSI48_FREQUENCY;
#endif
#else
#error "Unknown platform"
#endif
				static constexpr unsigned clockHSEfrequency = CLOCK_HSE_FREQUENCY;

			private:
				ClockDevice();
				ClockDevice(const ClockDevice&) = delete;

				bool operator = (const ClockDevice&) = delete;

			public:
				// Control del rellotge LSE
				//
				void enableLSE() const;
				void disableLSE() const;
				bool isLSEEnabled() const;

				// Control del rellotge HSE
				//
				void enableHSE(HseBypassMode bypass = HseBypassMode::off) const;
				void disableHSE() const;
				bool isHSEEnabled() const;

				// Control del rellotge LSI
				//
				void enableLSI() const;
				void disableLSI() const;
				bool isLSIEnabled() const;

#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				// Control del rellotge HSI
				//
				void enableHSI() const;
				void disableHSI() const;
				bool isHSIEnabled() const;
#elif defined(EOS_PLATFORM_STM32G0)
				// Control del rellotge HSI16
				//
				void enableHSI16(bool kernelMode = false) const;
				void disableHSI16() const;
				bool isHSI16Enabled() const;

#if defined(EOS_PLATFORM_STM32G0B1)
				// Control del rellotge HSI48
				//
				void enableHSI48() const;
				void disableHSI48() const;
				bool isHSI48Enabled() const;
#endif
#else
#error "Unknown platform"
#endif

				// Control del PLL
				//
				void enablePLL() const;
				void disablePLL() const;
				bool isPLLEnabled() const;
#if defined(EOS_PLATFORM_STM32G0)
				bool configurePLL(PLLsource source, unsigned multiplier, unsigned divider, PLLPdivider divP, PLLQdivider divQ, PLLRdivider divR) const;
#endif

				bool selectSystemClock(SystemClockSource source) const;
				unsigned getClockFrequency(ClockID clockID) const;
		};
	}
}


#endif // __STM32_htlClock__
