#include "eos.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;


static uint32_t __enableA = 0;
static uint32_t __enableB = 0;
static uint32_t __enableC = 0;
static uint32_t __enableD = 0;
static uint32_t __enableE = 0;
static uint32_t __enableF = 0;
static uint32_t __enableG = 0;
static uint32_t __enableH = 0;
static uint32_t __enableI = 0;
static uint32_t __enableJ = 0;
static uint32_t __enableK = 0;


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


static void disableClock(
	GPIO_TypeDef *reg,
	uint32_t pn) {

	switch (uint32_t(reg)) {
		case GPIOA_BASE:
			__enableA &= ~(1 << pn);
			if (!__enableA)
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
			break;
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

    // Configura el registre PUPDR (Pull Up/Down Register)
    //
    temp = regs->PUPDR;
    temp &= ~(0b11 << (pn * 2));
    temp |= (uint32_t(pull) & 0x11) << (pn * 2);
    regs->PUPDR = temp;
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

    // Configura el registre OTYPER (Output Type Register)
    //
    temp = regs->OTYPER;
    temp &= ~(0b1 << pn);
    temp |= (uint32_t(driver) & 0b1) << pn;
    regs->OTYPER = temp;

    // Configura el registre OSPEEDR (Output Speed Register)
    //
    temp = regs->OSPEEDR;
    temp &= ~(0b11 << (pn * 2));
    temp |= (uint32_t(speed) & 0b11) << (pn * 2);
    regs->OSPEEDR = temp;
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
    temp = regs->OTYPER;
    temp &= ~(0b1 << pn);
    temp |= (uint32_t(driver) & 0b1) << pn;
    regs->OTYPER = temp;

    // Configura el registre OSPEEDR (Output Speed Register)
    //
    temp = regs->OSPEEDR;
    temp &= ~(0b11 << (pn * 2));
    temp |= (uint32_t(speed) & 0b11) << (pn * 2);
    regs->OSPEEDR = temp;

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
