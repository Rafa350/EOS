#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halTMR.h"


#define __VERIFY_TIMER(timer)     eosAssert((timer >= HAL_TMR_TIMER_1) && (timer <= HAL_TMR_TIMER_14))
#define __VERIFY_DEVICE(device)   eosAssert(IS_TIM_INSTANCE(device))


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
            RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			__DSB();
			break;

		case TIM2_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
			__DSB();
			break;

		case TIM3_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
			__DSB();
			break;

		case TIM4_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
			__DSB();
			break;

		case TIM5_BASE:
            RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
			__DSB();
			break;

		case TIM6_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
			__DSB();
			break;

		case TIM7_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
			__DSB();
			break;

		case TIM8_BASE:
			RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
			__DSB();
			break;

		case TIM9_BASE:
			RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
			__DSB();
			break;

		case TIM10_BASE:
			RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
			__DSB();
			break;

		case TIM11_BASE:
			RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
			__DSB();
			break;

		case TIM12_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
			__DSB();
			break;

		case TIM13_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
			__DSB();
			break;

		case TIM14_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
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
            RCC->APB2ENR &= ~(RCC_APB2ENR_TIM1EN);
			break;

		case TIM2_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN);
			break;

		case TIM3_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN);
			break;

		case TIM4_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN);
			break;

		case TIM5_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM5EN);
			break;

		case TIM6_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM6EN);
			break;

		case TIM7_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM7EN);
			break;

		case TIM8_BASE:
			RCC->APB2ENR &= ~(RCC_APB2ENR_TIM8EN);
			break;

		case TIM9_BASE:
			RCC->APB2ENR &= ~(RCC_APB2ENR_TIM9EN);
			break;

		case TIM10_BASE:
			RCC->APB2ENR &= ~(RCC_APB2ENR_TIM10EN);
			break;

		case TIM11_BASE:
			RCC->APB2ENR &= ~(RCC_APB2ENR_TIM11EN);
			break;

		case TIM12_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM12EN);
			break;

		case TIM13_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM13EN);
			break;

		case TIM14_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM14EN);
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
	const TMRInitializeInfo* info) {

	TIM_TypeDef* device = getDevice(info->timer);

	enableDeviceClock(device);

	uint32_t temp;

	// Configura el registre CR1 (Control 1)
	//
	temp = device->CR1;
	temp &= ~(TIM_CR1_CEN);                 // Para el timer

	if (IS_TIM_CLOCK_DIVISION_INSTANCE(device)) {
		temp &= ~(TIM_CR1_CKD); 			// Divisor per 1 per defecte
		switch ((info->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos) {
			case HAL_TMR_CLKDIV_2:
				temp |= TIM_CR1_CKD_0;      // Divisor per 2
				break;

			case HAL_TMR_CLKDIV_4:          // Divisor per 4
				temp |= TIM_CR1_CKD_1;
				break;
		}
	}

	if ((info->options & HAL_TMR_DIRECTION_mask) == HAL_TMR_DIRECTION_DOWN)
		temp |= TIM_CR1_DIR;                // Conta cap avall

	device->CR1 = temp;

	// Configura el registre PSC (Prescaler)
	//
	device->PSC = info->prescaler;

	// Configura el registre ARR (Periode)
	//
	device->ARR = info->period;


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

	eosAssert(handler != NULL);

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

	eosAssert(handler != NULL);

	handler->device->CR1 |= TIM_CR1_CEN;      // Activa el temporitzador.
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el temporitzador.
/// \param    handler: Handler del temporitzador.
///
void halTMRStopTimer(
	TMRHandler handler) {

	eosAssert(handler != NULL);

	handler->device->CR1 &= ~TIM_CR1_CEN;     // Desactiva el temporitzador
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

	eosAssert(handler != NULL);

	handler->isrFunction = function;
	handler->isrParams = params;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa las interrupcions del temporitzador.
/// \param    handler: Handler del temporitzador.
///
void halTMRInterruptHandler(
	TMRHandler handler) {

	eosAssert(handler != NULL);

	TIM_TypeDef* device = handler->device;

	// Comprova si es un event UPDATE
	//
	if ((device->SR & TIM_SR_UIF) == TIM_SR_UIF) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams);
		device->SR &= ~TIM_SR_UIF;
	}

	// Comprova si es un event TRIGGER
	//
	if ((device->SR & TIM_SR_TIF) == TIM_SR_TIF) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams);
		device->SR &= ~TIM_SR_TIF;
	}

	// Comprova si es un event COM
	//
	if ((device->SR & TIM_SR_COMIF) == TIM_SR_COMIF) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams);
		device->SR &= ~TIM_SR_COMIF;
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

	uint32_t temp = handler->device->DIER;

	if ((events & HAL_TMR_EVENT_UP) == HAL_TMR_EVENT_UP)
		temp |= TIM_DIER_UIE;
	if ((events & HAL_TMR_EVENT_TRG) == HAL_TMR_EVENT_TRG)
		temp |= TIM_DIER_TIE;
	if ((events & HAL_TMR_EVENT_COM) == HAL_TMR_EVENT_COM)
		temp |= TIM_DIER_COMIE;

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

	uint32_t temp = handler->device->DIER;

	uint32_t enabled = 0;
	if ((temp & TIM_DIER_UIE) == TIM_DIER_UIE)
		enabled |= HAL_TMR_EVENT_UP;
	if ((temp & TIM_DIER_UIE) == TIM_DIER_TIE)
		enabled |= HAL_TMR_EVENT_TRG;
	if ((temp & TIM_DIER_UIE) == TIM_DIER_COMIE)
		enabled |= HAL_TMR_EVENT_COM;

	if ((events & HAL_TMR_EVENT_UP) == HAL_TMR_EVENT_UP)
		temp &= ~TIM_DIER_UIE;
	if ((events & HAL_TMR_EVENT_TRG) == HAL_TMR_EVENT_TRG)
		temp &= ~TIM_DIER_TIE;
	if ((events & HAL_TMR_EVENT_COM) == HAL_TMR_EVENT_COM)
		temp &= ~TIM_DIER_COMIE;

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

	TIM_TypeDef* device = handler->device;

	if ((events & HAL_TMR_EVENT_UP) == HAL_TMR_EVENT_UP)
		device->SR &= ~TIM_SR_UIF;

	if ((events & HAL_TMR_EVENT_TRG) == HAL_TMR_EVENT_TRG)
		device->SR &= ~TIM_SR_TIF;

	if ((events & HAL_TMR_EVENT_COM) == HAL_TMR_EVENT_COM)
		device->SR &= ~TIM_SR_COMIF;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del indicador d'interrupcio del temporitzador.
/// \param    handler: Handler del tempositzador.
/// \param    event: Identificador del event
/// \return   El valor del indicador.
///
bool halTMRGetInterruptFlag(
	TMRHandler handler,
	uint32_t event) {

	TIM_TypeDef* device = handler->device;

	switch (event) {
		case HAL_TMR_EVENT_UP:
			return (device->SR & TIM_SR_UIF) == TIM_SR_UIF;

		case HAL_TMR_EVENT_TRG:
			return (device->SR & TIM_SR_TIF) == TIM_SR_TIF;

		case HAL_TMR_EVENT_COM:
			return (device->SR & TIM_SR_COMIF) == TIM_SR_COMIF;

		default:
			return false;
	}
}
