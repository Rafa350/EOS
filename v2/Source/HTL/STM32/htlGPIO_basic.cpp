#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/htlAtomic.h"
#include "HTL/STM32/htlGPIO.h"


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


#ifdef HTL_GPIOA_EXIST
static uint16_t __activeA = 0; // Control de l'activacio del modul GPIOA
#endif
#ifdef HTL_GPIOB_EXIST
static uint16_t __activeB = 0; // Control de l'activacio del modul GPIOB
#endif
#ifdef HTL_GPIOC_EXIST
static uint16_t __activeC = 0; // Control de l'activacio del modul GPIOC
#endif
#ifdef HTL_GPIOD_EXIST
static uint16_t __activeD = 0; // Control de l'activacio del modul GPIOD
#endif
#ifdef HTL_GPIOE_EXIST
static uint16_t __activeE = 0; // Control de l'activacio del modul GPIOE
#endif
#ifdef HTL_GPIOF_EXIST
static uint16_t __activeF = 0; // Control de l'activacio del modul GPIOF
#endif
#ifdef HTL_GPIOG_EXIST
static uint16_t __activeG = 0; // Control de l'activacio del modul GPIOG
#endif
#ifdef HTL_GPIOH_EXIST
static uint16_t __activeH = 0; // Control de l'activacio del modul GPIOH
#endif
#ifdef HTL_GPIOI_EXIST
static uint16_t __activeI = 0; // Control de l'activacio del modul GPIOI
#endif
#ifdef HTL_GPIOJ_EXIST
static uint16_t __activeJ = 0; // Control de l'activacio del modul GPIOJ
#endif
#ifdef HTL_GPIOK_EXIST
static uint16_t __activeK = 0; // Control de l'activacio del modul GPIOK
#endif


static uint32_t getSpeedValue(htl::gpio::Speed speed);
static uint32_t getOutputTypeValue(htl::gpio::OutputMode mode);
static uint32_t getPullUpDownValue(htl::gpio::InputMode mode);
static uint32_t getPullUpDownValue(htl::gpio::OutputMode mode);

static void portClockEnable(uint16_t &activeX, volatile uint32_t& r, uint32_t b, htl::gpio::PinMask mask);
static void portClockDisable(uint16_t &activeX, volatile uint32_t& r, uint32_t b, htl::gpio::PinMask mask);


/// ----------------------------------------------------------------------
/// \brief    Activa el modul
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins per activar.
///
#if defined(EOS_PLATFORM_STM32F7)
void htl::gpio::activate(
	GPIO_TypeDef * const gpio,
	PinMask mask) {
	auto a = htl::startAtomic();

	switch ((uint32_t) gpio) {
#ifdef HTL_GPIOA_EXIST
		case GPIOA_BASE:
			portClockEnable(__activeA, RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN, mask);
			break;
#endif
#ifdef HTL_GPIOB_EXIST
		case GPIOB_BASE:
			portClockEnable(__activeB, RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN, mask);
			break;
#endif
#ifdef HTL_GPIOC_EXIST
		case GPIOC_BASE:
			portClockEnable(__activeC, RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN, mask);
			break;
#endif

#ifdef HTL_GPIOD_EXIST
		case GPIOD_BASE:
			portClockEnable(__activeD, RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN, mask);
			break;
#endif
#ifdef HTL_GPIOE_EXIST
		case GPIOE_BASE:
			portClockEnable(__activeE, RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN, mask);
			break;
#endif
#ifdef HTL_GPIOF_EXIST
		case GPIOF_BASE:
			portClockEnable(__activeF, RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN, mask);
			break;
#endif
#ifdef HTL_GPIOG_EXIST
		case GPIOG_BASE:
			portClockEnable(__activeG, RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN, mask);
			break;
#endif
#ifdef HTL_GPIOH_EXIST
		case GPIOH_BASE:
			portClockEnable(__activeH, RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN, mask);
			break;
#endif
#ifdef HTL_GPIOI_EXIST
		case GPIOI_BASE:
			portClockEnable(__activeI, RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN, mask);
			break;
#endif
#ifdef HTL_GPIOJ_EXIST
		case GPIOJ_BASE:
			portClockEnable(__activeJ, RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN, mask);
			break;
#endif
#ifdef HTL_GPIOK_EXIST
		case GPIOK_BASE:
			portClockEnable(__activeK, RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN, mask);
			break;
#endif
	}
	__DSB();

	htl::endAtomic(a);
}

#elif defined(EOS_PLATFORM_STM32G0)

void htl::gpio::activate(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

	auto a = htl::startAtomic();

	switch ((uint32_t) gpio) {
#ifdef HTL_GPIOA_EXIST
		case GPIOA_BASE:
			portClockEnable(__activeA, RCC->IOPENR, RCC_IOPENR_GPIOAEN, mask);
			break;
#endif
#ifdef HTL_GPIOB_EXIST
		case GPIOB_BASE:
			portClockEnable(__activeB, RCC->IOPENR, RCC_IOPENR_GPIOBEN, mask);
			break;
#endif
#ifdef HTL_GPIOC_EXIST
		case GPIOC_BASE:
			portClockEnable(__activeC, RCC->IOPENR, RCC_IOPENR_GPIOCEN, mask);
			break;
#endif
#ifdef HTL_GPIOD_EXIST
		case GPIOD_BASE:
			portClockEnable(__activeD, RCC->IOPENR, RCC_IOPENR_GPIODEN, mask);
			break;
#endif
#ifdef HTL_GPIOE_EXIST
		case GPIOE_BASE:
			portClockEnable(__activeE, RCC->IOPENR, RCC_IOPENR_GPIOEEN, mask);
			break;
#endif
#ifdef HTL_GPIOF_EXIST
		case GPIOF_BASE:
			portClockEnable(__activeF, RCC->IOPENR, RCC_IOPENR_GPIOFEN, mask);
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
/// \param    mask: Mascara dels pins per activar.
///
#if defined(EOS_PLATFORM_STM32F7)
void htl::gpio::deactivate(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

	auto a = htl::startAtomic();

	switch ((uint32_t) gpio) {
#ifdef HTL_GPIOA_EXIST
		case GPIOA_BASE:
			portClockDisable(__activeA, RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN, mask);
			break;
#endif
#ifdef HTL_GPIOB_EXIST
		case GPIOB_BASE:
			portClockDisable(__activeB, RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN, mask);
			break;
#endif
#ifdef HTL_GPIOC_EXIST
		case GPIOC_BASE:
			portClockDisable(__activeC, RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN, mask);
			break;
#endif
#ifdef HTL_GPIOD_EXIST
		case GPIOD_BASE:
			portClockDisable(__activeD, RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN, mask);
			break;
#endif
#ifdef HTL_GPIOE_EXIST
		case GPIOE_BASE:
			portClockDisable(__activeE, RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN, mask);
			break;
#endif
#ifdef HTL_GPIOF_EXIST
		case GPIOF_BASE:
			portClockDisable(__activeF, RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN, mask);
			break;
#endif
#ifdef HTL_GPIOG_EXIST
		case GPIOG_BASE:
			portClockDisable(__activeG, RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN, mask);
			break;
#endif
#ifdef HTL_GPIOH_EXIST
		case GPIOH_BASE:
			portClockDisable(__activeH, RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN, mask);
			break;
#endif
#ifdef HTL_GPIOI_EXIST
		case GPIOI_BASE:
			portClockDisable(__activeI, RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN, mask);
			break;
#endif
#ifdef HTL_GPIOJ_EXIST
		case GPIOJ_BASE:
			portClockDisable(__activeJ, RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN, mask);
			break;
#endif
#ifdef HTL_GPIOK_EXIST
		case GPIOK_BASE:
			portClockDisable(__activeK, RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN, mask);
			break;
#endif
	}
	__DSB();

	htl::endAtomic(a);
}

#elif defined(EOS_PLATFORM_STM32G0)
void htl::gpio::deactivate(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

	auto a = htl::startAtomic();

	switch ((uint32_t) gpio) {
#ifdef HTL_GPIOA_EXIST
		case GPIOA_BASE:
			portClockDisable(__activeA, RCC->IOPENR, RCC_IOPENR_GPIOAEN, mask);
			break;
#endif
#ifdef HTL_GPIOB_EXIST
		case GPIOB_BASE:
			portClockDisable(__activeB, RCC->IOPENR, RCC_IOPENR_GPIOBEN, mask);
			break;
#endif
#ifdef HTL_GPIOC_EXIST
		case GPIOC_BASE:
			portClockDisable(__activeC, RCC->IOPENR, RCC_IOPENR_GPIOCEN, mask);
			break;
#endif

#ifdef HTL_GPIOD_EXIST
		case GPIOD_BASE:
			portClockDisable(__activeD, RCC->IOPENR, RCC_IOPENR_GPIODEN, mask);
			break;
#endif
#ifdef HTL_GPIOE_EXIST
		case GPIOE_BASE:
			portClockDisable(__activeE, RCC->IOPENR, RCC_IOPENR_GPIOEEN, mask);
			break;
#endif
#ifdef HTL_GPIOF_EXIST
		case GPIOF_BASE:
			portClockDisable(__activeF, RCC->IOPENR, RCC_IOPENR_GPIOFEN, mask);
			break;
#endif
	}
	__DSB();

	htl::endAtomic(a);
}
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

	activate(gpio, PinMask(bit));

	auto a = startAtomic();

    auto b = (uint8_t) bit;

    // Configura el pin com a entrada digital
    //
    auto MODER = gpio->MODER;
    htl::bits::clear(MODER, MODE::Mask << (b * 2));
    htl::bits::set(MODER, MODE::INPUT << (b * 2));
    gpio->MODER = MODER;

    // Configura les resistencies pull UP/DOWN
    //
    auto PUPDR = gpio->PUPDR;
    htl::bits::clear(PUPDR, PUPD::Mask << (b * 2));
    htl::bits::set(PUPDR, getPullUpDownValue(mode) << (b * 2));
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

	activate(gpio, PinMask(bit));

	auto a = startAtomic();

    auto b = (uint8_t) bit;

    // Configura el pin com sortida digital
    //
    auto MODER = gpio->MODER;
    htl::bits::clear(MODER, MODE::Mask << (b * 2));
    htl::bits::set(MODER, MODE::OUTPUT << (b * 2));
    gpio->MODER = MODER;

    // Configura el driver de sortida
    //
    auto OTYPER = gpio->OTYPER;
    htl::bits::clear(OTYPER, OTYPE::Mask << b);
    htl::bits::set(OTYPER, getOutputTypeValue(mode) << b);
    gpio->OTYPER = OTYPER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    htl::bits::clear(PUPDR, PUPD::Mask << (b * 2));
    htl::bits::set(PUPDR, getPullUpDownValue(mode) << (b * 2));
    gpio->PUPDR = PUPDR;

    // Configura la velocitat de conmutacio
    //
    auto OSPEEDR = gpio->OSPEEDR;
    htl::bits::clear(OSPEEDR, OSPEED::Mask << (b * 2));
    htl::bits::set(OSPEEDR, getSpeedValue(speed) << (b * 2));
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

	activate(gpio, PinMask(bit));

	auto a = startAtomic();

    auto b = uint8_t(bit);

    // Configura el pin com entrada/sortida alternativa
    //
    auto MODER = gpio->MODER;
    htl::bits::clear(MODER, MODE::Mask << (b * 2));
    htl::bits::set(MODER, MODE::ALTERNATE << (b * 2));
    gpio->MODER = MODER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    htl::bits::clear(PUPDR, PUPD::Mask << (b * 2));
    htl::bits::set(PUPDR, getPullUpDownValue(mode) << (b * 2));
    gpio->PUPDR = PUPDR;

    // Selecciona la funcio alternativa
    //
    auto AFR = gpio->AFR[b >> 3];
    htl::bits::clear(AFR, AF::Mask << ((b & 0x07) * 4)) ;
    htl::bits::set(AFR, (((uint32_t)af) & AF::Mask) << ((b & 0x07) * 4));
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

	activate(gpio, PinMask(bit));

	auto a = startAtomic();

    auto b = uint8_t(bit);

    // Configura el pin com entrada/sortida alternativa
    //
    auto MODER = gpio->MODER;
    htl::bits::clear(MODER, MODE::Mask << (b * 2));
    htl::bits::set(MODER, MODE::ALTERNATE << (b * 2));
    gpio->MODER = MODER;

    // Configura el driver de sortida
    //
    auto OTYPER = gpio->OTYPER;
    htl::bits::clear(OTYPER, OTYPE::Mask << b);
    htl::bits::set(OTYPER, getOutputTypeValue(mode) << b);
    gpio->OTYPER = OTYPER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    htl::bits::clear(PUPDR, PUPD::Mask << (b * 2));
    htl::bits::set(PUPDR, getPullUpDownValue(mode) << (b * 2));
    gpio->PUPDR = PUPDR;

    // Configura la velocitat de conmutacio
    //
    auto OSPEEDR = gpio->OSPEEDR;
    htl::bits::clear(OSPEEDR, OSPEED::Mask << (b * 2));
    htl::bits::set(OSPEEDR, getSpeedValue(speed) << (b * 2));
    gpio->OSPEEDR = OSPEEDR;

    // Selecciona la funcio alternativa
    //
    auto AFR = gpio->AFR[b >> 3];
    htl::bits::clear(AFR, AF::Mask << ((b & 0x07) * 4)) ;
    htl::bits::set(AFR, (((uint32_t)af) & AF::Mask) << ((b & 0x07) * 4));
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

	deactivate(gpio, PinMask(bit));
}


void htl::gpio::pinSet(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

    gpio->BSRR = mask;
}


void htl::gpio::pinSet(
	GPIO_TypeDef * const gpio,
	PinBit bit) {

    gpio->BSRR = 1 << bit;
}


void htl::gpio::pinClear(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

    gpio->BSRR = mask << 16;
}


void htl::gpio::pinClear(
	GPIO_TypeDef * const gpio,
	PinBit bit) {

    gpio->BSRR = 1 << (bit + 16);
}


void htl::gpio::pinToggle(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

	auto odr = gpio->ODR;
	gpio->BSRR = ((odr & mask) << 16) | (~odr & mask);
}


void htl::gpio::pinToggle(
	GPIO_TypeDef * const gpio,
	PinBit bit) {

	auto odr = gpio->ODR;
	auto mask = 1 << bit;
	gpio->BSRR = ((odr & mask) << 16) | (~odr & mask);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del tipus de sortida
/// \param    mode: El tipus de sortida.
/// \return   El resultat.
///
static uint32_t getOutputTypeValue(
	htl::gpio::OutputMode mode) {

	return mode == htl::gpio::OutputMode::pushPull ? OTYPE::PP : OTYPE::OD;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor de la velocitat
/// \param    speed: La velocitat.
/// \return   El resultat.
///
static uint32_t getSpeedValue(
	htl::gpio::Speed speed) {

    switch (speed) {
    	default:
    	case htl::gpio::Speed::low:
    	    return OSPEED::LOW;

    	case htl::gpio::Speed::medium:
    	    return OSPEED::MEDIUM;

    	case htl::gpio::Speed::high:
    	    return OSPEED::HIGH;

    	case htl::gpio::Speed::fast:
    	    return OSPEED::FAST;
    }
}


static uint32_t getPullUpDownValue(
	htl::gpio::InputMode mode)  {

	switch (mode) {
		case htl::gpio::InputMode::pullUp:
			return PUPD::UP;

		case htl::gpio::InputMode::pullDown:
			return PUPD::DOWN;

		default:
			return PUPD::NONE;
	}
}


static uint32_t getPullUpDownValue(
	htl::gpio::OutputMode mode) {

	return mode == htl::gpio::OutputMode::openDrainPullUp ? PUPD::UP : PUPD::NONE;
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona l'activacio del modul GPIO
/// \param    activeX: Variable que contr els flags d'activacio
/// \param    r: Registre d'activacio (RCC->xxxxx)
/// \param    b: Bit del registre d'activacio.
/// \param    mask: Mascara dels pins a activar.
///
static void portClockEnable(
	uint16_t &activeX,
	volatile uint32_t& r,
	uint32_t b,
	htl::gpio::PinMask mask) {

	htl::bits::set(activeX, (typeof(activeX)) mask);
	if ((activeX != 0) && !htl::bits::isSet(r, b))
		htl::bits::set(r, b);
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona la desactivacio del modul GPIO
/// \param    activeX: Variable que contr els flags d'activacio
/// \param    r: Registre d'activacio (RCC->xxxxx)
/// \param    b: Bit del registre d'activacio.
/// \param    mask: Mascara dels pins a desactivar.
///
static void portClockDisable(
	uint16_t &activeX,
	volatile uint32_t& r,
	uint32_t b,
	htl::gpio::PinMask mask) {

	htl::bits::clear(activeX, (typeof(activeX)) mask);
	if ((activeX == 0) && htl::bits::isSet(r, b))
		htl::bits::clear(r, b);
}
