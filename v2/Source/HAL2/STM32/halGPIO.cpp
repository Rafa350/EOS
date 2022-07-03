#include "HAL2/hal.h"
#include "HAL2/STM32/halGPIO.H"


using namespace hal;


/// ----------------------------------------------------------------------
/// \brief     Constructor.
/// \param     port: Identificador del port.
/// \param     pin: Identificador del pin.
//
GPIO::GPIO(
	GPIOPort port,
	GPIOPin pin) {

    switch (port) {
        case GPIOPort::portA:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        	_base = GPIOA_BASE;
        	break;

        case GPIOPort::portB:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
        	_base = GPIOB_BASE;
        	break;

        case GPIOPort::portC:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
        	_base = GPIOC_BASE;
        	break;

        case GPIOPort::portD:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
        	_base = GPIOD_BASE;
        	break;

        case GPIOPort::portE:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
        	_base = GPIOE_BASE;
        	break;

        case GPIOPort::portF:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
        	_base = GPIOF_BASE;
        	break;

        case GPIOPort::portG:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
        	_base = GPIOG_BASE;
        	break;

        case GPIOPort::portH:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
        	_base = GPIOH_BASE;
        	break;

        case GPIOPort::portI:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
        	_base = GPIOI_BASE;
        	break;

        case GPIOPort::portJ:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
        	_base = GPIOJ_BASE;
        	break;

        case GPIOPort::portK:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
        	_base = GPIOK_BASE;
        	break;
    }

    _pnum = static_cast<int>(pin);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    gpio: El objecte a copiar.
///
GPIO::GPIO(
	const GPIO &gpio) :

    _base(gpio._base),
    _pnum(gpio._pnum) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin per entrada.
/// \param    mode: Modus de treball del pin.
///
void GPIO::setMode(
	InpMode mode) {

	uint32_t temp;

	GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_base);

	// Configura el registre MODER (Mode Register)
	//
	temp = regs->MODER;
	temp &= ~(0b11 << (_pnum * 2));
	if (mode == InpMode::analog)
		temp |= 0b11 << (_pnum * 2);
	regs->MODER = temp;

	// Configura el registre PUPDR (Pull Up/Down Register)
	//
	temp = regs->PUPDR;
	temp &= ~(0b11 << (_pnum * 2));
	if (mode == InpMode::input_PU)
		temp |= 0b01 << (_pnum * 2);
	else if (mode == InpMode::input_PD)
		temp |= 0b10 << (_pnum * 2);
	regs->PUPDR = temp;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin per sortida.
/// \param    mode: Modus de treball del pin.
/// \param    alt: Funcio alternativa
///
void GPIO::setMode(
	OutMode mode,
	Alt alt) {

	GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_base);

	uint32_t temp;

	// Configura el registre MODER (Mode Register)
	//
	temp = regs->MODER;
	temp &= ~(0b11 << (_pnum * 2));
	if (alt == Alt::altNone)
		temp |= 0b01 << (_pnum * 2);
	else
		temp |= 0b10 << (_pnum * 2);
	regs->MODER = temp;

	// Configura el registre OTYPER (Output Type Register)
	//
	temp = regs->OTYPER;
	temp &= ~(1u << _pnum);
	if (mode == OutMode::output_OD)
		temp |= 1 << _pnum;
	regs->OTYPER = temp;

	// Configura el registre PUPDR (Pull Up/Down Register)
	//
	temp = regs->PUPDR;
	temp &= ~(0b11 << (_pnum * 2));
	if (mode == OutMode::output_OD_PU)
		temp |= 0b01 << (_pnum * 2);
	regs->PUPDR = temp;

	// Configura el registre AFR (Alternate Funcion Register)
	//
	if (alt != Alt::altNone) {
		temp = regs->AFR[_pnum >> 3];
		temp &= ~(0x0F << ((_pnum & 0x07) * 4)) ;
		temp |= ((uint32_t)(alt) << ((_pnum & 0x07) * 4));
		regs->AFR[_pnum >> 3] = temp;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la velocitat de conmutacio
/// \param    speed: Velocitat.
///
void GPIO::setSpeed(
	Speed speed) {

	GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_base);

	// Conmfigura el registre OSPEEDR (Output Speed Register)
	//
	uint32_t temp = regs->OSPEEDR;
	temp &= ~(0b11 << (_pnum * 2));
	switch (speed) {
		case Speed::low:
			break;

		case Speed::medium:
			temp |= 0b01 < (_pnum * 2);
			break;

		case Speed::high:
			temp |= 0b10 < (_pnum * 2);
			break;

		case Speed::fast:
			temp |= 0b11u < (_pnum * 2);
			break;
	}
	regs->OSPEEDR = temp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el estat SET al pin.
///
void GPIO::set() const {

	GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_base);

	regs->BSRR = 1 << _pnum;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el estat CLEAR al pin.
///
void GPIO::clear() const {

	GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_base);

	regs->BSRR = 1 << (_pnum + 16);
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat del pin.
///
void GPIO::toggle() const {

	GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_base);

	regs->ODR ^= 1 << _pnum;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu l'estat del pin.
/// \param    s: eL ESTAT.
///
void GPIO::write(
	bool s) const {

	GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_base);

	regs->BSRR = 1 << (_pnum + (s ? 0 : 16));
}


/// ----------------------------------------------------------------------
/// \Brief    Llegeix l'estat del pin.
/// \return   L'estat del pin.
///
bool GPIO::read() const {

	GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_base);

	return (regs->IDR & (1 << _pnum)) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Operador =
/// \param    gpio: El objecte a asignar.
///
GPIO & GPIO::operator = (
	const GPIO &gpio) {

    _base = gpio._base;
    _pnum = gpio._pnum;

    return *this;
}
