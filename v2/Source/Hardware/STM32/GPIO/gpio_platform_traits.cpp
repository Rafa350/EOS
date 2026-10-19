module;


#include "hardware.h"


export module Eos.Hardware.GPIO.__PLATFORM_TRAITS;


import Eos.Platform;


namespace eos::hardware::gpio::internal {

    namespace hidden {

        enum class PortID_Type1 {portA, portB, portC, portD, portF};
        enum class PortID_Type2 {portA, portB, portC, portD, portE, portF};
        enum class PortID_Type3 {portA, portB, portC, portD, portE, portF, portG, portH, portI, portJ, portK};

        template <PlatformID platformId_>
        struct PlatformTraits {
        };

        template <>
        struct PlatformTraits<PlatformID::STM32_F429_ZI> {
            using PortID = PortID_Type3;
        };

        template <>
        struct PlatformTraits<PlatformID::STM32_G031_K8> {
            using PortID = PortID_Type1;
        };

        template <>
        struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
            using PortID = PortID_Type2;
        };

    }

    export using PlatformTraits = hidden::PlatformTraits<Platform::id>;
}
