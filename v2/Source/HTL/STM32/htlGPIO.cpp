#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;
using namespace htl::gpio;


#define MODER_Mask           0b11
#define MODER_INPUT          0b00
#define MODER_OUTPUT         0b01
#define MODER_ALTERNATE      0b10
#define MODER_ANALOGIC       0b11

#define PUPDR_Mask           0b11
#define PUPDR_NONE           0b00
#define PUPDR_UP             0b01
#define PUPDR_DOWN           0b10

#define OTYPER_Mask          0b1
#define OTYPER_PP            0b0
#define OTYPER_OD            0b1

#define OSPEEDR_Mask         0b11
#define OSPEEDR_LOW          0b00
#define OSPEEDR_MEDIUM       0b01
#define OSPEEDR_HIGH         0b10
#define OSPEEDR_FAST         0b11

#define AFR_Mask             0b1111


static void gpioInitInput(GPIO_TypeDef * const gpio, PinMask mask, InputMode mode);
static void gpioInitOutput(GPIO_TypeDef * const gpio, PinMask mask, OutputMode mode, Speed speed, bool state);
static void gpioInitAlternate(GPIO_TypeDef * const gpio, PinMask mask, AlternateMode mode, Speed speed, PinFunction pinFuntion);
static void gpioInitAnalogic(GPIO_TypeDef * const gpio, PinMask mask);
static void gpioDeinitialize(GPIO_TypeDef * const gpio, PinMask mask);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres hardware del modul GPIO.
///
Port::Port(
	GPIO_TypeDef *gpio):

	_gpio {gpio} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com entrades.
/// \param    mask: Mascara de pins a configurar.
/// \param    mode: Tipus d'entrada.
///
void Port::initInput(
	PinMask mask,
	InputMode mode) {

	activate(mask);
	gpioInitInput(_gpio, mask, mode);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com sortides.
/// \param    mask: Mascara de pins a configurar.
/// \param    mode: El tipus de sortida.
/// \param    speed: Opcions de velocitat.
///
void Port::initOutput(
	PinMask mask,
	OutputMode mode,
	Speed speed) {

	activate(mask);
	gpioInitOutput(_gpio, mask, mode, speed, false);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
///
void Port::deinitialize() {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres harware del modul GPIO.
/// \param    pinID: Identificador del pin.
///
Pin::Pin(
	GPIO_TypeDef *gpio,
	PinID pinID) :

	_gpio {gpio},
	_mask {PinMask(1 << uint32_t(pinID))} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin en modun entrada digital.
/// \param    mode: El tipus d'entrada.
///
void Pin::initInput(
	InputMode mode)  {

	activate();
	gpioInitInput(_gpio, _mask, mode);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin en modus soirtida digital.
/// \parAM    mode: El tipus de sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    state: L'estat inicial de la sortida.
///
void Pin::initOutput(
	OutputMode mode,
	Speed speed,
	bool state) {

	activate();
	gpioInitOutput(_gpio, _mask, mode, speed, state);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin en modus alternatiu.
/// \param    mode: El tipus de entrada/sortida
/// \param    speed: Velocitat de conmutacio.
/// \param    pinFunctionID: Funcio alternativa.
///
void Pin::initAlternate(
	AlternateMode mode,
	Speed speed,
	PinFunction pinFunction) {

	activate();
	gpioInitAlternate(_gpio, _mask, mode, speed, pinFunction);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com a entrada/sortida analogica.
///
void Pin::initAnalogic() {

	activate();
	gpioInitAnalogic(_gpio, _mask);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el pin i el deixa als valor per defecte.
///
void Pin::deinitialize() {

	gpioDeinitialize(_gpio, _mask);
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
	_notifyEvent {nullptr},
	_notifyEventEnabled {false} {

}


/// ----------------------------------------------------------------------
/// \brief    Habilita la interrupcio.
/// \param    edge: El flanc que genera la interrupcio.
/// \remarks  Hi han limitavcions en funcio del hardware.
///
void PinInterrupt::enableInterruptPin(
	Edge edge) {

	#if defined(EOS_PLATFORM_STM32F4) || \
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
void PinInterrupt::disableInterruptPin() {

	#if defined(EOS_PLATFORM_STM32F4) || \
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
void PinInterrupt::interruptService() {

	// Revisar per que els flags son per tots els ports

	uint32_t mask = 1 << _pinNum;

	#if defined(EOS_PLATFORM_STM32F4) || \
	    defined(EOS_PLATFORM_STM32F7)

	if (EXTI->PR & mask) {
		EXTI->PR = mask;

		GPIO_TypeDef *gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE + (_portNum * 0x400));

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
void PinInterrupt::notifyRisingEdge() {

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
void PinInterrupt::notifyFallingEdge() {

	if (_notifyEventEnabled) {
		NotifyEventArgs args = {
			.id = NotifyID::fallingEdge,
			.isr = true
		};
		_notifyEvent->execute(this, args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com a entrades.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a inicialitzar.
/// \param    node: Tipus d'entrada.
///
static void gpioInitInput(
	GPIO_TypeDef * const gpio,
	PinMask mask,
	InputMode mode) {

	for (PinNumber pn = 0; pn < 15; pn++) {
		if ((mask & (1 << pn)) != 0) {

			uint32_t tmp;

			// Configura el piun com a entrada digital
			//
			tmp = gpio->MODER;
			tmp &= ~(MODER_Mask << (pn * 2));
			tmp |= MODER_INPUT << (pn * 2);
			gpio->MODER = tmp;

			// Configura les resistencies pull UP/DOWN
			//
			tmp = gpio->PUPDR;
			tmp &= ~(PUPDR_Mask << (pn * 2));
			switch (mode) {
				case InputMode::pullUp:
					tmp |= PUPDR_UP << (pn * 2);
					break;

				case InputMode::pullDown:
					tmp |= PUPDR_DOWN << (pn * 2);
					break;

				default:
				    break;
			}
			gpio->PUPDR = tmp;

		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com sortides.
/// \param    gpio: Els registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a inicialitzar.
/// \param    mode: Tipus de sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    state: L'estat inicial del pin.
///
static void gpioInitOutput(
	GPIO_TypeDef * const gpio,
	PinMask mask,
	OutputMode mode,
	Speed speed,
	bool state) {

	static const uint32_t speedTbl[] = {OSPEEDR_LOW, OSPEEDR_MEDIUM,
		OSPEEDR_HIGH, OSPEEDR_FAST};

	for (PinNumber pn = 0; pn < 15; pn++) {
		if ((mask & (1 << pn)) != 0) {

			uint32_t tmp;

			// Configura el pin com sortida digital
			//
			tmp = gpio->MODER;
			tmp &= ~(MODER_Mask << (pn * 2));
			tmp |= MODER_OUTPUT << (pn * 2);
			gpio->MODER = tmp;

			// Configura el driver de sortida
			//
			tmp = gpio->OTYPER;
			tmp &= ~(OTYPER_Mask << pn);
			if (mode == OutputMode::openDrain ||
				mode == OutputMode::openDrainPullUp)
				tmp |= OTYPER_OD << pn;
			gpio->OTYPER = tmp;

			// Configura la resistencia pull UP
			//
			tmp = gpio->PUPDR;
			tmp &= ~(PUPDR_Mask << (pn * 2));
			if (mode == OutputMode::openDrainPullUp)
				tmp |= PUPDR_UP << (pn * 2);
			gpio->PUPDR = tmp;

			// Configura la velocitat de conmutacio
			//
			tmp = gpio->OSPEEDR;
			tmp &= ~(OSPEEDR_Mask << (pn * 2));
			tmp |= speedTbl[uint8_t(speed)] << (pn * 2);
			gpio->OSPEEDR = tmp;

			gpio->ODR |= (state ? 1 : 0) << pn;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com entrades/sortides alternatives.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara del pins a inicialitzar.
/// \param    mode: Tipus de entrada/sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    pinFunction: La funcio alternativa.
///
static void gpioInitAlternate(
	GPIO_TypeDef * const gpio,
	PinMask mask,
	AlternateMode mode,
	Speed speed,
	PinFunction pinFunction) {

	static const uint32_t speedTbl[] = {OSPEEDR_LOW, OSPEEDR_MEDIUM,
		OSPEEDR_HIGH, OSPEEDR_FAST};

	for (PinNumber pn = 0; pn < 15; pn++) {
		if ((mask & (1 << pn)) != 0) {

			uint32_t tmp;

			// Configura el pin com entrada/sortida alternativa
			//
			tmp = gpio->MODER;
			tmp &= ~(MODER_Mask << (pn * 2));
			tmp |= MODER_ALTERNATE << (pn * 2);
			gpio->MODER = tmp;

			// Configura el driver de sortida
			//
			tmp = gpio->OTYPER;
			tmp &= ~(OTYPER_Mask << pn);
			if (mode == AlternateMode::openDrain ||
				mode == AlternateMode::openDrainPullUp)
				tmp |= OTYPER_OD << pn;
			gpio->OTYPER = tmp;

			// Configura la resistencia pull UP
			//
			tmp = gpio->PUPDR;
			tmp &= ~(PUPDR_Mask << (pn * 2));
			if (mode == AlternateMode::openDrainPullUp)
				tmp |= PUPDR_UP << (pn * 2);
			gpio->PUPDR = tmp;

			// Configura la velocitat de conmutacio
			//
			tmp = gpio->OSPEEDR;
			tmp &= ~(OSPEEDR_Mask << (pn * 2));
			tmp |= speedTbl[uint8_t(speed)] << (pn * 2);
			gpio->OSPEEDR = tmp;

			// Selecciona la funcio alternativa
			//
			tmp = gpio->AFR[pn >> 3];
			tmp &= ~(AFR_Mask << ((pn & 0x07) * 4)) ;
			tmp |= (uint32_t(pinFunction) & AFR_Mask) << ((pn & 0x07) * 4);
			gpio->AFR[pn >> 3] = tmp;
		}
	}
}


static void gpioInitAnalogic(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

}


static void gpioDeinitialize(
	GPIO_TypeDef * const gpio,
	PinMask mask) {
/*
	for (PinNumber pn = 0; pn < 15; pn++) {
		if ((mask & (1 << pn)) != 0) {

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
		}
	}
	*/
}
