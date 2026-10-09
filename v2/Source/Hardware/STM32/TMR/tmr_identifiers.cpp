export module Eos.Hardware.TMR.Identifiers;


import Eos.Configuration.Platform;


namespace eos::hardware::tmr {

    namespace internal {

        template<PlatformID platformID_>
        struct PlatformTraits;

        // STM32G031_K8
        template<>
        struct PlatformTraits<PlatformID::STM32_G031_K8> {
            enum class DeviceID { };
        };

        // STM32G0B1RE
        template<>
        struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
            enum class DeviceID { tmr1, tmr2, tmr3, tmr4, tmr6, tmr7, tmr14, tmr15, tmr16, tmr17 };
        };
    }

    export using TMRDeviceID = internal::PlatformTraits<Platform::id>::DeviceID;
}
