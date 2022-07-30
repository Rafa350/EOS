#include "eos.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Selecciona el driver de sortida.
/// \param    regs: El bloc de registres.
/// \param    pn: El numero de pin.
/// \param    driver: El driver a seleccionar.
///
static void setDriver(
	GPIO_TypeDef *regs,
	uint32_t pn,
	GPIODriver driver) {

    // Configura el registre OTYPER (Output Type Register)
    //
	if (driver != GPIODriver::noChange) {
		uint32_t temp = regs->OTYPER;
		temp &= ~(1 << pn);
		if (driver == GPIODriver::openDrain)
			temp |= 1 << pn;
		regs->OTYPER = temp;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la velocitat de sortida.
/// \param    regs: El bloc de registres.
/// \param    pn: El numero de pin.
/// \param    speed: La velocitat a seleccionar.
///
static void setSpeed(
	GPIO_TypeDef *regs,
	uint32_t pn,
	GPIOSpeed speed) {

	if (speed != GPIOSpeed::noChange) {

		uint32_t value = 1; // Per defecte medium

		#pragma GCC diagnostic push
		#pragma GCC diagnostic ignored "-Wswitch"
		switch (speed) {
			case GPIOSpeed::low:
				value = 0;
				break;

			case GPIOSpeed::high:
				value = 2;
				break;

			case GPIOSpeed::fast:
				value = 3;
				break;
		}
		#pragma GCC diagnostic pop

		// Configura el registre OSPEEDR (Output Speed Register)
		//
		uint32_t temp = regs->OSPEEDR;
		temp &= ~(0b11 << (pn * 2));
		temp |= value << (pn * 2);
		regs->OSPEEDR = temp;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la opcio pull.
/// \param    regs: El bloc de registres.
/// \param    pn: El numero de pin.
/// \param    pull: El pull a seleccionar.
///
static void setPull(
	GPIO_TypeDef *regs,
	uint32_t pn,
	GPIOPull pull) {

	if (pull != GPIOPull::noChange) {

		uint32_t value = 0; // Per defecte sense PU/PD

		#pragma GCC diagnostic push
		#pragma GCC diagnostic ignored "-Wswitch"
		switch (pull) {
			case GPIOPull::down:
				value = 2;
				break;

			case GPIOPull::up:
				value = 1;
				break;
		}
		#pragma GCC diagnostic pop

		// Configura el registre PUPDR (Pull Up/Down Register)
		//
		uint32_t temp = regs->PUPDR;
		temp &= ~(0b11 << (pn * 2));
		temp |= value << (pn * 2);
		regs->PUPDR = temp;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com a entrada.
/// \param    regs: Bloc de registres.
/// \param    pn: Numero de pin.
/// \param    pull: Opcions pull up/down.
///
void htl::GPIO_initInput(
    GPIO_TypeDef *regs,
    uint32_t pn,
    GPIOPull pull) {

    uint32_t temp;

    // Configura el registre MODER (Mode Register)
    //
    temp = regs->MODER;
    temp &= ~(0b11 << (pn * 2));
    regs->MODER = temp;

    setPull(regs, pn, pull);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com a sortida.
/// \param    reg: Bloc de registres.
/// \param    pn: Numero de pin.
/// \param    driver: Opcions del driver.
/// \param    speed: Opcions de velocitat.

void htl::GPIO_initOutput(
    GPIO_TypeDef *regs,
    uint32_t pn,
    GPIODriver driver,
    GPIOSpeed speed) {

    // Configura el registre MODER (Mode Register)
    //
    uint32_t temp = regs->MODER;
    temp &= ~(0b11 << (pn * 2));
    temp |= 0b01 << (pn * 2);
    regs->MODER = temp;

    setDriver(regs, pn, driver);
    setSpeed(regs, pn, speed);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com a sortida alternativa.
/// \param    regs: Bloc de registres.
/// \param    pn: Numero de pin.
/// \param    driver: Opcions del driver de sortida.
/// \param    speed: Opcions de velocitat.
/// \param    alt: Funcio alternativa.
///
void htl::GPIO_initAlt(
    GPIO_TypeDef *regs,
    uint32_t pn,
    GPIODriver driver,
    GPIOSpeed speed,
    unsigned alt) {
        
    uint32_t temp;

    // Configura el registre MODER (Mode Register)
    //
    temp = regs->MODER;
    temp &= ~(0b11 << (pn * 2));
    temp |= 0b10 << (pn * 2);
    regs->MODER = temp;

    // Configura el registre OTYPER (Output Type Register)
    //
    setDriver(regs, pn, driver);
    setSpeed(regs, pn, speed);

    // Configura el registre AFR (Alternate Funcion Register)
    //
    temp = regs->AFR[pn >> 3];
    temp &= ~(0b1111 << ((pn & 0x07) * 4)) ;
    temp |= (alt & 0b1111) << ((pn & 0x07) * 4);
    regs->AFR[pn >> 3] = temp;
}
