module;


#include "hardware.h"


export module Eos.Hardware.GPIO.__ACTIVATOR;


import Eos.Bits;
import Eos.Hardware.GPIO.__PLATFORM_TRAITS;
import Eos.Hardware.GPIO.__PORT_TRAITS;
import Eos.Hardware.GPIO.__TYPES;
import Eos.Hardware.Interrupts;
import Eos.Types;


namespace eos::hardware::gpio::internal {

    export template <PortID portId_>
    class Activator final: private StaticClass<Activator<portId_>> {
        private:
            using PortTraits = internal::PortTraits<portId_>;

        private:
            static constexpr auto _addr = PortTraits::activateAddr;
            static constexpr auto _pos = PortTraits::activatePos;

        private:
            static UInt16 _usedPins;

        public:
            static void activate(PinMask mask);
            static void deactivate(PinMask mask);
    };

    template <PortID portId_>
    uint16_t Activator<portId_>::_usedPins {0};
}


using namespace eos;
using namespace eos::hardware::gpio;
using namespace eos::hardware::gpio::internal;
using namespace eos::hardware::interrupts;


/// -----------------------------------------------------------------------------------------------
/// @brief    Crida __DSB() desde el modul.
///
void DSB() {

    __DSB();
}


/// -----------------------------------------------------------------------------------------------
/// @brief    Activa el dispositiu.
/// @tparam   portId_: Identificador del port.
/// @param    mask: Mascara dels pins a activar.
///
template <PortID portId_>
void Activator<portId_>::activate(
    PinMask mask) {

    auto i = Irq::getInterruptState();
    Irq::disableInterrupts();

    if (!_usedPins) {
        Bits::set(*reinterpret_cast<UInt32*>(_addr), (UInt32)(1 << _pos));
        DSB();
    }
    Bits::set(_usedPins, (UInt16) mask);

    Irq::restoreInterrupts(i);
}


/// -----------------------------------------------------------------------------------------------
/// @brief    Desactiva el dispositiu.
/// @tparam   portId_: Identificador del port.
/// @param    mask: Mascara dels pins a desactivat.
///
template <PortID portId_>
void Activator<portId_>::deactivate(
    PinMask mask) {

    auto i = Irq::getInterruptState();
    Irq::disableInterrupts();

    Bits::clear(_usedPins, (UInt16)mask);
    if (!_usedPins) {
        Bits::clear(*reinterpret_cast<UInt32*>(_addr), (UInt32)(1 << _pos));
        DSB();
    }

    Irq::restoreInterrupts(i);
}
