module;

#include "hardware.h"


export module Eos.Hardware.Clock;


import Eos.Hardware.Flash;
import Eos.Platform;
import Eos.Types;


namespace eos::hardware::clock::internal {

    namespace hidden {

        // Identificador del Clock
        //
		enum class ClockID_F0xx { sysclk, pclk, hclk, hse, hsi, lse, lsi };
        enum class ClockID_F4xx { sysclk, pclk1, pclk2, tim1clk, tim2clk,
                                  hclk, hse, hsi, lse, lsi };
        using      ClockID_F7xx = ClockID_F4xx;
        enum class ClockID_G0xx { sysclk, pclk, timpclk, hclk, hclk8, hse,
                                  hsi16, lse, lsi, hsisys, pllpclk, pllqclk,
                                  pllrclk };
        enum class ClockID_G0Bx { sysclk, pclk, timpclk, hclk, hclk8, hse,
                                  hsi16, hsi48, lse, lsi, hsisys, pllpclk,
                                  pllqclk, pllrclk };

        // Font del clock del sistema
        //
        enum class SystemClockSource_F0xx { hsi, hse, pll };
        using      SystemClockSource_F4xx = SystemClockSource_F0xx;
        using      SystemClockSource_F7xx = SystemClockSource_F0xx;
        enum class SystemClockSource_G0xx { lsi, lse, hse, pllrclk, hsisys };

        // Font del PLL
        //
        enum class PLLSource_F0xx { hsi, hse };
        using      PLLSource_F4xx = PLLSource_F0xx;
        using      PLLSource_F7xx = PLLSource_F0xx;
        enum class PLLSource_G0xx { hsi16, hse };

        // Traits depenents de la plataforma
        //
        template <PlatformID platformId_>
        class PlatformTraits;

        template <>
        class PlatformTraits<PlatformID::STM32_F429_ZI> {
            public:
                static constexpr bool has_HSI   = true;
                static constexpr bool has_HSI16 = false;
                static constexpr bool has_HSI48 = false;

            public:
                using ClockID           = ClockID_F4xx;
                using SystemClockSource = SystemClockSource_F4xx;
                using PLLSource         = PLLSource_F4xx;
        };

        template <>
        class PlatformTraits<PlatformID::STM32_G0B1_RE> {
            public:
                static constexpr bool has_HSI   = false;
                static constexpr bool has_HSI16 = true;
                static constexpr bool has_HSI48 = true;

            public:
                using ClockID           = ClockID_G0Bx;
                using SystemClockSource = SystemClockSource_G0xx;
                using PLLSource         = PLLSource_G0xx;
        };
    }

    using PlatformTraits = hidden::PlatformTraits<Platform::id>;


    // -------------------
    // Interface per HSI
    //
    template <bool use>
    class Clock_HSI: private StaticClass<Clock_HSI<use>> {
        // Buida per defecte
    };

    template <>
    class Clock_HSI<true>: private StaticClass<Clock_HSI<true>> {
        public:
            static void enableHSI(bool kernelMode = false);
            static void disableHSI();
            [[nodiscard]] static bool isHSIEnabled();
    };

    // -------------------
    // Interface per HSI16
    //
    template <bool use>
    class Clock_HSI16: private StaticClass<Clock_HSI16<use>> {
        // Buida per defecte
    };

    template <>
    class Clock_HSI16<true>: private StaticClass<Clock_HSI16<true>> {
        public:
            static void enableHSI16(bool kernelMode = false);
            static void disableHSI16();
            [[nodiscard]] static bool isHSI16Enabled();
    };

    // -------------------
    // Interface per HSI48
    //
    template <bool use>
    class Clock_HSI48: private StaticClass<Clock_HSI48<use>> {
        // Buida per defecte
    };

    template <>
    class Clock_HSI48<true>: private StaticClass<Clock_HSI48<true>> {
        public:
            static void enableHSI48();
            static void disableHSI48();
            [[nodiscard]] static bool isHSI48Enabled();
    };
}


export namespace eos::hardware::clock {

    class Clock:
        private StaticClass<Clock>,
        public internal::Clock_HSI<internal::PlatformTraits::has_HSI>,
        public internal::Clock_HSI16<internal::PlatformTraits::has_HSI16>,
        public internal::Clock_HSI48<internal::PlatformTraits::has_HSI48> {

        public:
            using ClockID = internal::PlatformTraits::ClockID;
            using SystemClockSource = internal::PlatformTraits::SystemClockSource;
            using PLLsource = internal::PlatformTraits::PLLSource;
            using FlashLatency = flash::Flash::Latency;

            enum class HSEBypass {
                disabled,
                enabled
            };

            enum class PLLPdivider {
                div2, div3, div4, div5, div6, div7, div8, div9,
                div10, div11, div12, div13, div14, div15, div16, div17, div18, div19,
                div20, div21, div22, div23, div24, div25, div26, div27, div28, div29,
                div30, div31, div32,
                disabled
            };

            enum class PLLQdivider {
                div2, div3, div4, div5, div6, div7, div8,
                disabled
            };

            enum class PLLRdivider {
                div2, div3, div4, div5, div6, div7, div8,
                disabled
            };

            enum class AHBPrescaler {
                div1, div2, div4, div8, div16, div64, div128, div256, div512
            };

            enum class APBPrescaler {
                div1, div2, div4, div8, div16
            };

        public:

            // Control del oscilador LSE
            //
            static void enableLSE();
            static void disableLSE();
            [[nodiscard]] static bool isLSEEnabled();

            // Control del oscilador HSE
            //
            static void enableHSE(HSEBypass bypass = HSEBypass::disabled);
            static void disableHSE();
            [[nodiscard]] static bool isHSEEnabled();

            // Control del oscilador LSI
            //
            static void enableLSI();
            static void disableLSI();
            [[nodiscard]] static bool isLSIEnabled();

            // Control del PLL
            //
            static void enablePLL();
            static void disablePLL();
            [[nodiscard]] static bool isPLLEnabled();
            static bool configurePLL(PLLsource source, UInt32 multiplier, UInt32 divider,
                    PLLPdivider divP, PLLQdivider divQ, PLLRdivider divR);

            // Configuracio dels rellotges del sistema
            //
            static bool selectSystemClock(SystemClockSource source, FlashLatency fl);
            static void setAHBPrescaler(AHBPrescaler prescaler);
            static void setAPBPrescaler(APBPrescaler prescaler);

            [[nodiscard]] static UInt32 getClockFrequency(ClockID clockID);

            static void updateSystemCoreClock();
    };
}
