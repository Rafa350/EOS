#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halTMR.h"
#include "HAL/STM32/halINT.h"

// TODO
// Eliminar les referencies a la llibreria HAL


typedef struct {
	TIM_HandleTypeDef handle;
	TMRInterruptFunction isrFunction;
	void* isrParams;
} TimerInfo;

static TimerInfo timerInfoTbl[HAL_TMR_TIMER_MAX];


/// ----------------------------------------------------------------------
/// \brief Activa el rellotge del temporitzador
/// \param[in] timer: Identificador del temporitzador.
///
static void enableClock(
	TMRTimer timer) {

	switch (timer) {
		case HAL_TMR_TIMER_1:
			__HAL_RCC_TIM1_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_2:
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
			break;

		case HAL_TMR_TIMER_3:
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
			break;

		case HAL_TMR_TIMER_4:
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
			break;

		case HAL_TMR_TIMER_5:
			__HAL_RCC_TIM5_CLK_ENABLE();
			break;

#ifdef HAL_TMR_TIMER_6
		case HAL_TMR_TIMER_6:
			__HAL_RCC_TIM6_CLK_ENABLE();
			break;
#endif

		case HAL_TMR_TIMER_7:
			__HAL_RCC_TIM7_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_8:
			__HAL_RCC_TIM8_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_9:
			__HAL_RCC_TIM9_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_10:
			__HAL_RCC_TIM10_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_11:
			__HAL_RCC_TIM11_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_12:
			__HAL_RCC_TIM12_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_13:
			__HAL_RCC_TIM13_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_14:
			__HAL_RCC_TIM14_CLK_ENABLE();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el rellotge del temporitzador
/// \param timer: Identificador del temporitzador.
///
static void disableClock(
	TMRTimer timer) {

	switch (timer) {
		case HAL_TMR_TIMER_1:
			__HAL_RCC_TIM1_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_2:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN);
			break;

		case HAL_TMR_TIMER_3:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN);
			break;

		case HAL_TMR_TIMER_4:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN);
			break;

		case HAL_TMR_TIMER_5:
			__HAL_RCC_TIM5_CLK_DISABLE();
			break;

#ifdef HAL_TMR_TIMER_6
		case HAL_TMR_TIMER_6:
			__HAL_RCC_TIM6_CLK_DISABLE();
			break;
#endif

		case HAL_TMR_TIMER_7:
			__HAL_RCC_TIM7_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_8:
			__HAL_RCC_TIM8_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_9:
			__HAL_RCC_TIM9_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_10:
			__HAL_RCC_TIM10_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_11:
			__HAL_RCC_TIM11_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_12:
			__HAL_RCC_TIM12_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_13:
			__HAL_RCC_TIM13_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_14:
			__HAL_RCC_TIM14_CLK_DISABLE();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Prepara el handle per inicialitzar.
/// \brief pHandle: El handle a inicialitzar.
/// \param pInfo: Parametres d'inicialitzacio.
///
static void prepareTimerHandle(
	TIM_HandleTypeDef* handle,
	const TMRInitializeInfo* info) {

	static TIM_TypeDef * const instances[] = {
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

	static const uint32_t clockDivision[] = {
        TIM_CLOCKDIVISION_DIV1,
        TIM_CLOCKDIVISION_DIV2,
        TIM_CLOCKDIVISION_DIV4
	};

	handle->Instance = instances[info->timer];
	handle->Init.CounterMode = TIM_COUNTERMODE_UP;
	handle->Init.ClockDivision = clockDivision[(info->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos];
	handle->Init.Prescaler = info->prescaler;
	handle->Init.Period = info->period;
	handle->Init.RepetitionCounter = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un temporitzador
/// \param    pInfo: Parametres d'inicialitzacio.
///
void halTMRInitialize(
	const TMRInitializeInfo* info) {

	// Precondicions
	//
	eosAssert(info != NULL);

	TMRTimer timer = info->timer;
	TimerInfo *timerInfo = &timerInfoTbl[timer];

	enableClock(timer);

	prepareTimerHandle(&timerInfo->handle, info);
	HAL_TIM_Base_Init(&timerInfo->handle);

	if ((info->options & HAL_TMR_INTERRUPT_mask) == HAL_TMR_INTERRUPT_ENABLE) {

		static const IRQn_Type irq[] = {
			0,
		    TIM2_IRQn,
			TIM3_IRQn,
			TIM4_IRQn
		};

		timerInfo->isrFunction = info->isrFunction;
		timerInfo->isrParams = info->isrParams;

		halINTSetPriority(irq[timer], info->irqPriority, info->irqSubPriority);
		halINTEnableIRQ(irq[timer]);
	}
	else
		timerInfo->isrFunction = NULL;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva un temporitzador
/// \param    id: Identificador del temporitzador.
///
void halTMRShutdown(
	TMRTimer timer) {

	TimerInfo *pTimerInfo = &timerInfoTbl[timer];

	HAL_TIM_Base_DeInit(&pTimerInfo->handle);

	disableClock(timer);
}


/// ----------------------------------------------------------------------
/// \brief    Posa en marxa el temporitzador i comen�a a contar.
/// \param    timer: El identificador del temporitzador.
///
void halTMRStartTimer(
	TMRTimer timer) {

	TimerInfo *timerInfo = &timerInfoTbl[timer];

	if (timerInfo->isrFunction != NULL)
		__HAL_TIM_ENABLE_IT(&timerInfo->handle, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE(&timerInfo->handle);
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    timer: El identificador del temporitzador.
///
void halTMRStopTimer(
	TMRTimer timer) {

	TimerInfo *timerInfo = &timerInfoTbl[timer];

	if (timerInfo->isrFunction != NULL)
		__HAL_TIM_DISABLE_IT(&timerInfo->handle, TIM_IT_UPDATE);
	__HAL_TIM_DISABLE(&timerInfo->handle);
}


/// ----------------------------------------------------------------------
/// \brief    Activa les interrupcions del temporitzador.
/// \param    timer: El temporitzador.
///
void halTMREnableInterrupt(
	TMRTimer timer) {

	TimerInfo *timerInfo = &timerInfoTbl[timer];
	__HAL_TIM_ENABLE_IT(&timerInfo->handle, TIM_IT_UPDATE);
}


/// ----------------------------------------------------------------------
/// \brief    Activa les interrupcions del temporitzador.
/// \param    timer: El temporitzador.
///
void halTMRDisableInterrupt(
	TMRTimer timer) {

	TimerInfo *timerInfo = &timerInfoTbl[timer];
	__HAL_TIM_DISABLE_IT(&timerInfo->handle, TIM_IT_UPDATE);
}


/// ----------------------------------------------------------------------
/// \brief    Retard en milisegons.
/// \param    time: Temps en milisegons.
///
void halTMRDelay(
    int time) {

	HAL_Delay(time);
}


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio.
/// \param    timer: Identificador del temporitzador.
///
static void IRQHandler(
	TMRTimer timer) {

	TimerInfo* timerInfo = &timerInfoTbl[timer];

	// Interrupcio UPDATE
	//
	if(__HAL_TIM_GET_FLAG(&timerInfo->handle, TIM_FLAG_UPDATE) != RESET) {
		if(__HAL_TIM_GET_IT_SOURCE(&timerInfo->handle, TIM_IT_UPDATE) != RESET) {

			if (timerInfo->isrFunction != NULL)
				timerInfo->isrFunction(timer, timerInfo->isrParams);

			__HAL_TIM_CLEAR_IT(&timerInfo->handle, TIM_IT_UPDATE);
	    }
	}
}


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio.
///
#ifdef HAL_TMR_TIMER_2
void TIM2_IRQHandler() {

	IRQHandler(HAL_TMR_TIMER_2);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio.
///
#ifdef HAL_TMR_TIMER_3
void TIM3_IRQHandler() {

	IRQHandler(HAL_TMR_TIMER_3);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio.
///
#ifdef HAL_TMR_TIMER_4
void TIM4_IRQHandler() {

	IRQHandler(HAL_TMR_TIMER_4);
}
#endif

