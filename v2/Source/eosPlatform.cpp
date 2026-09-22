module;


#include "eos.h"


export module Eos.Configuration.Platform;


import Eos.Types;


export namespace eos {

    enum class PlatformID {

        // PIC32MX4xxxFxxx
        pic32mx460f512l,

        // STM32F0xx
        stm32f030r8,

        // STM32F429xx
        stm32f429zi,

        // STM32F7446xx
        stm32f746ng,

        // STM32G031xx
        stm32g031k8,

        // STM32G071xx
        stm32g071c8,
        stm32g071cb,
        stm32g071k8,
        stm32g071kb,
        stm32g071r8,
        stm32g071rb,

        // STM32G0B1xx
        stm32g0B1re

    };

#ifdef EOS_PLATFORM_STM32G0B1RE
    constexpr PlatformID currentPlatform = PlatformID::stm32g0B1re;
#else
    error "Unknown platformm"
#endif

    template <PlatformID id_>
    struct Platform {
    };

    template <>
    struct Platform<PlatformID::stm32g0B1re> {
        static constexpr PlatformID id        = PlatformID::stm32g0B1re;
        static constexpr UInt32     ramSize   = 0;
        static constexpr UInt32     flashSize = 0;
    };
}
