module;


#include "hardware.h"


export module Eos.Hardware.FDCAN.__PIN_TRAITS;


import Eos.Hardware.GPIO;
import Eos.Hardware.FDCAN.__PLATFORM_TRAITS;


export namespace eos::hardware::fdcan::internal {

    enum class PinFunction {tx, rx};

    template <CANDeviceID, PinFunction, gpio::PortID, gpio::PinID>
    struct PinTraits;

#if defined(FDCAN1_BASE)
    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::tx, gpio::PortID::portA, gpio::PinID::pin12> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::tx, gpio::PortID::portB, gpio::PinID::pin9> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::tx, gpio::PortID::portD, gpio::PinID::pin13> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::rx, gpio::PortID::portA, gpio::PinID::pin11> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::rx, gpio::PortID::portB, gpio::PinID::pin8> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can1, PinFunction::rx, gpio::PortID::portD, gpio::PinID::pin12> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };
#endif

#if defined(FDCAN2_BASE)
    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::tx, gpio::PortID::portB, gpio::PinID::pin1> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::tx, gpio::PortID::portB, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::tx, gpio::PortID::portB, gpio::PinID::pin13> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::tx, gpio::PortID::portD, gpio::PinID::pin15> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::rx, gpio::PortID::portB, gpio::PinID::pin0> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::rx, gpio::PortID::portB, gpio::PinID::pin5> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::rx, gpio::PortID::portB, gpio::PinID::pin12> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };

    template<>
    struct PinTraits<CANDeviceID::can2, PinFunction::rx, gpio::PortID::portD, gpio::PinID::pin14> {
        static constexpr auto value = gpio::AlternateFunction::_3;
    };
#endif

}
