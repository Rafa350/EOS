module;


#include "hardware.h"


export module Eos.Hardware.TMR._PinTraits;


import Eos.Hardware.GPIO;
import Eos.Hardware.TMR._Types;


export namespace eos::hardware::tmr::internal {

    enum class PinFunction { ch1, ch2, ch3, ch4 };

    template <TMRDeviceID, PinFunction, gpio::PortID, gpio::PinID>
    struct PinTraits;

    #ifdef TIM3_BASE
    template<>
    struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch1, gpio::PortID::portA, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };

    template<>
    struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch1, gpio::PortID::portB, gpio::PinID::pin4> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };

    template<>
    struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch1, gpio::PortID::portC, gpio::PinID::pin6> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };

    template<>
    struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch2, gpio::PortID::portA, gpio::PinID::pin7> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };

    template<>
    struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch2, gpio::PortID::portB, gpio::PinID::pin5> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };

    template<>
    struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch2, gpio::PortID::portC, gpio::PinID::pin7> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };

    template<>
    struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch3, gpio::PortID::portB, gpio::PinID::pin0> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };

    template<>
    struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch3, gpio::PortID::portC, gpio::PinID::pin8> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };

    template<>
    struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch4, gpio::PortID::portB, gpio::PinID::pin1> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };

    template<>
    struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch4, gpio::PortID::portC, gpio::PinID::pin9> {
        static constexpr auto value = gpio::AlternateFunction::_1;
    };
    #endif // TIM3_BASE
}
