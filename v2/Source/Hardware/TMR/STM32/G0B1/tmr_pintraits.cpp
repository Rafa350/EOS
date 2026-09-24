module;


#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


export module Eos.Hardware.TMR.Pins;


import Eos.Hardware.TMR.Identifiers;


namespace g = htl::gpio;


export namespace eos::hardware::tmr {

    namespace internal {

        enum class PinUse {
            ch1,
            ch2,
            ch3,
            ch4
        };

		template <TMRDeviceID, PinUse, g::PortID, g::PinID>
		struct PinTraits;

#if defined(HTL_TMR3_EXIST)
        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinUse::ch1, g::PortID::portA, g::PinID::pin6> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinUse::ch1, g::PortID::portB, g::PinID::pin4> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinUse::ch1, g::PortID::portC, g::PinID::pin6> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinUse::ch2, g::PortID::portA, g::PinID::pin7> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinUse::ch2, g::PortID::portB, g::PinID::pin5> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinUse::ch2, g::PortID::portC, g::PinID::pin7> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinUse::ch3, g::PortID::portB, g::PinID::pin0> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinUse::ch3, g::PortID::portC, g::PinID::pin8> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinUse::ch4, g::PortID::portB, g::PinID::pin1> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };

        template<>
        struct PinTraits<TMRDeviceID::tmr3, PinUse::ch4, g::PortID::portC, g::PinID::pin9> {
            static constexpr g::AlternateFunction value = g::AlternateFunction::_1;
        };
#endif
    }
}
