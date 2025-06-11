#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/htlAtomic.h"
#include "HTL/htlGPIO.h"


using namespace htl;
using namespace htl::gpio;


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
/// \param    pupd: Resistencies pull up/down.
///
void PortDevice::initInput(
	PinMask mask,
	PullUpDown pupd) const {

	activate(mask);
	htl::gpio::initInput(_gpio, mask, pupd);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com sortides.
/// \param    mask: Mascara de pins a configurar.
/// \param    type: El tipus de sortida.
/// \param    pupd: Resistencies pull up/down.
/// \param    speed: Opcions de velocitat.
///
void PortDevice::initOutput(
	PinMask mask,
	OutputType type,
	PullUpDown pupd,
	Speed speed) const {

	activate(mask);
	htl::gpio::initOutput(_gpio, mask, type, pupd, speed, false);
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

    htl::gpio::initialize(_gpio, _mask, &info);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com entrada digital.
/// \param    pupd: Reesistencies pull up/down.
///
void PinDevice::initInput(
	PullUpDown pupd) const {

	activate();
	htl::gpio::initInput(_gpio, _mask, pupd);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com sortida digital.
/// \parAM    type: El tipus de sortida.
/// \param    pupd: Resistencies pull up/down.
/// \param    speed: Velocitat de conmutacio.
/// \param    state: L'estat inicial de la sortida.
///
void PinDevice::initOutput(
	OutputType type,
	PullUpDown pupd,
	Speed speed,
	bool state) const {

	activate();
	htl::gpio::initOutput(_gpio, _mask, type, pupd, speed, state);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com a entrada/sortida analogica.
///
void PinDevice::initAnalogic() const {

	activate();
	htl::gpio::initAnalogic(_gpio, _mask);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com entrada/sortida alternativa.
/// \param    type: El tipus de sortida.
/// \param    pupd: Resistencies pull pu/down
/// \param    speed: Velocitat de conmutacio.
/// \param    af: La funcio alternativa.
///
void PinDevice::initAlternate(
	OutputType type,
	PullUpDown pupd,
	Speed speed,
	AlternateFunction af) const {

	activate();
	htl::gpio::initAlternate(_gpio, _mask, type, pupd, speed, af);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el pin i el deixa als valor per defecte.
///
void PinDevice::deinitialize() const {

#if HTL_GPIO_OPTIONS == 1
	deactivate();
#endif
	htl::gpio::deinitialize(_gpio, _mask);
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


