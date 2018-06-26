#include "eos.h"
#include "eosAssert.h"
#include "hal/halGPIO.h"
#if defined(STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(STM32F7)
#include "stm32f7xx_hal.h"
#else
#error Hardware no soportado
#endif


GPIO_TypeDef * const gpioTbl[] = {
    GPIOA,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF,
	GPIOG,
	GPIOH,
	GPIOI,
	GPIOJ,
	GPIOK
};


// Taula de conversio HAL_GPIO_MODE_xxxx
//
static const uint32_t modeTbl[] = {
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT_PP,
	GPIO_MODE_OUTPUT_OD,
	GPIO_MODE_AF_PP,
	GPIO_MODE_AF_OD,
	GPIO_MODE_ANALOG,
	GPIO_MODE_IT_RISING,
	GPIO_MODE_IT_FALLING,
	GPIO_MODE_IT_RISING_FALLING
};

// Taula de conversio HAL_GPIO_SPEED
//
static const uint32_t speedTbl[] = {
	GPIO_SPEED_FREQ_LOW,
	GPIO_SPEED_FREQ_MEDIUM,
	GPIO_SPEED_FREQ_HIGH,
	GPIO_SPEED_FREQ_VERY_HIGH
};

// Taula de conversio HAL_GPIO_PULL
//
static const uint32_t pupdTbl[] = {
	GPIO_NOPULL,
	GPIO_PULLUP,
	GPIO_PULLDOWN
};


/// ----------------------------------------------------------------------
/// \brief Activa el rellotge del port GPIO
/// \param port: El identificador del port.
///
static void EnableClock(
	uint8_t port) {

	switch (port) {
		case HAL_GPIO_PORT_A:
			__HAL_RCC_GPIOA_CLK_ENABLE();
			break;

		case HAL_GPIO_PORT_B:
			__HAL_RCC_GPIOB_CLK_ENABLE();
			break;

		case HAL_GPIO_PORT_C:
			__HAL_RCC_GPIOC_CLK_ENABLE();
			break;

		case HAL_GPIO_PORT_D:
			__HAL_RCC_GPIOD_CLK_ENABLE();
			break;

		case HAL_GPIO_PORT_E:
			__HAL_RCC_GPIOE_CLK_ENABLE();
			break;

		case HAL_GPIO_PORT_F:
			__HAL_RCC_GPIOF_CLK_ENABLE();
			break;

		case HAL_GPIO_PORT_G:
			__HAL_RCC_GPIOG_CLK_ENABLE();
			break;

		case HAL_GPIO_PORT_H:
			__HAL_RCC_GPIOH_CLK_ENABLE();
			break;

		case HAL_GPIO_PORT_I:
			__HAL_RCC_GPIOI_CLK_ENABLE();
			break;

		case HAL_GPIO_PORT_J:
			__HAL_RCC_GPIOJ_CLK_ENABLE();
			break;

		case HAL_GPIO_PORT_K:
			__HAL_RCC_GPIOK_CLK_ENABLE();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Configura els parametres d'inicialitzacio.
/// \param pInfo: Informacio d'inicialitzacio.
/// \param init: Buffer on deixar els parametres d'inicialitzacio.
/// \return Adressa del buffer.
///
static GPIO_InitTypeDef *PreparePinInit(
	const GPIOInitializePinInfo *pInfo,
	GPIO_InitTypeDef *init) {

	init->Pin = 1 << pInfo->pin;
	init->Mode = modeTbl[(pInfo->options & HAL_GPIO_MODE_MASK) >> HAL_GPIO_MODE_POS];
	init->Speed = speedTbl[(pInfo->options & HAL_GPIO_SPEED_MASK) >> HAL_GPIO_SPEED_POS];
	init->Pull = pupdTbl[(pInfo->options & HAL_GPIO_PULL_MASK) >> HAL_GPIO_PULL_POS];
	init->Alternate = (uint32_t) pInfo->alt;

	return init;
}


/// ----------------------------------------------------------------------
/// \brief Configura els parametres d'inicialitzacio.
/// \param pInfo: Informacio d'inicialitzacio.
/// \param init: Buffer on deixar els parametres d'inicialitzacio.
/// \return Adressa del buffer.
///
static GPIO_InitTypeDef *PreparePortInit(
	const GPIOInitializePortInfo *pInfo,
	GPIO_InitTypeDef *init) {

	init->Pin = pInfo->mask;
	init->Mode = modeTbl[(pInfo->options & HAL_GPIO_MODE_MASK) >> HAL_GPIO_MODE_POS];
	init->Speed = speedTbl[(pInfo->options & HAL_GPIO_SPEED_MASK) >> HAL_GPIO_SPEED_POS];
	init->Pull = pupdTbl[(pInfo->options & HAL_GPIO_PULL_MASK) >> HAL_GPIO_PULL_POS];
	init->Alternate = (uint32_t) pInfo->alt;

	return init;
}


/// ----------------------------------------------------------------------
/// \brief Configura una llista de pins.
/// \param pInfo: Llista d'informacio de configuracio.
/// \param count: Numero d'elements de la llista.
///
void halGPIOInitializePins(
	const GPIOInitializePinInfo *pInfo,
	uint8_t count) {

	eosArgumentIsNotNull(pInfo);
	eosArgumentIsNotZero(count);

	for (uint8_t i = 0; i < count; i++) {

		const GPIOInitializePinInfo *p = &pInfo[i];

		EnableClock(p->port);

		GPIO_InitTypeDef gpioInit;
		PreparePinInit(p, &gpioInit);
		HAL_GPIO_Init(gpioTbl[p->port], &gpioInit);
	}
}


/// ----------------------------------------------------------------------
/// \brief Configura una llista de ports.
/// \param pInfo: Llista d'informacio de confiuguracio.
/// \param count: Numero d'elements de la llista.
///
void halGPIOInitializePorts(
	const GPIOInitializePortInfo *pInfo,
	uint8_t count) {

	eosArgumentIsNotNull(pInfo);
	eosArgumentIsNotZero(count);

	for (uint8_t i = 0; i < count; i++) {

		const GPIOInitializePortInfo *p = &pInfo[i];

		EnableClock(p->port);

		GPIO_InitTypeDef init;
		PreparePortInit(p, &init);
		HAL_GPIO_Init(gpioTbl[p->port], &init);
	}
}


/// ----------------------------------------------------------------------
/// \brief Configura un pin.
/// \param port: Identificador del port.
/// \param pin: Identificador del pin.
/// \param options: Opcions.
/// \param function: Funcio del pin.
///
void halGPIOInitializePin(
	GPIOPort port,
	GPIOPin pin,
	GPIOOptions options,
	GPIOAlt alt) {

	GPIOInitializePinInfo info;
	info.port = port;
	info.pin = pin;
	info.options = options;
	info.alt = alt;

	halGPIOInitializePins(&info, 1);
}
