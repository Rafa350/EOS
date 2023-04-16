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

	_gpio(regs) {

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

	activateImpl(mask);

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
	_mask(1 << int(pinID)) {

}

/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com entrada.
/// \param    pull: Opcions pull up/down.
///
void Pin::initInput(
    PullUpDn pull) {

	activateImpl();

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

	activateImpl();

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

	activateImpl();

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

	activateImpl();

	setMode(_gpio, _mask, 3);
}
