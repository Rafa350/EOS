module;


#include "HTL/htl.h"


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
        class Clock_HSI16 {
        };

        template <>
        class Clock_HSI16<true> {
            public:
			    static constexpr UInt32 clockHSI16frequency = 16000000;

            public:
                void enableHSI16(bool kernelMode = false) const;
                void disableHSI16() const;
                [[nodiscard]] bool isHSI16Enabled() const;
        };

        // -------------------
        // Interface per HSI48
        //
        template <bool use>
        class Clock_HSI48;

        template <>
        class Clock_HSI48<true> {
            public:
                static constexpr UInt32 clockHSI48frequency = 48000000;

            public:
                void enableHSI48() const;
                void disableHSI48() const;
                [[nodiscard]] bool isHSI48Enabled() const;
        };

    }

    export class Clock:
        private NonCopyableClass,
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

        private:
            static Clock _instance;

        public:
            static constexpr Clock *pInst = &_instance;
            static constexpr Clock &rInst = _instance;
            static constexpr UInt32 clockLSIfrequency = CLOCK_LSI_FREQUENCY;
            static constexpr UInt32 clockLSEfrequency = CLOCK_LSE_FREQUENCY;
            static constexpr UInt32 clockHSEfrequency = CLOCK_HSE_FREQUENCY;

        private:
            Clock() = default;

        public:

            // Control del oscilador LSE
            //
            void enableLSE() const;
            void disableLSE() const;
            [[nodiscard]] bool isLSEEnabled() const;

            // Control del oscilador HSE
            //
            void enableHSE(HSEBypass bypass = HSEBypass::disabled) const;
            void disableHSE() const;
            [[nodiscard]] bool isHSEEnabled() const;

            // Control del oscilador LSI
            //
            void enableLSI() const;
            void disableLSI() const;
            [[nodiscard]] bool isLSIEnabled() const;

            // Control del PLL
            //
            void enablePLL() const;
            void disablePLL() const;
            [[nodiscard]] bool isPLLEnabled() const;
            bool configurePLL(PLLsource source, UInt32 multiplier, UInt32 divider,
                    PLLPdivider divP, PLLQdivider divQ, PLLRdivider divR) const;

            // Configuracio dels rellotges del sistema
            //
            bool selectSystemClock(SystemClockSource source, FlashLatency fl) const;
            void setAHBPrescaler(AHBPrescaler prescaler) const;
            void setAPBPrescaler(APBPrescaler prescaler) const;

            [[nodiscard]] UInt32 getClockFrequency(ClockID clockID) const;
    };

    Clock Clock::_instance;

}
