module;


#include "hardware.h"
#include <cstddef>


export module Eos.Hardware.CAN.__DEVICE_TRAITS;


import Eos.Hardware.CAN.__PLATFORM_TRAITS;
import Eos.Types;


using namespace eos;
using namespace eos::hardware::can;


constexpr UInt32 SRAMCAN_SIZE = 848;


export namespace eos::hardware::can::internal {

    template<CANDeviceID>
    struct CANTraits {
    };

#ifdef FDCAN1_BASE
    template <>
    struct CANTraits<CANDeviceID::can1> {
        static constexpr UInt32 canAddr         = FDCAN1_BASE;
        static constexpr UInt32 ramAddr         = SRAMCAN_BASE;

        static constexpr UInt32 activateAddr    = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos     = RCC_APBENR1_FDCANEN_Pos;

        static constexpr UInt32 clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, CCIPR2);
        static constexpr UInt32 clockSourcePos  = RCC_CCIPR2_FDCANSEL_Pos;
        static constexpr UInt32 clockSourceMsk  = RCC_CCIPR2_FDCANSEL_Msk;
    };
#endif

#ifdef FDCAN2_BASE
    template <>
    struct CANTraits<CANDeviceID::can2> {
        static constexpr UInt32 canAddr         = FDCAN2_BASE;
        static constexpr UInt32 ramAddr         = SRAMCAN_BASE + SRAMCAN_SIZE;

        static constexpr UInt32 activateAddr    = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos     = RCC_APBENR1_FDCANEN_Pos;

        static constexpr UInt32 clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, CCIPR2);
        static constexpr UInt32 clockSourcePos  = RCC_CCIPR2_FDCANSEL_Pos;
        static constexpr UInt32 clockSourceMsk  = RCC_CCIPR2_FDCANSEL_Msk;
    };
#endif
}
