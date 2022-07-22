#include "eos.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;


static uint16_t __enableA = 0;
static uint16_t __enableB = 0;
static uint16_t __enableC = 0;
static uint16_t __enableD = 0;
static uint16_t __enableE = 0;
static uint16_t __enableF = 0;
static uint16_t __enableG = 0;
static uint16_t __enableH = 0;
static uint16_t __enableI = 0;
static uint16_t __enableJ = 0;
static uint16_t __enableK = 0;


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge del modul GPIO
/// \param    regs: El bloc de registres.
/// \param    pn: El numero de pin.
///
static void enableClock(
	GPIO_TypeDef *regs,
	uint32_t pn) {

	switch (uint32_t(regs)) {
		case GPIOA_BASE:
			if (!__enableA)
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
			__enableA |= 1 << pn;
			break;

		case GPIOB_BASE:
			if (!__enableB)
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
			__enableB |= 1 << pn;
			break;

		case GPIOC_BASE:
			if (!__enableC)
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
			__enableC |= 1 << pn;
			break;

		case GPIOD_BASE:
			if (!__enableD)
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
			__enableD |= 1 << pn;
			break;

		case GPIOE_BASE:
			if (!__enableE)
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
			__enableE |= 1 << pn;
			break;

		case GPIOF_BASE:
			if (!__enableF)
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
			__enableF |= 1 << pn;
			break;

		case GPIOG_BASE:
			if (!__enableG)
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
			__enableG |= 1 << pn;
			break;

		case GPIOH_BASE:
			if (!__enableH)
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
			__enableH |= 1 << pn;
			break;

		case GPIOI_BASE:
			if (!__enableI)
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
			__enableI |= 1 << pn;
			break;

		case GPIOJ_BASE:
			if (!__enableJ)
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
			__enableJ |= 1 << pn;
			break;

		case GPIOK_BASE:
			if (!__enableK)
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
			__enableK |= 1 << pn;
			break;
	}

	__DSB();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el rellotge del modul GPIO.
/// \param    regs: El bloc de registres.
/// \param    pn: El numero de pin.
///
static void disableClock(
	GPIO_TypeDef *reg,
	uint32_t pn) {

	switch (uint32_t(reg)) {
		case GPIOA_BASE:
			__enableA &= ~(1 << pn);
			if (!__enableA)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
			break;

		case GPIOB_BASE:
			__enableB &= ~(1 << pn);
			if (!__enableB)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
			break;

		case GPIOC_BASE:
			__enableC &= ~(1 << pn);
			if (!__enableC)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
			break;

		case GPIOD_BASE:
			__enableD &= ~(1 << pn);
			if (!__enableD)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
			break;

		case GPIOE_BASE:
			__enableE &= ~(1 << pn);
			if (!__enableE)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN;
			break;

		case GPIOF_BASE:
			__enableF &= ~(1 << pn);
			if (!__enableF)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOFEN;
			break;

		case GPIOG_BASE:
			__enableG &= ~(1 << pn);
			if (!__enableG)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOGEN;
			break;

		case GPIOH_BASE:
			__enableH &= ~(1 << pn);
			if (!__enableH)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN;
			break;

		case GPIOI_BASE:
			__enableI &= ~(1 << pn);
			if (!__enableI)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOIEN;
			break;

		case GPIOJ_BASE:
			__enableJ &= ~(1 << pn);
			if (!__enableJ)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOJEN;
			break;

		case GPIOK_BASE:
			__enableK &= ~(1 << pn);
			if (!__enableK)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOKEN;
			break;
	}
}


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

    // Activa el rellotge del port
    //
    enableClock(regs, pn);

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

    uint32_t temp;

    // Activa el rellotge del port
    //
    enableClock(regs, pn);

    // Configura el registre MODER (Mode Register)
    //
    temp = regs->MODER;
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

    // Activa el rellotge del port
    //
    enableClock(regs, pn);

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


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza un pin.
/// \param    regs: El bloc de registres.
/// \param    pin: El pin.
///
void htl::GPIO_deInit(
	GPIO_TypeDef *regs,
	uint32_t pn) {

    // Desactiva el rellotge del port
    //
	disableClock(regs, pn);
}
