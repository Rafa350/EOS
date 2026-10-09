module;


#include "hardware.h"


export module Eos.Hardware.Clock;


import Eos.Configuration.Platform;
import Eos.Hardware.Flash;
import Eos.Types;


namespace eos::hardware::clock {

    namespace internal {

        // ---------------------------------
        // Traits depenents de la plataforma
        //
        enum class ClockID_Type1 { sysclk, pclk, timpclk, hclk, hclk8, hse,
            hsi16, hsi48, lse, lsi, hsisys, pllpclk, pllqclk, pllrclk };

        enum class PLLSource_Type1 { hsi16, hse };
        enum class PLLSource_Type2 { hsi, hse };

        enum class SystemClockSource_Type1 { lsi, lse, hse, pllrclk, hsisys };

        template <PlatformID platformId_>
        class PlatformTraits {
        };

        template <>
        class PlatformTraits<PlatformID::STM32_G0B1_RE> {
            public:
                static constexpr bool has_HSI16 = true;
                static constexpr bool has_HSI48 = true;

            public:
                using ClockID = ClockID_Type1;
    		    using SystemClockSource = SystemClockSource_Type1;
                using PLLSource = PLLSource_Type1;
        };

        // -------------------
        // Interface per HSI16
        //
        template <bool use>
        class Clock_HSI16: private StaticClass<Clock_HSI16<use>> {
        };

        template <>
        class Clock_HSI16<true>: private StaticClass<Clock_HSI16<true>> {
            public:
			    static constexpr UInt32 clockHSI16frequency = CLOCK_HSI16_FREQUENCY;

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
        };

        template <>
        class Clock_HSI48<true>: private StaticClass<Clock_HSI48<true>> {
            public:
                static constexpr UInt32 clockHSI48frequency = CLOCK_HSI48_FREQUENCY;

            public:
                static void enableHSI48();
                static void disableHSI48();
                [[nodiscard]] static bool isHSI48Enabled();
        };

    }

    export class Clock:
        private StaticClass<Clock>,
        public internal::Clock_HSI16<internal::PlatformTraits<Platform::id>::has_HSI16>,
        public internal::Clock_HSI48<internal::PlatformTraits<Platform::id>::has_HSI48> {

        private:
            using PlatformTraits = internal::PlatformTraits<Platform::id>;

        public:
            using ClockID = PlatformTraits::ClockID;
            using SystemClockSource = PlatformTraits::SystemClockSource;
            using PLLsource = PlatformTraits::PLLSource;
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
            static constexpr UInt32 clockLSIfrequency = CLOCK_LSI_FREQUENCY;
            static constexpr UInt32 clockLSEfrequency = CLOCK_LSE_FREQUENCY;
            static constexpr UInt32 clockHSEfrequency = CLOCK_HSE_FREQUENCY;

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
    };

}
