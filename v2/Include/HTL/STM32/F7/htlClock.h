#pragma once


#include "HTL/htl.h"


#if !defined(EOS_PLATFORM_STM32F7)
	#error Solo es valido para la plataforma STM32F7
#endif


namespace htl {

    namespace clock {

        enum class ClockID {
            sysclk,
            pclk,
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
        void setPClkPrescaler(PClkPrescaler value);

        unsigned getClockFrequency(ClockID clockId);
    }
}
