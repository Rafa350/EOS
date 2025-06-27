#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/htlAtomic.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl::gpio::internal {

	struct MODE {
		static constexpr uint32_t Mask      = 0b11;
		static constexpr uint32_t INPUT     = 0b00;
		static constexpr uint32_t OUTPUT    = 0b01;
		static constexpr uint32_t ALTERNATE = 0b10;
		static constexpr uint32_t ANALOGIC  = 0b11;
	};

	struct PUPD {
		static constexpr uint32_t Mask = 0b11;
		static constexpr uint32_t NONE = 0b00;
		static constexpr uint32_t UP   = 0b01;
		static constexpr uint32_t DOWN = 0b10;
	};

	struct OTYPE {
		static constexpr uint32_t Mask = 0b1;
		static constexpr uint32_t PP   = 0b0;
		static constexpr uint32_t OD   = 0b1;
	};

	struct OSPEED {
		static constexpr uint32_t Mask   = 0b11;
		static constexpr uint32_t LOW    = 0b00;
		static constexpr uint32_t MEDIUM = 0b01;
		static constexpr uint32_t HIGH   = 0b10;
		static constexpr uint32_t FAST   = 0b11;
	};

	struct AF {
		static constexpr uint32_t Mask = 0b1111;
	};

	uint32_t convert(Speed speed);
	uint32_t convert(OutputType type);
	uint32_t convert(PullUpDown pupd);
}


using namespace htl::bits;
using namespace htl::gpio;
using namespace htl::gpio::internal;


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mack: mascara de pins
/// \param    info: Informacio per la inicialitzacio.
///
void htl::gpio::initialize(
    GPIO_TypeDef * const gpio,
	PinMask mask,
    const InitInfo *info) {

    switch(info->mode) {
        case InitMode::input:
            initInput(gpio, mask, info->input.pupd);
            break;

        case InitMode::output:
        	initOutput(gpio, mask, info->output.type, info->output.pupd,
        		info->output.speed, info->output.state);
            break;

        case InitMode::alternate:
        	initAlternate(gpio, mask, info->alternate.type, info->alternate.pupd,
        		info->alternate.speed, info->alternate.function);
            break;

        case InitMode::analogic:
        	initAnalogic(gpio, mask);
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com a entrades.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a inicialitzar.
/// \param    pupd: Resistencies pull up/down.
///
void htl::gpio::initInput(
    GPIO_TypeDef * const gpio,
    PinMask mask,
	PullUpDown pupd) {

    auto m = (uint16_t) mask;
    for (auto b = 0; b < 16; b++) {
        if ((m & (1 << b)) != 0)
            initInput(gpio, PinBit(b), pupd);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com a entrada.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
/// \param    Resistencies pull up/down.
///
void htl::gpio::initInput(
	GPIO_TypeDef * const gpio,
	PinBit bit,
	PullUpDown pupd) {

	auto a = startAtomic();

    auto b = (uint8_t) bit;

    // Configura el pin com a entrada digital
    //
    auto MODER = gpio->MODER;
    clear(MODER, MODE::Mask << (b * 2));
    set(MODER, MODE::INPUT << (b * 2));
    gpio->MODER = MODER;

    // Configura les resistencies pull UP/DOWN
    //
    auto PUPDR = gpio->PUPDR;
    clear(PUPDR, PUPD::Mask << (b * 2));
    set(PUPDR, convert(pupd) << (b * 2));
    gpio->PUPDR = PUPDR;

    endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com sortides.
/// \param    gpio: Els registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a inicialitzar.
/// \param    type: Tipus de sortida.
/// \param    pupd: Resistencies pull up/down.
/// \param    speed: Velocitat de conmutacio.
/// \param    state: L'estat inicial del pin.
///
void htl::gpio::initOutput(
    GPIO_TypeDef * const gpio,
    PinMask mask,
    OutputType type,
	PullUpDown pupd,
    Speed speed,
    bool state) {

    auto m = (uint16_t) mask;
    for (auto b = 0; b < 16; b++) {
        if ((m & (1 << b)) != 0)
            initOutput(gpio, PinBit(b), type, pupd, speed, state);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com sortida.
/// \param    gpio: Els registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
/// \param    mode: Tipus de sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    state: L'estat inicial del pin.
///
void htl::gpio::initOutput(
	GPIO_TypeDef * const gpio,
	PinBit bit,
	OutputType type,
	PullUpDown pupd,
	Speed speed,
	bool state) {

	auto a = startAtomic();

    auto b = (uint8_t) bit;

    // Configura el pin com sortida digital
    //
    auto MODER = gpio->MODER;
    clear(MODER, MODE::Mask << (b * 2));
    set(MODER, MODE::OUTPUT << (b * 2));
    gpio->MODER = MODER;

    // Configura el driver de sortida
    //
    auto OTYPER = gpio->OTYPER;
    clear(OTYPER, OTYPE::Mask << b);
    set(OTYPER, convert(type) << b);
    gpio->OTYPER = OTYPER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    clear(PUPDR, PUPD::Mask << (b * 2));
    set(PUPDR, convert(pupd) << (b * 2));
    gpio->PUPDR = PUPDR;

    // Configura la velocitat de conmutacio
    //
    auto OSPEEDR = gpio->OSPEEDR;
    clear(OSPEEDR, OSPEED::Mask << (b * 2));
    set(OSPEEDR, convert(speed) << (b * 2));
    gpio->OSPEEDR = OSPEEDR;

    // Configura l'estat de sortida
    //
   	set(gpio->BSRR, 1UL << (b + (state ? 0 : 16)));

    endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com i/o alternatiu.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara del pins a inicialitzar.
/// \param    type: Tipus de entrada/sortida.
/// \param    pupd: Resistencies pull UD/DN
/// \param    speed: Velocitat de conmutacio.
/// \param    af: La funcio alternativa.
///
void htl::gpio::initAlternate(
	GPIO_TypeDef * const gpio,
	PinMask mask,
	OutputType type,
	PullUpDown pupd,
	Speed speed,
	AlternateFunction af) {

    auto m = (uint16_t) mask;
	for (auto b = 0; b < 16; b++) {
		if ((m & (1 << b)) != 0)
		    initAlternate(gpio, PinBit(b), type, pupd, speed, af);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com i/o sortida alternatiu.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
/// \param    type: Tipus de sortida.
/// \param    pupd: Resistencies pull UD/DN
/// \param    speed: Velocitat de conmutacio.
/// \param    af: La funcio alternativa.
///
void htl::gpio::initAlternate(
    GPIO_TypeDef * const gpio,
    PinBit bit,
    OutputType type,
	PullUpDown pupd,
    Speed speed,
    AlternateFunction af) {

	auto a = startAtomic();

    auto b = uint8_t(bit);

    // Configura el pin com entrada/sortida alternativa
    //
    auto MODER = gpio->MODER;
    clear(MODER, MODE::Mask << (b * 2));
    set(MODER, MODE::ALTERNATE << (b * 2));
    gpio->MODER = MODER;

    // Configura el driver de sortida
    //
    auto OTYPER = gpio->OTYPER;
    clear(OTYPER, OTYPE::Mask << b);
    set(OTYPER, convert(type) << b);
    gpio->OTYPER = OTYPER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    clear(PUPDR, PUPD::Mask << (b * 2));
    set(PUPDR, convert(pupd) << (b * 2));
    gpio->PUPDR = PUPDR;

    // Configura la velocitat de conmutacio
    //
    auto OSPEEDR = gpio->OSPEEDR;
    clear(OSPEEDR, OSPEED::Mask << (b * 2));
    set(OSPEEDR, convert(speed) << (b * 2));
    gpio->OSPEEDR = OSPEEDR;

    // Selecciona la funcio alternativa
    //
    auto AFR = gpio->AFR[b >> 3];
    clear(AFR, AF::Mask << ((b & 0x07) * 4)) ;
    set(AFR, (((uint32_t)af) & AF::Mask) << ((b & 0x07) * 4));
    gpio->AFR[b >> 3] = AFR;

    endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin entrada analogica
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a inicialitzar.
///
void htl::gpio::initAnalogic(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

    auto m = (uint16_t) mask;
	for (auto b = 0; b < 16; b++) {
		if ((m & (1 << b)) != 0)
		    initAnalogic(gpio, PinBit(b));
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin entrada analogica
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: Bit del pin a inicialitzar.
///
void htl::gpio::initAnalogic(
	GPIO_TypeDef * const gpio,
	PinBit bit) {

    auto b = uint8_t(bit);

    auto a = startAtomic();

    // Configura el pin com entrada analogica
    //
    auto MODER = gpio->MODER;
    clear(MODER, MODE::Mask << (b * 2));
    set(MODER, MODE::ANALOGIC << (b * 2));
    gpio->MODER = MODER;

    endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza els pins. Els deixa en la seva configuracio
///           per defecte.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a desinicialitzar.
///
void htl::gpio::deinitialize(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

    auto m = (uint16_t) mask;
    for (auto b = 0; b < 16; b++) {
        if ((m & (1 << b)) != 0)
            deinitialize(gpio, PinBit(b));
    }
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza un pin. El deixa en la seva configuracio
///           per defecte.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a desinicialitzar.
///
void htl::gpio::deinitialize(
	GPIO_TypeDef * const gpio,
	PinBit bit) {

}


/// ----------------------------------------------------------------------
/// \brief    Converteix OutputType a uint32_t
/// \param    mode: El valor a convertir.
/// \return   El resultat.
///
uint32_t htl::gpio::internal::convert(
	htl::gpio::OutputType type) {

	return type == OutputType::pushPull ? OTYPE::PP : OTYPE::OD;
}


/// ----------------------------------------------------------------------
/// \brief    Converteix Speed a uint32_t
/// \param    speed: El valor a convertir.
/// \return   El resultat.
///
uint32_t htl::gpio::internal::convert(
	htl::gpio::Speed speed) {

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
/// \brief    Converteix el valor PullUp a uint32_t
/// \param    pupd: El valor a convertir
/// \return   El resultat.
///
uint32_t htl::gpio::internal::convert(
	htl::gpio::PullUpDown pupd)  {

	switch (pupd) {
		case PullUpDown::up:
			return PUPD::UP;

		case PullUpDown::down:
			return PUPD::DOWN;

		default:
			return PUPD::NONE;
	}
}
