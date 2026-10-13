module;


#include "hardware.h"


export module Eos.Hardware.GPIO.__INITIALIZER;


import Eos.Types;
import Eos.Hardware.GPIO.__PORT_TRAITS;
import Eos.Hardware.GPIO.__PIN_TRAITS;
import Eos.Hardware.GPIO.__TYPES;
import Eos.Hardware.GPIO.__UTILS;


export namespace eos::hardware::gpio::internal {

    template <PortID portId_>
    class PortInitializer final: private StaticClass<PortInitializer<portId_>> {
        private:
            using PortTraits = internal::PortTraits<portId_>;

        private:
            static constexpr auto _gpioAddr = PortTraits::gpioAddr;

        public:
            static inline void initInput(PinMask mask, PullUpDown pupd);
            static inline void initOutput(PinMask mask, OutputType type, PullUpDown pupd, Speed speed);
            static inline void deinitialize(PinMask mask);
    };

    template <PortID portId_, PinID pinId_>
    class PinInitializer final {
        private:
            static constexpr auto _gpioAddr = PortTraits<portId_>::gpioAddr;
            static constexpr auto _bit = PinTraits<pinId_>::bit;

        public:
            static inline void initInput(PullUpDown pupd);
            static inline void initOutput(OutputType type, PullUpDown pupd, Speed speed, bool state);
            static inline void initAlternate(OutputType type, PullUpDown pupd, Speed speed, AlternateFunction af);
            static inline void initAnalogic();
            static inline void deinitialize();
    };

}


using namespace eos;
using namespace eos::hardware::gpio;
using namespace eos::hardware::gpio::internal;


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el port com a entrada.
/// @tparam   portId_: Identificador del port.
/// @param    mask: Mascara dels pins a inicalitzar.
/// @param    pupd: Configuracio de les resistencies pull up/down.
///
template <PortID portId_>
void PortInitializer<portId_>::initInput(
    PinMask mask,
    PullUpDown pupd) {

    auto gpioRegs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
    GPIOUtils::initInput(gpioRegs, mask, pupd);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el port com a sortida.
/// @tparam   portId_: Identificador del port.
/// @param    mask: Mascara dels pins a inicalitzar.
/// @param    type: El tipus del driver de sortida.
/// @param    pupd: Configuracio de les resistencies pull up/down.
/// @param    speed: Velocitat de sortida suportada.
///
template <PortID portId_>
void PortInitializer<portId_>::initOutput(
    PinMask mask,
    OutputType type,
    PullUpDown pupd,
    Speed speed) {

    auto gpioRegs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
    GPIOUtils::initOutput(gpioRegs, mask, type, pupd, speed);
}


/// ---------------------------------------------------------------------------
/// @brief    Desinicialitza el port.
/// @tparam   portId_: Identificador del port.
/// @param    mask: Mascara dels pins a desinicialitzar.
///
template <PortID portId_>
void PortInitializer<portId_>::deinitialize(
    PinMask mask) {

    auto gpioRegs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
    GPIOUtils::deinitialize(gpioRegs, mask);
}



/// ---------------------------------------------------------------------------
/// @brief    Inicialitza un pin com a entrada digital.
/// @tparam   portId_: Identificador del port.
/// @tparam   pinId_: Identificador del pin.
/// @param    pupd Configura la resistencia pull up/down.
///
template <PortID portId_, PinID pinId_>
void PinInitializer<portId_, pinId_>::initInput(
    PullUpDown pupd) {

    auto gpioRegs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
    GPIOUtils::initInput(gpioRegs, _bit, pupd);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza un pin com a sortida digital.
/// @tparam   portId_: Identificador del port.
/// @tparam   pinId_: Identificador del pin.
/// @param    type: Tipus de dortida.
/// @param    pupd: Resistencies pull up/down.
/// @param    speed: Velocitat de conmutacio.
/// @param    state: Estat inicial del pin.
///
template <PortID portId_, PinID pinId_>
void PinInitializer<portId_, pinId_>::initOutput(
    OutputType type,
    PullUpDown pupd,
    Speed speed,
    bool state) {

    auto gpioRegs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
    GPIOUtils::initOutput(gpioRegs, _bit, type, pupd, speed, state);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza un pin com sortida alternativa
/// @tparam   portId_: Identificadot del port.
/// @tparam   pinId_: Identificador del pin.
/// @param    type: Tipus de sortidas.
/// @param    pupd: Resistencies pull up/down
/// @param    speed: Velocitat de conmutacio.
/// @param    af: Funcio alternativa.
///
template <PortID portId_, PinID pinId_>
void PinInitializer<portId_, pinId_>::initAlternate(
    OutputType type,
    PullUpDown pupd,
    Speed speed,
    AlternateFunction af) {

    auto gpioRegs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
    GPIOUtils::initAlternate(gpioRegs, _bit, type, pupd, speed, af);
}


/// ---------------------------------------------------------------------------
/// \brief  Inicialitza un pin com a entrada/sortida analogica.
/// @tparam   portId_: Identificadot del port.
/// @tparam   pinId_: Identificador del pin.
///
template <PortID portId_, PinID pinId_>
void PinInitializer<portId_, pinId_>::initAnalogic() {

    auto gpioRegs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
    GPIOUtils::initAnalogic(gpioRegs, _bit);
}


/// ---------------------------------------------------------------------------
/// @brief    Desinicialitza el pin.
/// @tparam   portId_: Identificador del port.
/// @tparam   pinId_: Identificador del pin.
///
template <PortID portId_, PinID pinId_>
void PinInitializer<portId_, pinId_>::deinitialize() {

    auto gpioRegs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
    GPIOUtils::deinitialize(gpioRegs, _bit);
}
