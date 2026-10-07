module;


#include "hardware.h"
#include "HTL/htlGPIO.h"


export module Eos.Hardware.TMR.Pins;


import Eos.Hardware.TMR.Identifiers;


namespace g = htl::gpio;


export namespace eos::hardware::tmr {

    namespace internal {

        enum class PinFunction { ch1, ch2, ch3, ch4 };

		template <TMRDeviceID, PinFunction, g::PortID, g::PinID>
		struct PinTraits;

#ifdef TIM3_BASE
        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch1, g::PortID::portA, g::PinID::pin6> {
            static constexpr auto value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch1, g::PortID::portB, g::PinID::pin4> {
            static constexpr auto value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch1, g::PortID::portC, g::PinID::pin6> {
            static constexpr auto value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch2, g::PortID::portA, g::PinID::pin7> {
            static constexpr auto value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch2, g::PortID::portB, g::PinID::pin5> {
            static constexpr auto value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch2, g::PortID::portC, g::PinID::pin7> {
            static constexpr auto value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch3, g::PortID::portB, g::PinID::pin0> {
            static constexpr auto value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch3, g::PortID::portC, g::PinID::pin8> {
            static constexpr auto value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch4, g::PortID::portB, g::PinID::pin1> {
            static constexpr auto value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinFunction::ch4, g::PortID::portC, g::PinID::pin9> {
            static constexpr auto value = g::AlternateFunction::_1;
        };
#endif // TIM3_BASE
    }
}
