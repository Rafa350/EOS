#include "HAL2/hal.h"
#include "HAL2/STM32/halGPIO.H"


using namespace hal;


/// ----------------------------------------------------------------------
/// \brief     Constructor.
/// \param     port: Identificador del port.
/// \param     pin: Identificador del pin.
//
GPIO::GPIO(
	Port port,
	Pin pin) :

    _regs(getRegister(port)),
    _pinNumber(getPinNumber(pin)) {

	enableClock(port);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    gpio: El objecte a copiar.
///
GPIO::GPIO(
	const GPIO &gpio) :

    _regs(gpio._regs),
    _pinNumber(gpio._pinNumber) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin per entrada.
/// \param    mode: Modus de treball del pin.
///
void GPIO::initInput(
	InputMode mode) {

	uint32_t temp;

	// Configura el registre MODER (Mode Register)
	//
	temp = _regs->MODER;
	temp &= ~(0b11 << (_pinNumber * 2));
	if (mode == InputMode::analog)
		temp |= 0b11 << (_pinNumber * 2);
	_regs->MODER = temp;

	// Configura el registre PUPDR (Pull Up/Down Register)
	//
	temp = _regs->PUPDR;
	temp &= ~(0b11 << (_pinNumber * 2u));
	if (mode == InputMode::input_PU)
		temp |= 0b01 << (_pinNumber * 2);
	else if (mode == InputMode::input_PD)
		temp |= 0b10 << (_pinNumber * 2);
	_regs->PUPDR = temp;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin per sortida.
/// \param    mode: Modus de treball del pin.
///
void GPIO::initOutput(
	OutputMode mode) {

	uint32_t temp;

	// Configura el registre MODER (Mode Register)
	//
	temp = _regs->MODER;
	temp &= ~(0b11 << (_pinNumber * 2));
	switch (mode) {

		// Sortida digital
		case OutputMode::output:
		case OutputMode::output_OD:
			temp |= 0b01 << (_pinNumber * 2);
			break;

		// Funcio alternativa
		case OutputMode::alt:
		case OutputMode::alt_OD:
			temp |= 0b10 << (_pinNumber * 2);
			break;
	}
	_regs->MODER = temp;

	// Configura el registre OTYPER (Output Type Register)
	//
	temp = _regs->OTYPER;
	temp &= ~(1u << _pinNumber);
	if ((mode == OutputMode::output_OD) ||
		(mode == OutputMode::alt_OD))
		temp |= 1 << _pinNumber;
	_regs->OTYPER = temp;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la velocitat de conmutacio
/// \param    speed: Velocitat.
///
void GPIO::setSpeed(
	Speed speed) {

	// Conmfigura el registre OSPEEDR (Output Speed Register)
	//
	uint32_t temp = _regs->OSPEEDR;
	temp &= ~(0b11 << (_pinNumber * 2));
	switch (speed) {
		case Speed::low:
			break;

		case Speed::medium:
			temp |= 0b01 < (_pinNumber * 2);
			break;

		case Speed::high:
			temp |= 0b10 < (_pinNumber * 2);
			break;

		case Speed::fast:
			temp |= 0b11u < (_pinNumber * 2);
			break;
	}
	_regs->OSPEEDR = temp;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la funcio alternativa del pin.
/// \param    alt: La funcio alternativa.
///
void GPIO::setAlt(
	Alt alt) {

	// Configura el registre AFR (Alternate Funcion Register)
	//
	uint32_t temp = _regs->AFR[_pinNumber >> 3];
	temp &= ~(0x0F << ((_pinNumber & 0x07) * 4)) ;
	temp |= ((uint32_t)(alt) << ((_pinNumber & 0x07) * 4));
	_regs->AFR[_pinNumber >> 3] = temp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el estat SET al pin.
///
void GPIO::set() const {

	_regs->BSRR = 1 << _pinNumber;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el estat CLEAR al pin.
///
void GPIO::clear() const {

	_regs->BSRR = 1 << (_pinNumber + 16);
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat del pin.
///
void GPIO::toggle() const {

	_regs->ODR ^= 1 << _pinNumber;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu l'estat del pin.
/// \param    s: eL ESTAT.
///
void GPIO::write(
	bool s) const {

	_regs->BSRR = 1 << (_pinNumber + (s ? 0 : 16));
}


/// ----------------------------------------------------------------------
/// \Brief    Llegeix l'estat del pin.
/// \return   L'estat del pin.
///
bool GPIO::read() const {

	return (_regs->IDR & (1 << _pinNumber)) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Operador =
/// \param    gpio: El objecte a asignar.
///
GPIO & GPIO::operator = (
	const GPIO &gpio) {

    _regs = gpio._regs;
    _pinNumber = gpio._pinNumber;

    return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador =
/// \param    s: El valor a signar.
///
GPIO & GPIO::operator = (
	bool s) {

	write(s);

    return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador de conversio a bool
/// \return   L'estat del pin.
///
GPIO::operator bool() const {

    return read();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el punter als registres asociats al port.
/// \param    port: El identificador del port.
/// \return   El punter.
///
GPIO_TypeDef* GPIO::getRegister(
	Port port) {

    uint32_t addr = 0;

    switch (port) {
        case Port::portA: addr = GPIOA_BASE; break;
        case Port::portB: addr = GPIOB_BASE; break;
        case Port::portC: addr = GPIOC_BASE; break;
        case Port::portD: addr = GPIOD_BASE; break;
        case Port::portE: addr = GPIOE_BASE; break;
        case Port::portF: addr = GPIOF_BASE; break;
        case Port::portG: addr = GPIOG_BASE; break;
        case Port::portH: addr = GPIOH_BASE; break;
        case Port::portI: addr = GPIOI_BASE; break;
        case Port::portJ: addr = GPIOJ_BASE; break;
        case Port::portK: addr = GPIOK_BASE; break;
    }

    return reinterpret_cast<GPIO_TypeDef*>(addr);
}


/// ----------------------------------------------------------------------
/// \brief    Obte la mascara associada al pin.
/// \param    pin: El identificador del pin.
/// \return   La mascara.
///

uint32_t GPIO::getPinNumber(
	Pin pin) {

	uint32_t pinNumber = 0;

    switch (pin) {
        case Pin::pin0: pinNumber = 0; break;
        case Pin::pin1: pinNumber = 1; break;
        case Pin::pin2: pinNumber = 2; break;
        case Pin::pin3: pinNumber = 3; break;
        case Pin::pin4: pinNumber = 4; break;
        case Pin::pin5: pinNumber = 5; break;
        case Pin::pin6: pinNumber = 6; break;
        case Pin::pin7: pinNumber = 7; break;
        case Pin::pin8: pinNumber = 8; break;
        case Pin::pin9: pinNumber = 9; break;
        case Pin::pin10: pinNumber = 10; break;
        case Pin::pin11: pinNumber = 11; break;
        case Pin::pin12: pinNumber = 12; break;
        case Pin::pin13: pinNumber = 13; break;
        case Pin::pin14: pinNumber = 14; break;
        case Pin::pin15: pinNumber = 15; break;
    }

    return pinNumber;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el port.
/// \param    port: El identificador del port.
///
void GPIO::enableClock(
	Port port) {

	switch (port) {
		case Port::portA:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
			break;

		case Port::portB:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
			break;

		case Port::portC:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
			break;

		case Port::portD:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
			break;

		case Port::portE:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
			break;

		case Port::portF:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
			break;

		case Port::portG:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
			break;

		case Port::portH:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
			break;

		case Port::portI:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
			break;

		case Port::portJ:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
			break;

		case Port::portK:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
			break;
	}

	__DSB();
}
