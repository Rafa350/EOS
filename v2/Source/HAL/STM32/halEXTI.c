#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halEXTI.h"


typedef struct {
	EXTICallbackFunction function;
	void *pParam;
} CallbackInfo;

static CallbackInfo callback[16] = {
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL}
};

static CallbackInfo globalCallback = {
	NULL, NULL
};



/// ----------------------------------------------------------------------
/// \brief Inicialitza un pin per que generi interrupcions
/// \param port: El port.
/// \param pin: El pin.
/// \param options: Opcions de configuracio.
///
static void setupPin(
	GPIOPort port,
	GPIOPin pin,
	EXTIOptions options) {

	eosAssert((port >= HAL_GPIO_PORT_A) && (port <= HAL_GPIO_PORT_K));
	eosAssert((pin >= HAL_GPIO_PIN_0) && (pin <= HAL_GPIO_PIN_15));

	uint32_t temp;

	// Configura el registre EXTICR per mepejar la linia amb el pin GPIO
	//
    temp = SYSCFG->EXTICR[pin >> 2];
    temp &= ~(((uint32_t)0x0F) << (4 * (pin & 0x03)));
    temp |= ((uint32_t)(port) << (4 * (pin & 0x03)));
    SYSCFG->EXTICR[pin >> 2] = temp;

    uint32_t pinMask = 1 << pin;

	// Configura el registre IMR (Interrupt Mask Register);
	//
    if ((options & HAL_EXTI_MODE_mask) == HAL_EXTI_MODE_INT)
    	EXTI->IMR |= pinMask;
    else
    	EXTI->IMR &= ~pinMask;

	// Configura el registre EMR (Event Mask Register);
	//
    if ((options & HAL_EXTI_MODE_mask) == HAL_EXTI_MODE_EVENT)
    	EXTI->EMR |= pinMask;
    else
    	EXTI->EMR &= ~pinMask;

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if (((options & HAL_EXTI_TRIGGER_mask) == HAL_EXTI_TRIGGER_RISING) ||
		((options & HAL_EXTI_TRIGGER_mask) == HAL_EXTI_TRIGGER_CHANGING))
		EXTI->RTSR |= pinMask;
	else
		EXTI->RTSR &= ~pinMask;

	// Configura el registre FTSR (Falling Trigger Selection Register)
	//
	if (((options & HAL_EXTI_TRIGGER_mask) == HAL_EXTI_TRIGGER_FALLING) ||
		((options & HAL_EXTI_TRIGGER_mask) == HAL_EXTI_TRIGGER_CHANGING))
		EXTI->FTSR |= pinMask;
	else
		EXTI->FTSR &= ~pinMask;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza els pins per generar interrupcions o events.
/// \param pInfo: Llista de configuracio.
/// \param count: Numero d'elements en la llista.
///
void halEXTIInitializePins(
	const EXTIInitializePinInfo *pInfo,
	unsigned count) {

	eosAssert(pInfo != NULL);
	eosAssert(count > 0);

	// Activa el clock del modul EXTI
	//
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Inicialitza els elements de la llista
	//
	for (unsigned i = 0; i < count; i++) {
		const EXTIInitializePinInfo *p = &pInfo[i];
		setupPin(p->port, p->pin, p->options);
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna la funcio callback per gestionar les interrupcions
/// \param line: Linea EXTI a configurar.
/// \param function: La funcio.
///
void halEXTISetCallbackFunction(
	EXTILine line,
	EXTICallbackFunction function,
	void *pParam) {

	eosAssert((line >= HAL_EXTI_LINE_0) && (line <= HAL_EXTI_LINE_15));

	callback[line].function = function;
	callback[line].pParam = pParam;
}


/// ----------------------------------------------------------------------
/// \brief Crida a la funcio callback.
/// \param line: Linea EXTI que ha generat la interrupcio.
///
static inline void IRQHandler(
	EXTILine line) {

	if (globalCallback.function != NULL)
		globalCallback.function(line, globalCallback.pParam);

	if (callback[line].function != NULL)
		callback[line].function(line, callback[line].pParam);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI0
///
void EXTI0_IRQHandler() {

	IRQHandler(HAL_EXTI_LINE_0);

	// Borra les interrupcions pendents
	//
	EXTI->PR |= 1 << HAL_EXTI_LINE_0;
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI1
///
void EXTI1_IRQHandler() {

	IRQHandler(HAL_EXTI_LINE_1);

	// Borra les interrupcions pendents
	//
	EXTI->PR |= 1 << HAL_EXTI_LINE_1;
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI2
///
void EXTI2_IRQHandler() {

	IRQHandler(HAL_EXTI_LINE_2);

	// Borra les interrupcions pendents
	//
	EXTI->PR |= 1 << HAL_EXTI_LINE_2;
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI3
///
void EXTI3_IRQHandler() {

	IRQHandler(HAL_EXTI_LINE_3);

	// Borra les interrupcions pendents
	//
	EXTI->PR |= 1 << HAL_EXTI_LINE_3;
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI4
///
void EXTI4_IRQHandler() {

	IRQHandler(HAL_EXTI_LINE_4);

	// Borra les interrupcions pendents
	//
	EXTI->PR |= 1 << HAL_EXTI_LINE_4;
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI5 fins EXTI9
///
void EXTI9_5_IRQHandler() {

	// Obte les interrupcions pendents
	//
	uint32_t pending = EXTI->PR & 0x000003E0;

	if (pending == 1 << HAL_EXTI_LINE_5)
		IRQHandler(HAL_EXTI_LINE_5);
	if (pending == 1 << HAL_EXTI_LINE_6)
		IRQHandler(HAL_EXTI_LINE_6);
	if (pending == 1 << HAL_EXTI_LINE_7)
		IRQHandler(HAL_EXTI_LINE_7);
	if (pending == 1 << HAL_EXTI_LINE_8)
		IRQHandler(HAL_EXTI_LINE_8);
	if (pending == 1 << HAL_EXTI_LINE_9)
		IRQHandler(HAL_EXTI_LINE_9);

	// Borra les interrupcions pendents
	//
    EXTI->PR |= pending;
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI10 fins EXTI15
///
void EXTI15_10_IRQHandler() {

	// Obte les interrupcions pendents
	//
	uint32_t pending = EXTI->PR & 0x0000FC00;

	if (pending == 1 << HAL_EXTI_LINE_10)
		IRQHandler(HAL_EXTI_LINE_10);
	if (pending == 1 << HAL_EXTI_LINE_11)
		IRQHandler(HAL_EXTI_LINE_11);
	if (pending == 1 << HAL_EXTI_LINE_12)
		IRQHandler(HAL_EXTI_LINE_12);
	if (pending == 1 << HAL_EXTI_LINE_13)
		IRQHandler(HAL_EXTI_LINE_13);
	if (pending == 1 << HAL_EXTI_LINE_14)
		IRQHandler(HAL_EXTI_LINE_14);
	if (pending == 1 << HAL_EXTI_LINE_15)
		IRQHandler(HAL_EXTI_LINE_15);

	EXTI->PR |= pending;
}
