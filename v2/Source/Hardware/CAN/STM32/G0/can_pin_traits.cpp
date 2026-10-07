module;


#include "hardware.h"
#include "HTL/htlGPIO.h"


export module Eos.Hardware.CAN.__PIN_TRAITS;


import Eos.Hardware.CAN.__PLATFORM_TRAITS;


namespace g = htl::gpio;


export namespace eos::hardware::can::internal {

    enum class PinFunction {tx, rx};

    template <CANDeviceID, PinFunction, g::PortID, g::PinID>
    struct PinTraits;

#if defined(FDCAN1_BASE)
    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::tx, g::PortID::portA, g::PinID::pin12> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::tx, g::PortID::portB, g::PinID::pin9> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::tx, g::PortID::portD, g::PinID::pin13> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::rx, g::PortID::portA, g::PinID::pin11> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::rx, g::PortID::portB, g::PinID::pin8> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::rx, g::PortID::portD, g::PinID::pin12> {
        static constexpr auto value = g::AlternateFunction::_3;
    };
#endif

#if defined(FDCAN2_BASE)
    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::tx, g::PortID::portB, g::PinID::pin1> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::tx, g::PortID::portB, g::PinID::pin6> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::tx, g::PortID::portB, g::PinID::pin13> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::tx, g::PortID::portD, g::PinID::pin15> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::rx, g::PortID::portB, g::PinID::pin0> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::rx, g::PortID::portB, g::PinID::pin5> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::rx, g::PortID::portB, g::PinID::pin12> {
        static constexpr auto value = g::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::rx, g::PortID::portD, g::PinID::pin14> {
        static constexpr auto value = g::AlternateFunction::_3;
    };
#endif

}
