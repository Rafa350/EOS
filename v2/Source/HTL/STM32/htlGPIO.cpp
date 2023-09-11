#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl::gpio;


/// ----------------------------------------------------------------------
/// \brief    Selecciona el modus de treball dels pins.
/// \param    gpio: Registres hardware del modul GPIO.
/// \param    mask: Mascara de pins.
/// \param    mode: Opcions del modus de treball.
///
static void setMode(
	GPIO_TypeDef *gpio,
	PinMask mask,
	uint8_t mode) {

	for (PinNumber pn = 0; pn < 15; pn++) {
		if ((mask & (1 << pn)) != 0) {

			uint32_t tmp = gpio->MODER;
			tmp &= ~(0b11 << (pn * 2));
			tmp |= (mode & 0b11) << (pn * 2);
			gpio->MODER = tmp;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el driver de sortida.
/// \param    gpio: Registres hardware del modul GPIO
/// \param    mask: Mascara de pins.
/// \param    driver: Opcions de driver.
///
static void setDriver(
	GPIO_TypeDef *gpio,
	PinMask mask,
	OutDriver driver) {

	if (driver != OutDriver::noChange) {

		for (PinNumber pn = 0; pn < 15; pn++) {
			if ((mask & (1 << pn)) != 0) {
				uint32_t tmp = gpio->OTYPER;
				tmp &= ~(1 << pn);
				if (driver == OutDriver::openDrain)
					tmp |= 1 << pn;
				gpio->OTYPER = tmp;
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la velocitat de sortida.
/// \param    gpio: Registres de hardware del modul.
/// \param    mask: Mascara de pins.
/// \param    speed: Opcions de velocitat.
///
static void setSpeed(
	GPIO_TypeDef *gpio,
	PinMask mask,
	Speed speed) {

	if (speed != Speed::noChange) {

		uint32_t value = 1; // Per defecte medium

		switch (speed) {
			case Speed::low:
				value = 0;
				break;
			case Speed::high:
				value = 2;
				break;
			case Speed::fast:
				value = 3;
				break;
			default:
				break;
		}

		for (PinNumber pn = 0; pn < 15; pn++) {
			if ((mask & (1 << pn)) != 0) {
				uint32_t tmp = gpio->OSPEEDR;
				tmp &= ~(0b11 << (pn * 2));
				tmp |= value << (pn * 2);
				gpio->OSPEEDR = tmp;
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la opcio pull.
/// \param    gpio: Els registres hardware del modul GPIO
/// \param    mask: La mascara de pins.
/// \param    pull: Les opcions pull.
///
static void setPull(
	GPIO_TypeDef *gpio,
	PinMask mask,
	PullUpDn pull) {

	if (pull != PullUpDn::noChange) {

		uint32_t value = 0; // Per defecte sense PU/PD

		switch (pull) {
			case PullUpDn::down:
				value = 2;
				break;
			case PullUpDn::up:
				value = 1;
				break;
			default:
				break;
		}

		for (PinNumber pn = 0; pn < 15; pn++) {
			if ((mask & (1 << pn)) != 0) {
				uint32_t tmp = gpio->PUPDR;
				tmp &= ~(0b11 << (pn * 2));
				tmp |= value << (pn * 2);
				gpio->PUPDR = tmp;
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la funcio alternativa del pin.
/// \param    gpio: Els registres hardware del modul GPIO.
/// \param    mask: La mascara de pins
/// \param    pinFunctionID: Identificador de la funcio alternativa.
///
static void setPinFunction(
	GPIO_TypeDef *gpio,
	PinMask mask,
	PinFunctionID pinFunctionID) {

	for (PinNumber pn = 0; pn < 15; pn++) {
		if ((mask & (1 << pn)) != 0) {
			uint32_t tmp = gpio->AFR[pn >> 3];
			tmp &= ~(0b1111 << ((pn & 0x07) * 4)) ;
			tmp |= (uint32_t(pinFunctionID) & 0b1111) << ((pn & 0x07) * 4);
			gpio->AFR[pn >> 3] = tmp;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres hardware del modul GPIO.
///
Port::Port(
	GPIO_TypeDef *regs):

	_gpio {regs} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com entrades.
/// \param    mask: Mascara de pins a configurar.
/// \param    pull: Opcions de pull up-down
///
void Port::initInput(
	PinMask mask,
	PullUpDn pull) {

	activate(mask);

    setMode(_gpio, mask, 0);
    setPull(_gpio, mask, pull);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com sortides.
/// \param    mask: Mascara de pins a configurar.
/// \param    driver: Opcions de driver.
/// \param    speed: Opcions de velocitat.
///
void Port::initOutput(
	PinMask mask,
	OutDriver driver,
	Speed speed) {

	activate(mask);

	setMode(_gpio, mask, 1);
	setDriver(_gpio, mask, driver);
	setSpeed(_gpio, mask, speed);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres harware del modul GPIO.
/// \param    pinID: Identificador del pin.
///
Pin::Pin(
	GPIO_TypeDef *gpio,
	PinID pinID) :

	_gpio(gpio),
	_mask(1 << uint32_t(pinID)) {

}

/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com entrada.
/// \param    pull: Opcions pull up/down.
///
void Pin::initInput(
    PullUpDn pull) {

	activate();

    setMode(_gpio, _mask, 0);
    setPull(_gpio, _mask, pull);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com sortida.
/// \param    driver: Opcions de driver.
/// \param    speed: Opcions de velocitat.
/// \param    state: Estat inicial.
///
void Pin::initOutput(
	OutDriver driver,
	Speed speed,
	InitPinState state) {

	activate();

	switch (state) {
		case InitPinState::set:
			set();
			break;
		case InitPinState::clear:
			clear();
			break;
		default:
			break;
	}

	setMode(_gpio, _mask, 1);
	setDriver(_gpio, _mask, driver);
	setSpeed(_gpio, _mask, speed);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com a sortida alternativa.
/// \param    regs: Bloc de registres.
/// \param    pn: Numero de pin.
/// \param    driver: Opcions del driver de sortida.
/// \param    speed: Opcions de velocitat.
/// \param    pinFunctionID: Funcio alternativa.
///
void Pin::initAlt(
    OutDriver driver,
    Speed speed,
    PinFunctionID pinFunctionID) {

	activate();

    setMode(_gpio, _mask, 2);
    setDriver(_gpio, _mask, driver);
    setSpeed(_gpio, _mask, speed);
    setPinFunction(_gpio, _mask, pinFunctionID);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com a entrada/sortida analogica.
/// \param    regs: Bloc de registres.
/// \param    pn: Numero de pin.
///
void Pin::initAnalogic() {

	activate();

	setMode(_gpio, _mask, 3);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres de hardware del modul GPIO.
/// \param    pinID: Identificador del pin.
///
PinInterrupt::PinInterrupt(
	GPIO_TypeDef *gpio,
	PinID pinID) :

	_portNum {(uint32_t(gpio) >> 10) & 0x000F},
	_pinNum {uint32_t(pinID)},
	_risingEdgeEvent {nullptr},
	_fallingEdgeEvent {nullptr},
	_risingEdgeEventEnabled {false},
	_fallingEdgeEventEnabled {false} {

}


/// ----------------------------------------------------------------------
/// \brief    Habilita la interrupcio.
/// \param    edge: El flanc que genera la interrupcio.
/// \remarks  Hi han limitavcions en funcio del hardware.
///
void PinInterrupt::enableInterruptPin(
	Edge edge) {

	#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)

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
void PinInterrupt::disableInterruptPin() {

	#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)

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
void PinInterrupt::setFallingEdgeEvent(
	IFallingEdgeEvent &event,
	bool enabled) {

	_fallingEdgeEvent = &event;
	_fallingEdgeEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'event.
/// \param    event: El event.
/// \param    enabled: Indica si esta habilitat o no.
///
void PinInterrupt::setRisingEdgeEvent(
	IRisingEdgeEvent &event,
	bool enabled) {

	_risingEdgeEvent = &event;
	_risingEdgeEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interupcions.
///
void PinInterrupt::interruptService() {

	// Revisar per que els flags son per tots els ports

	uint32_t mask = 1 << _pinNum;

	#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)

	if (EXTI->PR & mask) {
		EXTI->PR = mask;

		GPIO_TypeDef *gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE + (_portNum * 0x400));

		// Si la entrada es 1, es un flanc ascendent
		//
		if (gpio->IDR & mask) {
			if (_risingEdgeEventEnabled)
				_risingEdgeEvent->execute(*this);
		}

		// En cas contrari es un flanc descendent
		//
		else {
			if (_fallingEdgeEventEnabled)
				_fallingEdgeEvent->execute(*this);
		}
	}

	#elif defined(EOS_PLATFORM_STM32G0)
	if (EXTI->FPR1 & mask) {
		EXTI->FPR1 = mask;

		if (_fallingEdgeEventEnabled)
			_fallingEdgeEvent->execute(*this);
	}

	if (EXTI->RPR1 & mask) {
		EXTI->RPR1 = mask;

		if (_risingEdgeEventEnabled)
			_risingEdgeEvent->execute(*this);
	}
	#endif
}

