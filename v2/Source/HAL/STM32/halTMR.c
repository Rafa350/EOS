#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halTMR.h"


#define __VERIFY_TIMER(timer)     eosAssert((timer >= HAL_TMR_TIMER_1) && (timer <= HAL_TMR_TIMER_14))
#define __VERIFY_DEVICE(device)   eosAssert(IS_TIM_INSTANCE(device))
#define __VERIFY_HANDLER(timer)   eosAssert(handler != NULL)


/// ----------------------------------------------------------------------
/// \brief    Obte el dispositiu.
/// \param    channel: El identificador del dispositiu.
/// \return   El dispositiu.
///
static inline TIM_TypeDef* getDevice(
	TMRTimer timer) {

	__VERIFY_TIMER(timer);

	static TIM_TypeDef* const devices[] = {
		TIM1,
		TIM2,
		TIM3,
		TIM4,
		TIM5,
		TIM6,
		TIM7,
		TIM8,
		TIM9,
		TIM10,
		TIM11,
		TIM12,
		TIM13,
		TIM14
	};

	return devices[timer];
}


/// ----------------------------------------------------------------------
/// \brief    Activa el dispositiu.
/// \param    device: El dispositiu.
///
static void enableDeviceClock(
	TIM_TypeDef* device) {

	__VERIFY_DEVICE(device);

	switch ((uint32_t) device) {
		case TIM1_BASE:
            __set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
			__DSB();
			break;

		case TIM2_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
			__DSB();
			break;

		case TIM3_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
			__DSB();
			break;

		case TIM4_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);
			__DSB();
			break;

		case TIM5_BASE:
            __set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM5EN);
			__DSB();
			break;

		case TIM6_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);
			__DSB();
			break;

		case TIM7_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM7EN);
			__DSB();
			break;

		case TIM8_BASE:
			__set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);
			__DSB();
			break;

		case TIM9_BASE:
			__set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_TIM9EN);
			__DSB();
			break;

		case TIM10_BASE:
			__set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);
			__DSB();
			break;

		case TIM11_BASE:
			__set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_TIM11EN);
			__DSB();
			break;

		case TIM12_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM12EN);
			__DSB();
			break;

		case TIM13_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM13EN);
			__DSB();
			break;

		case TIM14_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);
			__DSB();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el dispositiu.
/// \param    device: El dispositiu.
///
static void disableDeviceClock(
	TIM_TypeDef* device) {

	__VERIFY_DEVICE(device);

	switch ((uint32_t) device) {
		case TIM1_BASE:
            __clear_bit_msk(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
			break;

		case TIM2_BASE:
			__clear_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
			break;

		case TIM3_BASE:
			__clear_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
			break;

		case TIM4_BASE:
			__clear_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);
			break;

		case TIM5_BASE:
			__clear_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM5EN);
			break;

		case TIM6_BASE:
			__clear_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);
			break;

		case TIM7_BASE:
			__clear_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM7EN);
			break;

		case TIM8_BASE:
			__clear_bit_msk(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);
			break;

		case TIM9_BASE:
			__clear_bit_msk(RCC->APB2ENR, RCC_APB2ENR_TIM9EN);
			break;

		case TIM10_BASE:
			__clear_bit_msk(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);
			break;

		case TIM11_BASE:
			__clear_bit_msk(RCC->APB2ENR, RCC_APB2ENR_TIM11EN);
			break;

		case TIM12_BASE:
			__clear_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM12EN);
			break;

		case TIM13_BASE:
			__clear_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM13EN);
			break;

		case TIM14_BASE:
			__clear_bit_msk(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el handler del temporitzador.
/// \param    data: Bloc de memoria pel handler del temporitzador.
/// \param    info: Parametres d'inicialitzacio.
/// \return   El handler del temporitzador.
///
TMRHandler halTMRInitialize(
	TMRData* data,
	const TMRSettings *settings) {

	eosAssert(data !=NULL);
	eosAssert(settings != NULL);

	TIM_TypeDef* device = getDevice(settings->timer);

	enableDeviceClock(device);
	__clear_bit_msk(device->CR1, TIM_CR1_CEN);                 // Para el timer

	uint32_t temp;

	// Configura el registre CR1 (Control 1)
	//
	temp = device->CR1;

	if (IS_TIM_CLOCK_DIVISION_INSTANCE(device)) {
		__clear_bit_msk(temp, TIM_CR1_CKD); 			// Divisor per 1 per defecte
		switch ((settings->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos) {
			case HAL_TMR_CLKDIV_2:
				__set_bit_msk(temp, TIM_CR1_CKD_0);     // Divisor per 2
				break;

			case HAL_TMR_CLKDIV_4:
				__set_bit_msk(temp, TIM_CR1_CKD_1);     // Divisor per 4
				break;
		}
	}

	if ((settings->options & HAL_TMR_DIRECTION_mask) == HAL_TMR_DIRECTION_DOWN)
		__set_bit_msk(temp, TIM_CR1_DIR);               // Conta cap avall

	device->CR1 = temp;

	// Configura el registre PSC (Prescaler)
	//
	device->PSC = settings->prescaler;

	// Configura el registre ARR (Periode)
	//
	device->ARR = settings->period;

	TMRHandler handler = data;
	handler->device = device;
	handler->isrFunction = NULL;
	handler->isrParams = NULL;

	return handler;
}


/// ----------------------------------------------------------------------
/// \brief    Desactivacio del temporitzador.
/// \param    handler: Handler del temporitzador.
///
void halTMRDeinitialize(
	TMRHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	halTMRStopTimer(handler);
	halTMRDisableInterrupts(handler, HAL_TMR_EVENT_ALL);

	disableDeviceClock(handler->device);
}


/// ----------------------------------------------------------------------
/// \brief    Activa el temporitzador.
/// \param    handler: Handler del temporitzador.
///
void halTMRStartTimer(
	TMRHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	__set_bit_msk(handler->device->CR1, TIM_CR1_CEN);      // Activa el temporitzador.
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el temporitzador.
/// \param    handler: Handler del temporitzador.
///
void halTMRStopTimer(
	TMRHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	__clear_bit_msk(handler->device->CR1, TIM_CR1_CEN);    // Desactiva el temporitzador
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la funcio de gestion de la interrupcio.
/// \param    handler: Handler del temporitzador.
/// \param    function: La funcio.
/// \param    params: El parametre.
///
void halTMRSetInterruptFunction(
	TMRHandler handler,
	TMRInterruptFunction function,
	void* params) {

	__VERIFY_HANDLER(handler);

	// Desabilita les interrupcions temportalment
	//
	uint32_t state = halTMRDisableInterrupts(handler, HAL_TMR_EVENT_ALL);

	handler->isrFunction = function;
	handler->isrParams = params;

	// Restaura les interrupcions
	//
	if (state != 0)
		halTMREnableInterrupts(handler, state);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa las interrupcions del temporitzador.
/// \param    handler: Handler del temporitzador.
///
void halTMRInterruptHandler(
	TMRHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	TIM_TypeDef* device = handler->device;

	// Comprova si es un event UPDATE
	//
	if (__check_bit_msk(device->SR, TIM_SR_UIF)) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams, HAL_TMR_EVENT_UPDATE);
		__clear_bit_msk(device->SR, TIM_SR_UIF);
	}

	// Comprova si es un event TRIGGER
	//
	if (__check_bit_msk(device->SR, TIM_SR_TIF)) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams, HAL_TMR_EVENT_TRIGGER);
		__clear_bit_msk(device->SR, TIM_SR_TIF);
	}

	// Comprova si es un event COM
	//
	if (__check_bit_msk(device->SR, TIM_SR_COMIF)) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams, HAL_TMR_EVENT_COM);
		__clear_bit_msk(device->SR, TIM_SR_COMIF);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions del temporitzador.
/// \param    handler: Handler del temporitzador.
/// \param    events: Events a activar.
///
void halTMREnableInterrupts(
	TMRHandler handler,
	uint32_t events) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	uint32_t temp = handler->device->DIER;

	if (__check_bit_msk(events, HAL_TMR_EVENT_UPDATE))
		__set_bit_msk(temp, TIM_DIER_UIE);

	if (__check_bit_msk(events, HAL_TMR_EVENT_TRIGGER))
		__set_bit_msk(temp, TIM_DIER_TIE);

	if (__check_bit_msk(events, HAL_TMR_EVENT_COM))
		__set_bit_msk(temp, TIM_DIER_COMIE);

	handler->device->DIER = temp;
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita les interrupcions del temporitzador.
/// \param    handler: Handler del temporitzador.
/// \param    events: Events a desactivar.
/// \return   Els events previament actius.
///
uint32_t halTMRDisableInterrupts(
	TMRHandler handler,
	uint32_t events) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	uint32_t temp = handler->device->DIER;
	uint32_t enabled = 0;

	// Recupera l'estat d'habilitacio de les interrupcions
	//
	if (__check_bit_msk(temp, TIM_DIER_UIE))
		__set_bit_msk(enabled, HAL_TMR_EVENT_UPDATE);

	if (__check_bit_msk(temp, TIM_DIER_TIE))
		__set_bit_msk(enabled, HAL_TMR_EVENT_TRIGGER);

	if (__check_bit_msk(temp, TIM_DIER_COMIE))
		__set_bit_msk(enabled, HAL_TMR_EVENT_COM);

	// Desabilita les interrupcions
	//
	if (__check_bit_msk(events, HAL_TMR_EVENT_UPDATE))
		__clear_bit_msk(temp, TIM_DIER_UIE);

	if (__check_bit_msk(events, HAL_TMR_EVENT_TRIGGER))
		__clear_bit_msk(temp, TIM_DIER_TIE);

	if (__check_bit_msk(events, HAL_TMR_EVENT_COM))
		__clear_bit_msk(temp, TIM_DIER_COMIE);

	handler->device->DIER = temp;

	return enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Borra el indicador d'interrupcio del temporitzador.
/// \param    handler: Handler del temporitzador.
/// \return   Valor del indicador.
///
void halTMRClearInterruptFlags(
	TMRHandler handler,
	uint32_t events) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	TIM_TypeDef* device = handler->device;

	if (__check_bit_msk(events, HAL_TMR_EVENT_UPDATE))
		__clear_bit_msk(device->SR, TIM_SR_UIF);

	if (__check_bit_msk(events, HAL_TMR_EVENT_TRIGGER))
		__clear_bit_msk(device->SR, TIM_SR_TIF);

	if (__check_bit_msk(events, HAL_TMR_EVENT_COM))
		__clear_bit_msk(device->SR, TIM_SR_COMIF);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del indicador d'interrupcio del temporitzador.
/// \param    handler: Handler del temporitzador.
/// \param    event: Identificador del event
/// \return   El valor del indicador.
///
bool halTMRGetInterruptFlag(
	TMRHandler handler,
	uint32_t event) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	TIM_TypeDef* device = handler->device;

	switch (event) {
		case HAL_TMR_EVENT_UPDATE:
			return __check_bit_msk(device->SR, TIM_SR_UIF);

		case HAL_TMR_EVENT_TRIGGER:
			return __check_bit_msk(device->SR, TIM_SR_TIF);

		case HAL_TMR_EVENT_COM:
			return __check_bit_msk(device->SR, TIM_SR_COMIF);

		default:
			return false;
	}
}
