#include "HAL2/hal.h"
#include "HAL2/STM32/halGPIO.H"


using namespace eos;


#define __set_bit_msk(a, b)       ((a) |= (b))


/// ----------------------------------------------------------------------
/// \brief     Constructor.
/// \param     port: Identificador del port.
/// \param     pin: Identificador del pin.
//
GPIO::GPIO(
	GPIOPort port,
	GPIOPin pin) :

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
/// \brief    Inicialitza el pin.
/// \param    mode: Modus de treball del pin.
///
void GPIO::initialize(
	GPIOMode mode) {

	uint32_t temp;

	// Configura el registre MODER (Mode Register)
	//
	temp = _regs->MODER;
	temp &= ~(0b11 << (_pinNumber * 2));
	switch (mode) {

		// Sortida digital
		case GPIOMode::output:
		case GPIOMode::output_OD:
			temp |= 0b01 << (_pinNumber * 2);
			break;

		// Funcio alternativa
		case GPIOMode::alt:
		case GPIOMode::alt_OD:
			temp |= 0b10 << (_pinNumber * 2);
			break;

		// Entrada analogica
		case GPIOMode::analog:
			temp |= 0b11 << (_pinNumber * 2);
			break;

		// Entrada digital
		case GPIOMode::input:
		case GPIOMode::input_PU:
		case GPIOMode::input_PD:
			break;
	}
	_regs->MODER = temp;

	// Configura el registre OTYPER (Output Type Register)
	//
	if ((mode == GPIOMode::output) ||
		(mode == GPIOMode::output_OD) ||
		(mode == GPIOMode::alt) ||
		(mode == GPIOMode::alt_OD)) {

		temp = _regs->OTYPER;
		temp &= ~(1u << _pinNumber);
		if ((mode == GPIOMode::output_OD) ||
			(mode == GPIOMode::alt_OD))
			temp |= 1 << _pinNumber;
		_regs->OTYPER = temp;
	}

	// Configura el registre PUPDR (Pull Up/Down Register)
	//
	if ((mode == GPIOMode::input_PU) ||
		(mode == GPIOMode::input_PD)) {

		temp = _regs->PUPDR;
		temp &= ~(0b11 << (_pinNumber * 2u));
		if (mode == GPIOMode::input_PU)
			temp |= 0b01 << (_pinNumber * 2);
		else
			temp |= 0b10 << (_pinNumber * 2);
		_regs->PUPDR = temp;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la vecocitat de conmutacio
/// \param    speed: La velocitat.
///
void GPIO::setSpeed(
	GPIOSpeed speed) {

	uint32_t temp = _regs->OSPEEDR;
	temp &= ~(0b11 << (_pinNumber * 2));
	switch (speed) {
		case GPIOSpeed::low:
			break;

		case GPIOSpeed::medium:
			temp |= 0b01 < (_pinNumber * 2);
			break;

		case GPIOSpeed::high:
			temp |= 0b10 < (_pinNumber * 2);
			break;

		case GPIOSpeed::fast:
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
	uint32_t alt) {

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
	GPIOPort port) {

    uint32_t addr = 0;

    switch (port) {
        case GPIOPort::portA: addr = GPIOA_BASE; break;
        case GPIOPort::portB: addr = GPIOB_BASE; break;
        case GPIOPort::portC: addr = GPIOC_BASE; break;
        case GPIOPort::portD: addr = GPIOD_BASE; break;
        case GPIOPort::portE: addr = GPIOE_BASE; break;
        case GPIOPort::portF: addr = GPIOF_BASE; break;
        case GPIOPort::portG: addr = GPIOG_BASE; break;
        case GPIOPort::portH: addr = GPIOH_BASE; break;
        case GPIOPort::portI: addr = GPIOI_BASE; break;
        case GPIOPort::portJ: addr = GPIOJ_BASE; break;
        case GPIOPort::portK: addr = GPIOK_BASE; break;
    }

    return reinterpret_cast<GPIO_TypeDef*>(addr);
}


/// ----------------------------------------------------------------------
/// \brief    Obte la mascara associada al pin.
/// \param    pin: El identificador del pin.
/// \return   La mascara.
///

uint32_t GPIO::getPinNumber(
	GPIOPin pin) {

	uint32_t pinNumber = 0;

    switch (pin) {
        case GPIOPin::pin0: pinNumber = 0; break;
        case GPIOPin::pin1: pinNumber = 1; break;
        case GPIOPin::pin2: pinNumber = 2; break;
        case GPIOPin::pin3: pinNumber = 3; break;
        case GPIOPin::pin4: pinNumber = 4; break;
        case GPIOPin::pin5: pinNumber = 5; break;
        case GPIOPin::pin6: pinNumber = 6; break;
        case GPIOPin::pin7: pinNumber = 7; break;
        case GPIOPin::pin8: pinNumber = 8; break;
        case GPIOPin::pin9: pinNumber = 9; break;
        case GPIOPin::pin10: pinNumber = 10; break;
        case GPIOPin::pin11: pinNumber = 11; break;
        case GPIOPin::pin12: pinNumber = 12; break;
        case GPIOPin::pin13: pinNumber = 13; break;
        case GPIOPin::pin14: pinNumber = 14; break;
        case GPIOPin::pin15: pinNumber = 15; break;
    }

    return pinNumber;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el port.
/// \param    port: El identificador del port.
///
void GPIO::enableClock(
	GPIOPort port) {

	switch (port) {
		case GPIOPort::portA:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
			break;

		case GPIOPort::portB:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
			break;

		case GPIOPort::portC:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
			break;

		case GPIOPort::portD:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
			break;

		case GPIOPort::portE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
			break;

		case GPIOPort::portF:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);
			break;

		case GPIOPort::portG:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
			break;

		case GPIOPort::portH:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);
			break;

		case GPIOPort::portI:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);
			break;

		case GPIOPort::portJ:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN);
			break;

		case GPIOPort::portK:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN);
			break;
	}

	__DSB();
}
