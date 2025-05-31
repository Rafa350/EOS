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

	uint32_t getSpeedValue(Speed speed);
	uint32_t getOutputTypeValue(OutputMode mode);
	uint32_t getPullUpDownValue(InputMode mode);
	uint32_t getPullUpDownValue(OutputMode mode);
}


using namespace htl::bits;
using namespace htl::gpio;
using namespace htl::gpio::internal;

#if 0
/// ----------------------------------------------------------------------
/// \brief    Activa el modul
/// \param    gpio: Registres de hardware del GPIO.
///
#if defined(EOS_PLATFORM_STM32F4) || \
	defined(EOS_PLATFORM_STM32F7)
void htl::gpio::activate(
	GPIO_TypeDef * const gpio) {
	auto a = htl::startAtomic();

	switch ((uint32_t) gpio) {
#ifdef HTL_GPIOA_EXIST
		case GPIOA_BASE:
			set(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
			break;
#endif
#ifdef HTL_GPIOB_EXIST
		case GPIOB_BASE:
			set(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
			break;
#endif
#ifdef HTL_GPIOC_EXIST
		case GPIOC_BASE:
			set(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
			break;
#endif
#ifdef HTL_GPIOD_EXIST
		case GPIOD_BASE:
			set(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
			break;
#endif
#ifdef HTL_GPIOE_EXIST
		case GPIOE_BASE:
			set(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
			break;
#endif
#ifdef HTL_GPIOF_EXIST
		case GPIOF_BASE:
			bits::set(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);
			break;
#endif
#ifdef HTL_GPIOG_EXIST
		case GPIOG_BASE:
			bits::set(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
			break;
#endif
#ifdef HTL_GPIOH_EXIST
		case GPIOH_BASE:
			bits::set(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);
			break;
#endif
#ifdef HTL_GPIOI_EXIST
		case GPIOI_BASE:
			bits::set(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);
			break;
#endif
#ifdef HTL_GPIOJ_EXIST
		case GPIOJ_BASE:
			bits::set(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN);
			break;
#endif
#ifdef HTL_GPIOK_EXIST
		case GPIOK_BASE:
			bits::set(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN);
			break;
#endif
	}
	__DSB();

	htl::endAtomic(a);
}

#elif defined(EOS_PLATFORM_STM32G0)

void htl::gpio::activate(
	GPIO_TypeDef * const gpio) {

	auto a = htl::startAtomic();

	switch ((uint32_t) gpio) {
#ifdef HTL_GPIOA_EXIST
		case GPIOA_BASE:
			set(RCC->IOPENR, RCC_IOPENR_GPIOAEN);
			break;
#endif
#ifdef HTL_GPIOB_EXIST
		case GPIOB_BASE:
			set(RCC->IOPENR, RCC_IOPENR_GPIOBEN);
			break;
#endif
#ifdef HTL_GPIOC_EXIST
		case GPIOC_BASE:
			set(RCC->IOPENR, RCC_IOPENR_GPIOCEN);
			break;
#endif
#ifdef HTL_GPIOD_EXIST
		case GPIOD_BASE:
			set(RCC->IOPENR, RCC_IOPENR_GPIODEN);
			break;
#endif
#ifdef HTL_GPIOE_EXIST
		case GPIOE_BASE:
			set(RCC->IOPENR, RCC_IOPENR_GPIOEEN);
			break;
#endif
#ifdef HTL_GPIOF_EXIST
		case GPIOF_BASE:
			set(RCC->IOPENR, RCC_IOPENR_GPIOFEN);
			break;
#endif
	}
	__DSB();

	htl::endAtomic(a);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Desactiva el modul
/// \param    gpio: Registres de hardware del GPIO.
///
#if defined(EOS_PLATFORM_STM32F4) || \
	defined(EOS_PLATFORM_STM32F7)
void htl::gpio::deactivate(
	GPIO_TypeDef * const gpio) {

	auto a = htl::startAtomic();

	switch ((uint32_t) gpio) {
#ifdef HTL_GPIOA_EXIST
		case GPIOA_BASE:
			clear(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
			break;
#endif
#ifdef HTL_GPIOB_EXIST
		case GPIOB_BASE:
			clear(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
			break;
#endif
#ifdef HTL_GPIOC_EXIST
		case GPIOC_BASE:
			clear(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
			break;
#endif
#ifdef HTL_GPIOD_EXIST
		case GPIOD_BASE:
			clear(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
			break;
#endif
#ifdef HTL_GPIOE_EXIST
		case GPIOE_BASE:
			clear(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
			break;
#endif
#ifdef HTL_GPIOF_EXIST
		case GPIOF_BASE:
			clear(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);
			break;
#endif
#ifdef HTL_GPIOG_EXIST
		case GPIOG_BASE:
			clear(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
			break;
#endif
#ifdef HTL_GPIOH_EXIST
		case GPIOH_BASE:
			clear(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);
			break;
#endif
#ifdef HTL_GPIOI_EXIST
		case GPIOI_BASE:
			clear(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);
			break;
#endif
#ifdef HTL_GPIOJ_EXIST
		case GPIOJ_BASE:
			clear(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN);
			break;
#endif
#ifdef HTL_GPIOK_EXIST
		case GPIOK_BASE:
			clear(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN);
			break;
#endif
	}
	__DSB();

	htl::endAtomic(a);
}

#elif defined(EOS_PLATFORM_STM32G0)
void htl::gpio::deactivate(
	GPIO_TypeDef * const gpio) {

	auto a = htl::startAtomic();

	switch ((uint32_t) gpio) {
#ifdef HTL_GPIOA_EXIST
		case GPIOA_BASE:
			clear(RCC->IOPENR, RCC_IOPENR_GPIOAEN);
			break;
#endif
#ifdef HTL_GPIOB_EXIST
		case GPIOB_BASE:
			clear(RCC->IOPENR, RCC_IOPENR_GPIOBEN);
			break;
#endif
#ifdef HTL_GPIOC_EXIST
		case GPIOC_BASE:
			clear(RCC->IOPENR, RCC_IOPENR_GPIOCEN);
			break;
#endif
#ifdef HTL_GPIOD_EXIST
		case GPIOD_BASE:
			clear(RCC->IOPENR, RCC_IOPENR_GPIODEN);
			break;
#endif
#ifdef HTL_GPIOE_EXIST
		case GPIOE_BASE:
			clear(RCC->IOPENR, RCC_IOPENR_GPIOEEN);
			break;
#endif
#ifdef HTL_GPIOF_EXIST
		case GPIOF_BASE:
			clear(RCC->IOPENR, RCC_IOPENR_GPIOFEN);
			break;
#endif
	}
	__DSB();

	htl::endAtomic(a);
}
#endif
#endif


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
            initInput(gpio, mask, info->input.mode);
            break;

        case InitMode::output:
        	initOutput(gpio, mask, info->output.mode, info->output.speed, info->output.state);
            break;

        case InitMode::alternateInput:
        	initAlternateInput(gpio, mask, info->alternateInput.mode, info->alternateInput.function);
            break;

        case InitMode::alternateOutput:
        	initAlternateOutput(gpio, mask, info->alternateOutput.mode, info->alternateOutput.speed, info->alternateOutput.function);
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
/// \param    node: Tipus d'entrada.
///
void htl::gpio::initInput(
    GPIO_TypeDef * const gpio,
    PinMask mask,
    InputMode mode) {

    auto m = (uint16_t) mask;
    for (auto b = 0; b < 15; b++) {
        if ((m & (1 << b)) != 0)
            initInput(gpio, PinBit(b), mode);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com a entrada.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
/// \param    node: Tipus d'entrada.
///
void htl::gpio::initInput(
	GPIO_TypeDef * const gpio,
	PinBit bit,
	InputMode mode) {

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
    set(PUPDR, getPullUpDownValue(mode) << (b * 2));
    gpio->PUPDR = PUPDR;

    endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com sortides.
/// \param    gpio: Els registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a inicialitzar.
/// \param    mode: Tipus de sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    state: L'estat inicial del pin.
///
void htl::gpio::initOutput(
    GPIO_TypeDef * const gpio,
    PinMask mask,
    OutputMode mode,
    Speed speed,
    bool state) {

    auto m = (uint16_t) mask;
    for (auto b = 0; b < 15; b++) {
        if ((m & (1 << b)) != 0)
            initOutput(gpio, PinBit(b), mode, speed, state);
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
	OutputMode mode,
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
    set(OTYPER, getOutputTypeValue(mode) << b);
    gpio->OTYPER = OTYPER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    clear(PUPDR, PUPD::Mask << (b * 2));
    set(PUPDR, getPullUpDownValue(mode) << (b * 2));
    gpio->PUPDR = PUPDR;

    // Configura la velocitat de conmutacio
    //
    auto OSPEEDR = gpio->OSPEEDR;
    clear(OSPEEDR, OSPEED::Mask << (b * 2));
    set(OSPEEDR, getSpeedValue(speed) << (b * 2));
    gpio->OSPEEDR = OSPEEDR;

    // Configura l'estat de sortida
    //
    gpio->ODR = 1 << b;

    endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com entrades alternatives.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara del pins a inicialitzar.
/// \param    mode: Tipus d'entrada.
/// \param    af: La funcio alternativa.
///
void htl::gpio::initAlternateInput(
	GPIO_TypeDef * const gpio,
	PinMask mask,
	InputMode mode,
	AlternateFunction af) {

    auto m = uint16_t(mask);
	for (uint8_t b = 0; b < 15; b++) {
		if ((m & (1 << b)) != 0)
		    initAlternateInput(gpio, PinBit(b), mode, af);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com entradas alternativa.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
/// \param    mode: Tipus de entrada/sortida.
/// \param    af: La funcio alternativa.
///
void htl::gpio::initAlternateInput(
    GPIO_TypeDef * const gpio,
    PinBit bit,
    InputMode mode,
    AlternateFunction af) {

	auto a = startAtomic();

    auto b = uint8_t(bit);

    // Configura el pin com entrada/sortida alternativa
    //
    auto MODER = gpio->MODER;
    clear(MODER, MODE::Mask << (b * 2));
    set(MODER, MODE::ALTERNATE << (b * 2));
    gpio->MODER = MODER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    clear(PUPDR, PUPD::Mask << (b * 2));
    set(PUPDR, getPullUpDownValue(mode) << (b * 2));
    gpio->PUPDR = PUPDR;

    // Selecciona la funcio alternativa
    //
    auto AFR = gpio->AFR[b >> 3];
    clear(AFR, AF::Mask << ((b & 0x07) * 4)) ;
    set(AFR, (((uint32_t)af) & AF::Mask) << ((b & 0x07) * 4));
    gpio->AFR[b >> 3] = AFR;

    endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com sortides alternatives.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara del pins a inicialitzar.
/// \param    mode: Tipus de entrada/sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    af: La funcio alternativa.
///
void htl::gpio::initAlternateOutput(
	GPIO_TypeDef * const gpio,
	PinMask mask,
	OutputMode mode,
	Speed speed,
	AlternateFunction af) {

    auto m = uint16_t(mask);
	for (uint8_t b = 0; b < 15; b++) {
		if ((m & (1 << b)) != 0)
		    initAlternateOutput(gpio, PinBit(b), mode, speed, af);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com sortida alternativa.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
/// \param    mode: Tipus de entrada/sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    af: La funcio alternativa.
///
void htl::gpio::initAlternateOutput(
    GPIO_TypeDef * const gpio,
    PinBit bit,
    OutputMode mode,
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
    set(OTYPER, getOutputTypeValue(mode) << b);
    gpio->OTYPER = OTYPER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    clear(PUPDR, PUPD::Mask << (b * 2));
    set(PUPDR, getPullUpDownValue(mode) << (b * 2));
    gpio->PUPDR = PUPDR;

    // Configura la velocitat de conmutacio
    //
    auto OSPEEDR = gpio->OSPEEDR;
    clear(OSPEEDR, OSPEED::Mask << (b * 2));
    set(OSPEEDR, getSpeedValue(speed) << (b * 2));
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
/// \brief    Desinicialitza els pins. Els deixa en la seva configuracio
///           per defecte.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a desinicialitzar.
///
void htl::gpio::deinitialize(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

    auto m = (uint16_t) mask;
    for (uint8_t b = 0; b < 15; b++) {
        if ((m & (1 << b)) != 0)
            deinitialize(gpio, PinMask(1 << b));
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
/// \brief    Obte el valor del tipus de sortida
/// \param    mode: El tipus de sortida.
/// \return   El resultat.
///
uint32_t htl::gpio::internal::getOutputTypeValue(
	htl::gpio::OutputMode mode) {

	return mode == OutputMode::pushPull ? OTYPE::PP : OTYPE::OD;
}



/// ----------------------------------------------------------------------
/// \brief    Obte el valor de la velocitat
/// \param    speed: La velocitat.
/// \return   El resultat.
///
uint32_t htl::gpio::internal::getSpeedValue(
	htl::gpio::Speed speed) {

    switch (speed) {
    	default:
    	case Speed::low:
    	    return OSPEED::LOW;

    	case Speed::medium:
    	    return OSPEED::MEDIUM;

    	case Speed::high:
    	    return OSPEED::HIGH;

    	case Speed::fast:
    	    return OSPEED::FAST;
    }
}


uint32_t htl::gpio::internal::getPullUpDownValue(
	htl::gpio::InputMode mode)  {

	switch (mode) {
		case InputMode::pullUp:
			return PUPD::UP;

		case InputMode::pullDown:
			return PUPD::DOWN;

		default:
			return PUPD::NONE;
	}
}


uint32_t htl::gpio::internal::getPullUpDownValue(
	htl::gpio::OutputMode mode) {

	return mode == OutputMode::openDrainPullUp ? PUPD::UP : PUPD::NONE;
}
