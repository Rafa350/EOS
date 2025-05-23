#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;
using namespace htl::gpio;


struct MODER {
	static constexpr uint32_t Mask      = 0b11;
	static constexpr uint32_t INPUT     = 0b00;
	static constexpr uint32_t OUTPUT    = 0b01;
	static constexpr uint32_t ALTERNATE = 0b10;
	static constexpr uint32_t ANALOGIC  = 0b11;
};

struct PUPDR {
	static constexpr uint32_t Mask = 0b11;
	static constexpr uint32_t NONE = 0b00;
	static constexpr uint32_t UP   = 0b01;
	static constexpr uint32_t DOWN = 0b10;
};

struct OTYPER {
	static constexpr uint32_t Mask = 0b1;
	static constexpr uint32_t PP   = 0b0;
	static constexpr uint32_t OD   = 0b1;
};

struct OSPEEDR {
	static constexpr uint32_t Mask   = 0b11;
	static constexpr uint32_t LOW    = 0b00;
	static constexpr uint32_t MEDIUM = 0b01;
	static constexpr uint32_t HIGH   = 0b10;
	static constexpr uint32_t FAST   = 0b11;
};

struct AFR {
	static constexpr uint32_t Mask = 0b1111;
};


static const uint32_t __speedTbl[] = {
    OSPEEDR::LOW,
    OSPEEDR::MEDIUM,
    OSPEEDR::HIGH,
    OSPEEDR::FAST};


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
    PinBit bit):

    _gpio {gpio},
    _mask {bit} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    info: Parametres d'inicialitzacio.
///
void PinDevice::initialize(
    const InitInfo &info) const {

    activate();
    internal::initialize(_gpio, _mask, &info);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin en modun entrada digital.
/// \param    mode: El tipus d'entrada.
///
void PinDevice::initInput(
	InputMode mode) const {

	activate();
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

    activate();
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

	activate();
	internal::initAlternate(_gpio, _mask, mode, speed, af);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com a entrada/sortida analogica.
///
void PinDevice::initAnalogic() const {

    activate();
	internal::initAnalogic(_gpio, _mask);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el pin i el deixa als valor per defecte.
///
void PinDevice::deinitialize() const {

	internal::deinitialize(_gpio, _mask);
    deactivate();
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

    auto m = uint16_t(mask);
    for (uint8_t b = 0; b < 15; b++) {
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

    auto b = uint8_t(bit);

    uint32_t tmp;

    // Configura el pin com a entrada digital
    //
    tmp = gpio->MODER;
    tmp &= ~(MODER::Mask << (b * 2));
    tmp |= MODER::INPUT << (b * 2);
    gpio->MODER = tmp;

    // Configura les resistencies pull UP/DOWN
    //
    tmp = gpio->PUPDR;
    tmp &= ~(PUPDR::Mask << (b * 2));
    switch (mode) {
        case InputMode::pullUp:
            tmp |= PUPDR::UP << (b * 2);
            break;

        case InputMode::pullDown:
            tmp |= PUPDR::DOWN << (b * 2);
            break;

        default:
            tmp |= PUPDR::NONE << (b * 2);
            break;
    }
    gpio->PUPDR = tmp;
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

    auto m = uint16_t(mask);
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

    auto b = uint8_t(bit);

    uint32_t tmp;

    // Configura el pin com sortida digital
    //
    tmp = gpio->MODER;
    clearBits(tmp, MODER::Mask << (b * 2));
    setBits(tmp, MODER::OUTPUT << (b * 2));
    gpio->MODER = tmp;

    // Configura el driver de sortida
    //
    tmp = gpio->OTYPER;
    clearBits(tmp, OTYPER::Mask << b);
    if (mode == OutputMode::openDrain ||
        mode == OutputMode::openDrainPullUp)
        setBits(tmp, OTYPER::OD << b);
    else
        setBits(tmp, OTYPER::PP << b);
    gpio->OTYPER = tmp;

    // Configura la resistencia pull UP
    //
    tmp = gpio->PUPDR;
    clearBits(tmp, PUPDR::Mask << (b * 2));
    if (mode == OutputMode::openDrainPullUp)
        setBits(tmp, PUPDR::UP << (b * 2));
    else
        setBits(tmp, PUPDR::NONE << (b * 2));
    gpio->PUPDR = tmp;

    // Configura la velocitat de conmutacio
    //
    tmp = gpio->OSPEEDR;
    clearBits(tmp, OSPEEDR::Mask << (b * 2));
    setBits(tmp, __speedTbl[uint8_t(speed)] << (b * 2));
    gpio->OSPEEDR = tmp;

    setBits(gpio->ODR, (state ? 1 : 0) << b);
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

    auto b = uint8_t(bit);

    uint32_t tmp;

    // Configura el pin com entrada/sortida alternativa
    //
    tmp = gpio->MODER;
    clearBits(tmp, MODER::Mask << (b * 2));
    setBits(tmp, MODER::ALTERNATE << (b * 2));
    gpio->MODER = tmp;

    // Configura el driver de sortida
    //
    tmp = gpio->OTYPER;
    clearBits(tmp, OTYPER::Mask << b);
    if (mode == AlternateMode::openDrain ||
        mode == AlternateMode::openDrainPullUp)
        setBits(tmp, OTYPER::OD << b);
    else
    	setBits(tmp, OTYPER::PP << b);
    gpio->OTYPER = tmp;

    // Configura la resistencia pull UP
    //
    tmp = gpio->PUPDR;
    clearBits(tmp, PUPDR::Mask << (b * 2));
    if (mode == AlternateMode::openDrainPullUp)
        setBits(tmp, PUPDR::UP << (b * 2));
    else
    	setBits(tmp, PUPDR::NONE << (b * 2));
    gpio->PUPDR = tmp;

    // Configura la velocitat de conmutacio
    //
    tmp = gpio->OSPEEDR;
    clearBits(tmp, OSPEEDR::Mask << (b * 2));
    setBits(tmp, __speedTbl[uint8_t(speed)] << (b * 2));
    gpio->OSPEEDR = tmp;

    // Selecciona la funcio alternativa
    //
    tmp = gpio->AFR[b >> 3];
    clearBits(tmp, AFR::Mask << ((b & 0x07) * 4)) ;
    setBits(tmp, (uint32_t(af) & AFR::Mask) << ((b & 0x07) * 4));
    gpio->AFR[b >> 3] = tmp;
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

    auto m = uint16_t(mask);
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
/*

    uint32_t tmp;

    tmp = gpio->MODER;
    #if defined(EOS_PLATFORM_STM32F4)
    tmp |= MODER_ANALOGIC << pn;
    #elif defined(EOS_PLATFORM_STM32G0)
    tmp &= MODER_Mask << pn;
    if ((gpio == reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE)) && ((pn == 13 || pn == 14)))
        tmp |= MODER_ALTERNATE << pn;
    else
        tmp |= MODER_ANALOGIC << pn;
    #else
    #error "Undefined platform"
    #endif
    gpio->MODER = tmp;

    tmp = gpio->OTYPER;
    tmp &= OTYPER_Mask << pn;
    tmp |= OTYPER_PP << pn;
    gpio->OTYPER = tmp;

    tmp = gpio->PUPDR;
    tmp &= PUPDR_Mask << pn;
    #if defined(EOS_PLATFORM_STM32F4)
    tmp |=  PUPDR_NONE << pn;
    #elif defined(EOS_PLATFORM_STM32G0)
    if ((gpio == reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE)) && (pn == 14))
        tmp |= PUPDR_DOWN << pn;
    else if ((gpio == reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE)) && (pn == 13))
        tmp |= PUPDR_UP << pn;
    else
        tmp |=  PUPDR_NONE << pn;
    #else
    #error "Undefined platform"
    #endif
    gpio->PUPDR = tmp;

    gpio->ODR = 0 << pn;

    gpio->AFR[pn >> 3] &= ~(AFR_Mask << ((pn & 0x07) * 4)) ;
	*/
}
