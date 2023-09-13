#include "HAL/hal.h"
#include "HAL/STM32/halEXTI.h"


#define __VERIFY_LINE(line)  eosAssert((line >= HAL_EXTI_LINE_0) && (line <= HAL_EXTI_LINE_24))
#define __VERIFY_PORT(port)  eosAssert((port >= HAL_EXTI_PORT_A) && (port <= HAL_EXTI_PORT_K))


typedef struct {
	halEXTIInterruptFunction function;
	void *params;
} halEXTIData;

static halEXTIData callback[24] = {
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
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL},
	{ NULL, NULL}
};


/// ----------------------------------------------------------------------
/// \brief    Inicialitza una linia d'interrupcio externa.
/// \param    line: La linia.
/// \param    options: Opcions de configuracio.
///
static void setupLine(
	halEXTILine line,
	halEXTIOptions options) {

	__VERIFY_LINE(line);

	uint32_t temp;

	// Configura el registre EXTICR per asignar la linia al port
	//
	if (line <= HAL_EXTI_LINE_15) {

		uint32_t port = (options & HAL_EXTI_PORT_mask) >> HAL_EXTI_PORT_pos;
		__VERIFY_PORT(port);

		temp = SYSCFG->EXTICR[line >> 2];
		temp &= ~(((uint32_t)0x0F) << (4 * (line & 0x03)));
		temp |= ((uint32_t)(port) << (4 * (line & 0x03)));
		SYSCFG->EXTICR[line >> 2] = temp;
	}

    // Obte la mascara corresponent a la linia
    //
    uint32_t lineMsk = 1 << line;

	// Configura el registre IMR (Interrupt Mask Register);
	//
    if ((options & HAL_EXTI_MODE_mask) == HAL_EXTI_MODE_INT)
    	__set_bit_msk(EXTI->IMR, lineMsk);
    else
    	__clear_bit_msk(EXTI->IMR, lineMsk);

	// Configura el registre EMR (Event Mask Register);
	//
    if ((options & HAL_EXTI_MODE_mask) == HAL_EXTI_MODE_EVENT)
    	__set_bit_msk(EXTI->EMR, lineMsk);
    else
    	__clear_bit_msk(EXTI->EMR, lineMsk);

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if (((options & HAL_EXTI_TRIGGER_mask) == HAL_EXTI_TRIGGER_RISING) ||
		((options & HAL_EXTI_TRIGGER_mask) == HAL_EXTI_TRIGGER_CHANGING))
		__set_bit_msk(EXTI->RTSR, lineMsk);
	else
		__clear_bit_msk(EXTI->RTSR, lineMsk);

	// Configura el registre FTSR (Falling Trigger Selection Register)
	//
	if (((options & HAL_EXTI_TRIGGER_mask) == HAL_EXTI_TRIGGER_FALLING) ||
		((options & HAL_EXTI_TRIGGER_mask) == HAL_EXTI_TRIGGER_CHANGING))
		__set_bit_msk(EXTI->FTSR, lineMsk);
	else
		__clear_bit_msk(EXTI->FTSR, lineMsk);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza linies d'interrupcio externes.
/// \param    info: Llista de configuracio.
/// \param    count: Numero d'elements en la llista.
///
void halEXTIInitializeLines(
	const halEXTILineSettings *settings,
	uint32_t count) {

	eosAssert(settings != NULL);
	eosAssert(count > 0);

	// Activa el clock del modul EXTI
	//
	__set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
    __DSB();

	// Inicialitza els elements de la llista
	//
	for (int i = 0; i < count; i++) {

		const halEXTILineSettings *p = &settings[i];
		setupLine(p->line, p->options);

		if ((p->options & HAL_EXTI_MODE_mask) == HAL_EXTI_MODE_INT) {
			callback[p->line].function = p->isrFunction;
			callback[p->line].params = p->isrParams;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza una linia d'interrupcio externa.
/// \param    line: La linia.
/// \param    options: Les opcions.
///
void halEXTIInitializeLine(
	halEXTILine line,
	halEXTIOptions options) {

	// Activa el clock del modul EXTI
	//
	__set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
    __DSB();

    setupLine(line, options);
	callback[line].function = NULL;
	callback[line].params = NULL;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la funcio callback per gestionar les interrupcions
/// \param    line: Linea EXTI a configurar.
/// \param    function: La funcio.
/// \param    params: Parametres de la funcio.
///
void halEXTISetInterruptFunction(
	halEXTILine line,
	halEXTIInterruptFunction function,
	void *params) {

	__VERIFY_LINE(line);

	// Desactiva la interrupcio de la linea
	//
	bool state = halEXTIDisableInterrupt(line);

	callback[line].function = function;
	callback[line].params = params;

	// Restaura l'estat de la interrupcio de la linia
	//
	if (state)
		halEXTIEnableInterrupt(line);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la interrupcio en la linia especificada.
/// \param    line: La linia.
///
void halEXTIEnableInterrupt(
	halEXTILine line) {

	__VERIFY_LINE(line);

	__set_bit_pos(EXTI->IMR, line);
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita la interrupcio en la linia especificada.
/// \param    line: La linia.
/// \retrurn  state: Estat previ de la interrupcio.
///
bool halEXTIDisableInterrupt(
	halEXTILine line) {

	__VERIFY_LINE(line);

	bool state = __check_bit_pos(EXTI->IMR, line);

	__clear_bit_pos(EXTI->IMR, line);

	return state;
}


/// ----------------------------------------------------------------------
/// \brief Crida a la funcio callback.
/// \param line: Linea EXTI que ha generat la interrupcio.
///
static inline void IRQHandler(
	halEXTILine line) {

	__VERIFY_LINE(line);

	if (callback[line].function != NULL)
		callback[line].function(line, callback[line].params);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI0
///
void EXTI0_IRQHandler() {

	if (__check_bit_pos(EXTI->PR, HAL_EXTI_LINE_0)) {
		IRQHandler(HAL_EXTI_LINE_0);
		__clear_bit_pos(EXTI->PR, HAL_EXTI_LINE_0);
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI1
///
void EXTI1_IRQHandler() {

	if (__check_bit_pos(EXTI->PR, HAL_EXTI_LINE_1)) {
		IRQHandler(HAL_EXTI_LINE_1);
		__clear_bit_pos(EXTI->PR, HAL_EXTI_LINE_1);
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI2
///
void EXTI2_IRQHandler() {

	if (__check_bit_pos(EXTI->PR, HAL_EXTI_LINE_2)) {
		IRQHandler(HAL_EXTI_LINE_2);
		__clear_bit_pos(EXTI->PR, HAL_EXTI_LINE_2);
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI3
///
void EXTI3_IRQHandler() {

	if (__check_bit_pos(EXTI->PR, HAL_EXTI_LINE_3)) {
		IRQHandler(HAL_EXTI_LINE_3);
		__clear_bit_pos(EXTI->PR, HAL_EXTI_LINE_3);
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI4
///
void EXTI4_IRQHandler() {

	if (__check_bit_pos(EXTI->PR, HAL_EXTI_LINE_4)) {
		IRQHandler(HAL_EXTI_LINE_4);
		__clear_bit_pos(EXTI->PR, HAL_EXTI_LINE_4);
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI5 fins EXTI9
///
void EXTI9_5_IRQHandler() {

	// Obte les interrupcions pendents
	//
	uint32_t pending = EXTI->PR & 0x000003E0;
    if (pending != 0) {

		if (__check_bit_pos(pending, HAL_EXTI_LINE_5))
			IRQHandler(HAL_EXTI_LINE_5);

		if (__check_bit_pos(pending, HAL_EXTI_LINE_6))
			IRQHandler(HAL_EXTI_LINE_6);

		if (__check_bit_pos(pending, HAL_EXTI_LINE_7))
			IRQHandler(HAL_EXTI_LINE_7);

		if (__check_bit_pos(pending, HAL_EXTI_LINE_8))
			IRQHandler(HAL_EXTI_LINE_8);

		if (__check_bit_pos(pending, HAL_EXTI_LINE_9))
			IRQHandler(HAL_EXTI_LINE_9);

		// Borra les interrupcions pendents
		//
		EXTI->PR = pending;
    }
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI10 fins EXTI15
///
void EXTI15_10_IRQHandler() {

	// Obte les interrupcions pendents
	//
	uint32_t pending = EXTI->PR & 0x0000FC00;
    if (pending != 0) {

    	if (__check_bit_pos(pending, HAL_EXTI_LINE_10))
    		IRQHandler(HAL_EXTI_LINE_10);

    	if (__check_bit_pos(pending, HAL_EXTI_LINE_11))
    		IRQHandler(HAL_EXTI_LINE_11);

    	if (__check_bit_pos(pending, HAL_EXTI_LINE_12))
    		IRQHandler(HAL_EXTI_LINE_12);

    	if (__check_bit_pos(pending, HAL_EXTI_LINE_13))
    		IRQHandler(HAL_EXTI_LINE_13);

    	if (__check_bit_pos(pending, HAL_EXTI_LINE_14))
    		IRQHandler(HAL_EXTI_LINE_14);

    	if (__check_bit_pos(pending, HAL_EXTI_LINE_15))
    		IRQHandler(HAL_EXTI_LINE_15);

		// Borra les interrupcions pendents
		//
    	EXTI->PR = pending;
    }
}


