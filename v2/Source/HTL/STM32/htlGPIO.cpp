#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/htlAtomic.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;
using namespace htl::gpio;


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


static const uint32_t __speedTbl[] = {
    OSPEED::LOW,
    OSPEED::MEDIUM,
    OSPEED::HIGH,
    OSPEED::FAST};


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres hardware del modul GPIO.
///
PortDevice::PortDevice(
	GPIO_TypeDef *gpio):

	_gpio {gpio} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com entrades.
/// \param    mask: Mascara de pins a configurar.
/// \param    mode: Tipus d'entrada.
///
void PortDevice::initInput(
	PinMask mask,
	InputMode mode) const {

	activate(mask);
	internal::initInput(_gpio, mask, mode);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com sortides.
/// \param    mask: Mascara de pins a configurar.
/// \param    mode: El tipus de sortida.
/// \param    speed: Opcions de velocitat.
///
void PortDevice::initOutput(
	PinMask mask,
	OutputMode mode,
	Speed speed) const {

	activate(mask);
	internal::initOutput(_gpio, mask, mode, speed, false);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
///
void PortDevice::deinitialize() const {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres de hardware
/// \param    bit: El bit del pin.
///
PinDevice::PinDevice(
    GPIO_TypeDef *gpio,
    PinBit bit) :

    _gpio {gpio},
    _mask {bit} {


}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    info: Parametres d'inicialitzacio.
///
void PinDevice::initialize(
    const InitInfo &info) const {

    internal::initialize(_gpio, _mask, &info);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin en modun entrada digital.
/// \param    mode: El tipus d'entrada.
///
void PinDevice::initInput(
	InputMode mode) const {

	internal::initInput(_gpio, _mask, mode);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin en modus soirtida digital.
/// \parAM    mode: El tipus de sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    state: L'estat inicial de la sortida.
///
void PinDevice::initOutput(
	OutputMode mode,
	Speed speed,
	bool state) const {

	internal::initOutput(_gpio, _mask, mode, speed, state);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin en modus alternatiu.
/// \param    mode: El tipus de entrada/sortida
/// \param    speed: Velocitat de conmutacio.
/// \param    af: Funcio alternativa.
///
void PinDevice::initAlternate(
	AlternateMode mode,
	Speed speed,
	AlternateFunction af) const {

	internal::initAlternate(_gpio, _mask, mode, speed, af);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com a entrada/sortida analogica.
///
void PinDevice::initAnalogic() const {

	internal::initAnalogic(_gpio, _mask);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el pin i el deixa als valor per defecte.
///
void PinDevice::deinitialize() const {

	internal::deinitialize(_gpio, _mask);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres de hardware del modul GPIO.
/// \param    pinID: Identificador del pin.
///
PinInterrupt::PinInterrupt(
	GPIO_TypeDef *gpio,
	PinID pinID) :

	_portNum {uint8_t((uint32_t(gpio) >> 10) & 0x000F)},
	_pinNum {uint8_t(pinID)},
	_notifyEvent {nullptr},
	_notifyEventEnabled {false} {

}


/// ----------------------------------------------------------------------
/// \brief    Habilita la interrupcio.
/// \param    edge: El flanc que genera la interrupcio.
/// \remarks  Hi han limitavcions en funcio del hardware.
///
void PinInterrupt::enableInterruptPin(
	Edge edge) const {

	#if defined(EOS_PLATFORM_STM32F0) || \
	    defined(EOS_PLATFORM_STM32F4) || \
	    defined(EOS_PLATFORM_STM32F7)

	if ((RCC->APB2ENR & RCC_APB2ENR_SYSCFGEN) == 0) {
		RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
		__DSB();
	}

	uint32_t tmp = SYSCFG->EXTICR[_pinNum >> 2];
	tmp &= ~(((uint32_t)0x0F) << (4 * (_pinNum & 0x03)));
	tmp |= (_portNum << (4 * (_pinNum & 0x03)));
	SYSCFG->EXTICR[_pinNum >> 2] = tmp;

	uint32_t mask = 1 << _pinNum;

	// Configura en modus interrupcio
	//
	EXTI->IMR |= mask;
	EXTI->EMR &= ~mask;

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((edge == Edge::rising) || (edge == Edge::all))
		EXTI->RTSR |= mask;
	else
		EXTI->RTSR &= ~mask;

	// Configura el registre FTSR1 (Falling Trigger Selection Register)
	//
	if ((edge == Edge::falling) || (edge == Edge::all))
		EXTI->FTSR |= mask;
	else
		EXTI->FTSR &= ~mask;


	#elif defined(EOS_PLATFORM_STM32G0)

	/// Asigna el port GPIO a la linia EXTI
	//
	uint32_t tmp = EXTI->EXTICR[_pinNum >> 2u];
	tmp &= ~(EXTI_EXTICR1_EXTI0 << (EXTI_EXTICR1_EXTI1_Pos * (_pinNum & 0x03u)));
	tmp |= (_portNum << (EXTI_EXTICR1_EXTI1_Pos * (_pinNum & 0x03u)));
	EXTI->EXTICR[_pinNum >> 2u] = tmp;

	// Obte la mascara del pin
	//
	uint32_t mask = 1 << _pinNum;

	// Configura en modus interrupcio
	//
	EXTI->IMR1 |= mask;
	EXTI->EMR1 &= ~mask;

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((edge == Edge::rising) || (edge == Edge::all))
		EXTI->RTSR1 |= mask;
	else
		EXTI->RTSR1 &= ~mask;

	// Configura el registre FTSR1 (Falling Trigger Selection Register)
	//
	if ((edge == Edge::falling) || (edge == Edge::all))
		EXTI->FTSR1 |= mask;
	else
		EXTI->FTSR1 &= ~mask;

	#else
		#error "Unknown platform"
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita la interrupcio del pin.
///
void PinInterrupt::disableInterruptPin() const {

	#if defined(EOS_PLATFORM_STM32F0) || \
	    defined(EOS_PLATFORM_STM32F4) || \
	    defined(EOS_PLATFORM_STM32F7)

	uint32_t mask = 1 << _pinNum;
	EXTI->RTSR &= ~mask;
	EXTI->FTSR &= ~mask;

	#elif defined(EOS_PLATFORM_STM32G0)

	uint32_t mask = 1 << _pinNum;
	EXTI->RTSR1 &= ~mask;
	EXTI->FTSR1 &= ~mask;

	#else
		#error "Unknown platform"
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'event.
/// \param    event: El event.
/// \param    enabled: Indica si esta habilitat o no.
///
void PinInterrupt::setNotifyEvent(
	INotifyEvent &event,
	bool enabled) {

	_notifyEvent = &event;
	_notifyEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interupcions.
///
void PinInterrupt::interruptService() const {

	// Revisar per que els flags son per tots els ports

	uint32_t mask = 1 << _pinNum;

	#if defined(EOS_PLATFORM_STM32F4) || \
	    defined(EOS_PLATFORM_STM32F7)

	if (EXTI->PR & mask) {
		EXTI->PR = mask;

		auto gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE + (_portNum * 0x400));

		// Si la entrada es 1, es un flanc ascendent
		//
		if (gpio->IDR & mask)
			notifyRisingEdge();

		// En cas contrari es un flanc descendent
		//
		else
			notifyFallingEdge();
	}

	#elif defined(EOS_PLATFORM_STM32G0)

	if (EXTI->FPR1 & mask) {
		EXTI->FPR1 = mask;
		notifyFallingEdge();
	}

	if (EXTI->RPR1 & mask) {
		EXTI->RPR1 = mask;
		notifyRisingEdge();
	}

	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Invoca l'event de notificacio RisingEdge
///
void PinInterrupt::notifyRisingEdge() const {

	if (_notifyEventEnabled) {
		NotifyEventArgs args = {
			.id = NotifyID::risingEdge,
			.isr = true
		};
		_notifyEvent->execute(this, args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Invoca l'event de notificacio FallingEdge
///
void PinInterrupt::notifyFallingEdge() const {

	if (_notifyEventEnabled) {
		NotifyEventArgs args = {
			.id = NotifyID::fallingEdge,
			.isr = true
		};
		_notifyEvent->execute(this, args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mack: mascara de pins
/// \param    info: Informacio per la inicialitzacio.
///
void internal::initialize(
    GPIO_TypeDef * const gpio,
	PinMask mask,
    const InitInfo *info) {

    switch(info->mode) {
        case InitMode::input:
            internal::initInput(gpio, mask, info->input.mode);
            break;

        case InitMode::output:
            internal::initOutput(gpio, mask, info->output.mode,
                    info->output.speed, info->output.state);
            break;

        case InitMode::alternate:
            internal::initAlternate(gpio, mask, info->alternate.mode,
                    info->alternate.speed, info->alternate.function);
            break;

        case InitMode::analogic:
            internal::initAnalogic(gpio, mask);
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com a entrades.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a inicialitzar.
/// \param    node: Tipus d'entrada.
///
void internal::initInput(
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
void internal::initInput(
	GPIO_TypeDef * const gpio,
	PinBit bit,
	InputMode mode) {

	auto a = startAtomic();

    auto b = (uint8_t) bit;

    // Configura el pin com a entrada digital
    //
    auto MODER = gpio->MODER;
    MODER &= ~(MODE::Mask << (b * 2));
    MODER |= MODE::INPUT << (b * 2);
    gpio->MODER = MODER;

    // Configura les resistencies pull UP/DOWN
    //
    auto PUPDR = gpio->PUPDR;
    PUPDR &= ~(PUPD::Mask << (b * 2));
    switch (mode) {
        case InputMode::pullUp:
            PUPDR |= PUPD::UP << (b * 2);
            break;

        case InputMode::pullDown:
            PUPDR |= PUPD::DOWN << (b * 2);
            break;

        default:
            PUPDR |= PUPD::NONE << (b * 2);
            break;
    }
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
void internal::initOutput(
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
void internal::initOutput(
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
    clearBits(MODER, MODE::Mask << (b * 2));
    setBits(MODER, MODE::OUTPUT << (b * 2));
    gpio->MODER = MODER;

    // Configura el driver de sortida
    //
    auto OTYPER = gpio->OTYPER;
    clearBits(OTYPER, OTYPE::Mask << b);
    if (mode == OutputMode::openDrain ||
        mode == OutputMode::openDrainPullUp)
        setBits(OTYPER, OTYPE::OD << b);
    else
        setBits(OTYPER, OTYPE::PP << b);
    gpio->OTYPER = OTYPER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    clearBits(PUPDR, PUPD::Mask << (b * 2));
    if (mode == OutputMode::openDrainPullUp)
        setBits(PUPDR, PUPD::UP << (b * 2));
    else
        setBits(PUPDR, PUPD::NONE << (b * 2));
    gpio->PUPDR = PUPDR;

    // Configura la velocitat de conmutacio
    //
    auto OSPEEDR = gpio->OSPEEDR;
    clearBits(OSPEEDR, OSPEED::Mask << (b * 2));
    setBits(OSPEEDR, __speedTbl[(uint8_t) speed] << (b * 2));
    gpio->OSPEEDR = OSPEEDR;

    // Configura l'estat de sortida
    //
    gpio->ODR = 1 << b;

    endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com entrades/sortides alternatives.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara del pins a inicialitzar.
/// \param    mode: Tipus de entrada/sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    af: La funcio alternativa.
///
void internal::initAlternate(
	GPIO_TypeDef * const gpio,
	PinMask mask,
	AlternateMode mode,
	Speed speed,
	AlternateFunction af) {

    auto m = uint16_t(mask);
	for (uint8_t b = 0; b < 15; b++) {
		if ((m & (1 << b)) != 0)
		    initAlternate(gpio, PinBit(b), mode, speed, af);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com entrada/sortida alternativa.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
/// \param    mode: Tipus de entrada/sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    af: La funcio alternativa.
///
void internal::initAlternate(
    GPIO_TypeDef * const gpio,
    PinBit bit,
    AlternateMode mode,
    Speed speed,
    AlternateFunction af) {

	auto a = startAtomic();

    auto b = uint8_t(bit);

    // Configura el pin com entrada/sortida alternativa
    //
    auto MODER = gpio->MODER;
    clearBits(MODER, MODE::Mask << (b * 2));
    setBits(MODER, MODE::ALTERNATE << (b * 2));
    gpio->MODER = MODER;

    // Configura el driver de sortida
    //
    auto OTYPER = gpio->OTYPER;
    clearBits(OTYPER, OTYPE::Mask << b);
    if (mode == AlternateMode::openDrain ||
        mode == AlternateMode::openDrainPullUp)
        setBits(OTYPER, OTYPE::OD << b);
    else
    	setBits(OTYPER, OTYPE::PP << b);
    gpio->OTYPER = OTYPER;

    // Configura la resistencia pull UP
    //
    auto PUPDR = gpio->PUPDR;
    clearBits(PUPDR, PUPD::Mask << (b * 2));
    if (mode == AlternateMode::openDrainPullUp)
        setBits(PUPDR, PUPD::UP << (b * 2));
    else
    	setBits(PUPDR, PUPD::NONE << (b * 2));
    gpio->PUPDR = PUPDR;

    // Configura la velocitat de conmutacio
    //
    auto OSPEEDR = gpio->OSPEEDR;
    clearBits(OSPEEDR, OSPEED::Mask << (b * 2));
    setBits(OSPEEDR, __speedTbl[uint8_t(speed)] << (b * 2));
    gpio->OSPEEDR = OSPEEDR;

    // Selecciona la funcio alternativa
    //
    auto AFR = gpio->AFR[b >> 3];
    clearBits(AFR, AF::Mask << ((b & 0x07) * 4)) ;
    setBits(AFR, (uint32_t(af) & AF::Mask) << ((b & 0x07) * 4));
    gpio->AFR[b >> 3] = AFR;

    endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com entrades/sortides analogiques.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a inicialitzar.
///
void internal::initAnalogic(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

    auto m = uint16_t(mask);
    for (uint8_t b = 0; b < 15; b++) {
        if ((m & (1 << b)) != 0)
            initAnalogic(gpio, PinBit(b));
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com entrada/sortida analogica.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
///
void internal::initAnalogic(
    GPIO_TypeDef * const gpio,
    PinBit bit) {

	auto a = startAtomic();

	endAtomic(a);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza els pins. Els deixa en la seva configuracio
///           per defecte.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a desinicialitzar.
///
void internal::deinitialize(
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
void internal::deinitialize(
	GPIO_TypeDef * const gpio,
	PinBit bit) {
}
