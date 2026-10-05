module;


#include "eos.h"


export module Eos.Configuration.Platform;


import Eos.Types;


namespace eos {

    export enum class PlatformID {

        // PIC32MX4xxxFxxx
        PIC32MX_460F512L,

        // STM32F0xx
        STM32_F030_R8,

        // STM32F429xx
        STM32_F429_ZI,

        // STM32F7446xx
        STM32_F746_NG,

        // STM32G031xx
        STM32_G031_K8,

        // STM32G071xx
        STM32_G071_C8,
        STM32_G071_CB,
        STM32_G071_K8,
        STM32_G071_KB,
        STM32_G071_R8,
        STM32_G071_RB,

        // STM32G0B1xx
        STM32_G0B1_RE

    };

#if defined(EOS_PLATFORM_STM32G071RB)
    constexpr PlatformID currentPlatformId = PlatformID::STM32_G071_RB;
#elif defined(EOS_PLATFORM_STM32G0B1RE)
    constexpr PlatformID currentPlatformId = PlatformID::STM32_G0B1_RE;
#else
    error "Unknown platformm"
#endif

    namespace internal {

        template <PlatformID id_>
        struct PlatformTraits {
        };

        template <>
        struct PlatformTraits<PlatformID::STM32_G071_RB> {
            static constexpr PlatformID id                 = PlatformID::STM32_G071_RB;
            static constexpr bool is_STM32                 = true;
            static constexpr bool is_STM32_G0              = true;
            static constexpr bool is_STM32_G071            = true;
            static constexpr bool is_STM32_G071_RB         = true;
            static constexpr const char *deviceName        = "STM32G071RN";
            static constexpr const char *manufacturerName  = "ST-Microelectronics";
            static constexpr UInt32 ramSize                = 32;
            static constexpr UInt32 flashSize              = 128;
        };

        template <>
        struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
            static constexpr PlatformID id                 = PlatformID::STM32_G0B1_RE;
            static constexpr bool is_STM32                 = true;
            static constexpr bool is_STM32_G0              = true;
            static constexpr bool is_STM32_G0B1            = true;
            static constexpr bool is_STM32_G0B1_RE         = true;
            static constexpr const char *deviceName        = "STM32G0B1RE";
            static constexpr const char *manufacturerName  = "ST-Microelectronics";
            static constexpr UInt32 ramSize                = 128;
            static constexpr UInt32 flashSize              = 512;
        };
    }

    export using Platform = internal::PlatformTraits<currentPlatformId>;
}
