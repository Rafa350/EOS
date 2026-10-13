module;


#include "hardware.h"


export module Eos.Hardware.GPIO.__UTILS;


import Eos.Bits;
import Eos.Hardware.GPIO.__TYPES;
import Eos.Hardware.Interrupts;
import Eos.Types;


export namespace eos::hardware::gpio::internal {

    class GPIOUtils final: public StaticClass<GPIOUtils> {
        public:
            static void initInput(GPIO_TypeDef * const gpio, PinMask mask, PullUpDown pupd);
            static void initInput(GPIO_TypeDef * const gpio, PinBit bit, PullUpDown pupd);
            static void initOutput(GPIO_TypeDef * const gpio, PinMask mask, OutputType type, PullUpDown pupd, Speed speed);
            static void initOutput(GPIO_TypeDef * const gpio, PinBit bit, OutputType, PullUpDown pupd, Speed speed, bool state);
            static void initAnalogic(GPIO_TypeDef * const gpio, PinBit bit);
            static void initAlternate(GPIO_TypeDef * const gpio, PinBit bit, OutputType type, PullUpDown pull, Speed speed, AlternateFunction af);
            static void deinitialize(GPIO_TypeDef * const gpio, PinMask mask);
            static void deinitialize(GPIO_TypeDef * const gpio, PinBit bit);
    };

}


namespace eos::hardware::gpio::internal {

    struct MODE {
        static constexpr UInt32 Mask      = 0b11;
        static constexpr UInt32 INPUT     = 0b00;
        static constexpr UInt32 OUTPUT    = 0b01;
        static constexpr UInt32 ALTERNATE = 0b10;
        static constexpr UInt32 ANALOGIC  = 0b11;
    };

    struct PUPD {
        static constexpr UInt32 Mask = 0b11;
        static constexpr UInt32 NONE = 0b00;
        static constexpr UInt32 UP   = 0b01;
        static constexpr UInt32 DOWN = 0b10;
    };

    struct OTYPE {
        static constexpr UInt32 Mask = 0b1;
        static constexpr UInt32 PP   = 0b0;
        static constexpr UInt32 OD   = 0b1;
    };

    struct OSPEED {
        static constexpr UInt32 Mask   = 0b11;
        static constexpr UInt32 LOW    = 0b00;
        static constexpr UInt32 MEDIUM = 0b01;
        static constexpr UInt32 HIGH   = 0b10;
        static constexpr UInt32 FAST   = 0b11;
    };

    struct AF {
        static constexpr UInt32 Mask = 0b1111;
    };

    UInt32 convert(Speed speed);
    UInt32 convert(OutputType type);
    UInt32 convert(PullUpDown pupd);
}


using namespace eos;
using namespace eos::hardware::gpio;
using namespace eos::hardware::gpio::internal;
using namespace eos::hardware::interrupts;


/// ----------------------------------------------------------------------
/// @brief    Inicialitza els pins com a entrades.
/// @param    gpio: Registres de hardware del GPIO.
/// @param    mask: Mascara dels pins a inicialitzar.
/// @param    pupd: Resistencies pull up/down.
///
void GPIOUtils::initInput(
    GPIO_TypeDef * const gpio,
    PinMask mask,
	PullUpDown pupd) {

    auto m = (UInt16) mask;
    for (auto b = 0; b < 16; b++) {
        if ((m & (1 << b)) != 0)
            initInput(gpio, PinBit(b), pupd);
    }
}


/// ----------------------------------------------------------------------
/// @brief    Inicialitza un pin com a entrada.
/// @param    gpio: Registres de hardware del GPIO.
/// @param    bit: El bit del pin a inicialitzar.
/// @param    Resistencies pull up/down.
///
void GPIOUtils::initInput(
	GPIO_TypeDef * const gpio,
	PinBit bit,
	PullUpDown pupd) {

	auto i = Irq::getInterruptState();
    Irq::disableInterrupts();

    auto b = (UInt8) bit;

    // Configura el pin com a entrada digital
    //
    auto MODER = gpio->MODER;
    Bits::clear(MODER, MODE::Mask << (b * 2));
    Bits::set(MODER, MODE::INPUT << (b * 2));
    gpio->MODER = MODER;

    // Configura les resistencies pull UP/DOWN
    //
    auto PUPDR = gpio->PUPDR;
    Bits::clear(PUPDR, PUPD::Mask << (b * 2));
    Bits::set(PUPDR, convert(pupd) << (b * 2));
    gpio->PUPDR = PUPDR;

    Irq::restoreInterrupts(i);
}


/// ----------------------------------------------------------------------
/// @brief    Inicialitza els pins com sortides.
/// @param    gpio: Els registres de hardware del GPIO.
/// @param    mask: Mascara dels pins a inicialitzar.
/// @param    type: Tipus de sortida.
/// @param    pupd: Resistencies pull up/down.
/// @param    speed: Velocitat de conmutacio.
///
void GPIOUtils::initOutput(
    GPIO_TypeDef * const gpio,
    PinMask mask,
    OutputType type,
	PullUpDown pupd,
    Speed speed) {

    auto m = (UInt16) mask;
    for (auto b = 0; b < 16; b++) {
        if ((m & (1 << b)) != 0)
            initOutput(gpio, PinBit(b), type, pupd, speed, false);
    }
}


/// ----------------------------------------------------------------------
/// @brief    Inicialitza un pin com sortida.
/// @param    gpio: Els registres de hardware del GPIO.
/// @param    bit: El bit del pin a inicialitzar.
/// @param    mode: Tipus de sortida.
/// @param    speed: Velocitat de conmutacio.
/// @param    state: L'estat inicial del pin.
///
void GPIOUtils::initOutput(
	GPIO_TypeDef * const gpio,
	PinBit bit,
	OutputType type,
	PullUpDown pupd,
	Speed speed,
	bool state) {

	auto i = Irq::getInterruptState();
    Irq::disableInterrupts();

    auto b = (UInt8) bit;

    // Configura el pin com sortida digital
    //
    auto MODER = gpio->MODER;
    Bits::clear(MODER, MODE::Mask << (b * 2));
    Bits::set(MODER, MODE::OUTPUT << (b * 2));
    gpio->MODER = MODER;

    // Configura el driver de sortida
    //
    auto OTYPER = gpio->OTYPER;
    Bits::clear(OTYPER, OTYPE::Mask << b);
    Bits::set(OTYPER, convert(type) << b);
    gpio->OTYPER = OTYPER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    Bits::clear(PUPDR, PUPD::Mask << (b * 2));
    Bits::set(PUPDR, convert(pupd) << (b * 2));
    gpio->PUPDR = PUPDR;

    // Configura la velocitat de conmutacio
    //
    auto OSPEEDR = gpio->OSPEEDR;
    Bits::clear(OSPEEDR, OSPEED::Mask << (b * 2));
    Bits::set(OSPEEDR, convert(speed) << (b * 2));
    gpio->OSPEEDR = OSPEEDR;

    // Configura l'estat de sortida
    //
    Bits::set(gpio->BSRR, 1UL << (b + (state ? 0 : 16)));

    Irq::restoreInterrupts(i);
}


/// ----------------------------------------------------------------------
/// @brief    Inicialitza un pin com i/o sortida alternatiu.
/// @param    gpio: Registres de hardware del GPIO.
/// @param    bit: El bit del pin a inicialitzar.
/// @param    type: Tipus de sortida.
/// @param    pupd: Resistencies pull UD/DN
/// @param    speed: Velocitat de conmutacio.
/// @param    af: La funcio alternativa.
///
void GPIOUtils::initAlternate(
    GPIO_TypeDef * const gpio,
    PinBit bit,
    OutputType type,
	PullUpDown pupd,
    Speed speed,
    AlternateFunction af) {

	auto i = Irq::getInterruptState();
    Irq::disableInterrupts();

    auto b = UInt8(bit);

    // Configura el pin com entrada/sortida alternativa
    //
    auto MODER = gpio->MODER;
    Bits::clear(MODER, MODE::Mask << (b * 2));
    Bits::set(MODER, MODE::ALTERNATE << (b * 2));
    gpio->MODER = MODER;

    // Configura el driver de sortida
    //
    auto OTYPER = gpio->OTYPER;
    Bits::clear(OTYPER, OTYPE::Mask << b);
    Bits::set(OTYPER, convert(type) << b);
    gpio->OTYPER = OTYPER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    Bits::clear(PUPDR, PUPD::Mask << (b * 2));
    Bits::set(PUPDR, convert(pupd) << (b * 2));
    gpio->PUPDR = PUPDR;

    // Configura la velocitat de conmutacio
    //
    auto OSPEEDR = gpio->OSPEEDR;
    Bits::clear(OSPEEDR, OSPEED::Mask << (b * 2));
    Bits::set(OSPEEDR, convert(speed) << (b * 2));
    gpio->OSPEEDR = OSPEEDR;

    // Selecciona la funcio alternativa
    //
    auto AFR = gpio->AFR[b >> 3];
    Bits::clear(AFR, AF::Mask << ((b & 0x07) * 4)) ;
    Bits::set(AFR, (((UInt32)af) & AF::Mask) << ((b & 0x07) * 4));
    gpio->AFR[b >> 3] = AFR;

    Irq::restoreInterrupts(i);
}


/// ----------------------------------------------------------------------
/// @brief    Inicialitza un pin entrada analogica
/// @param    gpio: Registres de hardware del GPIO.
/// @param    bit: Bit del pin a inicialitzar.
///
void GPIOUtils::initAnalogic(
	GPIO_TypeDef * const gpio,
	PinBit bit) {

	auto i = Irq::getInterruptState();
    Irq::disableInterrupts();

    auto b = UInt8(bit);

    // Configura el pin com entrada analogica
    //
    auto MODER = gpio->MODER;
    Bits::clear(MODER, MODE::Mask << (b * 2));
    Bits::set(MODER, MODE::ANALOGIC << (b * 2));
    gpio->MODER = MODER;

    Irq::restoreInterrupts(i);
}


/// ----------------------------------------------------------------------
/// @brief    Desinicialitza els pins. Els deixa en la seva configuracio
///           per defecte.
/// @param    gpio: Registres de hardware del GPIO.
/// @param    mask: Mascara dels pins a desinicialitzar.
///
void GPIOUtils::deinitialize(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

    auto m = (UInt16) mask;
    for (auto b = 0; b < 16; b++) {
        if ((m & (1 << b)) != 0)
            deinitialize(gpio, PinBit(b));
    }
}


/// ----------------------------------------------------------------------
/// @brief    Desinicialitza un pin. El deixa en la seva configuracio
///           per defecte.
/// @param    gpio: Registres de hardware del GPIO.
/// @param    bit: El bit del pin a desinicialitzar.
///
void GPIOUtils::deinitialize(
	GPIO_TypeDef * const gpio,
	PinBit bit) {

}


/// ----------------------------------------------------------------------
/// @brief    Converteix OutputType a UInt32
/// @param    mode: El valor a convertir.
/// @return   El resultat.
///
UInt32 eos::hardware::gpio::internal::convert(
	OutputType type) {

	return type == OutputType::pushPull ? OTYPE::PP : OTYPE::OD;
}


/// ----------------------------------------------------------------------
/// @brief    Converteix Speed a UInt32
/// @param    speed: El valor a convertir.
/// @return   El resultat.
///
UInt32 eos::hardware::gpio::internal::convert(
	Speed speed) {

    switch (speed) {
    	case Speed::low:
    	    return OSPEED::LOW;

    	case Speed::medium:
    	    return OSPEED::MEDIUM;

    	case Speed::high:
    	    return OSPEED::HIGH;

    	default:
    	    return OSPEED::FAST;
    }
}


/// ----------------------------------------------------------------------
/// @brief    Converteix el valor PullUp a UInt32
/// @param    pupd: El valor a convertir
/// @return   El resultat.
///
UInt32 eos::hardware::gpio::internal::convert(
	PullUpDown pupd)  {

	switch (pupd) {
		case PullUpDown::up:
			return PUPD::UP;

		case PullUpDown::down:
			return PUPD::DOWN;

		default:
			return PUPD::NONE;
	}
}
