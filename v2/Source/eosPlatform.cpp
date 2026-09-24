module;


#include "eos.h"


export module Eos.Configuration.Platform;


import Eos.Types;


export namespace eos {

    enum class PlatformID {

        // PIC32MX4xxxFxxx
        idPIC32MX460F512L,

        // STM32F0xx
        idSTM32F030R8,

        // STM32F429xx
        idST32F429ZI,

        // STM32F7446xx
        idSTM32F746NG,

        // STM32G031xx
        idSTM32G031K8,

        // STM32G071xx
        idSTM32G071C8,
        idSTM32G071CB,
        idSTM32G071K8,
        idSTM32G071KB,
        idSTM32G071R8,
        idSTM32G071RB,

        // STM32G0B1xx
        idSTM32G0B1RE

    };

#ifdef EOS_PLATFORM_STM32G0B1RE
    constexpr PlatformID currentPlatformId = PlatformID::idSTM32G0B1RE;
#else
    error "Unknown platformm"
#endif

    template <PlatformID id_>
    struct PlatformTraits {};

    template <>
    struct PlatformTraits<PlatformID::idSTM32G0B1RE> {
        static constexpr PlatformID id        = PlatformID::idSTM32G0B1RE;
        static constexpr UInt32     ramSize   = 128;
        static constexpr UInt32     flashSize = 512;
    };

    using Platform = PlatformTraits<currentPlatformId>;
}
