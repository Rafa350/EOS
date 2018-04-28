#include "hal/halTMR.h"
#if defined(STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(STM32F7)
#include "stm32f7xx_hal.h"
#else
#error Hardware no soportado
#endif


static TIM_HandleTypeDef handles[HAL_TMR_ID_MAX];


/// ----------------------------------------------------------------------
/// \brief Activa el rellotge del temporitzador
/// \param timer: Identificador del temporitzador.
///
static void EnableTimerClock(
	uint8_t timer) {

	switch (timer) {
		case HAL_TMR_ID_1:
			__HAL_RCC_TIM1_CLK_ENABLE();
			break;

		case HAL_TMR_ID_2:
			__HAL_RCC_TIM2_CLK_ENABLE();
			break;

		case HAL_TMR_ID_3:
			__HAL_RCC_TIM3_CLK_ENABLE();
			break;

		case HAL_TMR_ID_4:
			__HAL_RCC_TIM4_CLK_ENABLE();
			break;

		case HAL_TMR_ID_5:
			__HAL_RCC_TIM5_CLK_ENABLE();
			break;

		case HAL_TMR_ID_6:
			__HAL_RCC_TIM6_CLK_ENABLE();
			break;

		case HAL_TMR_ID_7:
			__HAL_RCC_TIM7_CLK_ENABLE();
			break;

		case HAL_TMR_ID_8:
			__HAL_RCC_TIM8_CLK_ENABLE();
			break;

		case HAL_TMR_ID_9:
			__HAL_RCC_TIM9_CLK_ENABLE();
			break;

		case HAL_TMR_ID_10:
			__HAL_RCC_TIM10_CLK_ENABLE();
			break;

		case HAL_TMR_ID_11:
			__HAL_RCC_TIM11_CLK_ENABLE();
			break;

		case HAL_TMR_ID_12:
			__HAL_RCC_TIM12_CLK_ENABLE();
			break;

		case HAL_TMR_ID_13:
			__HAL_RCC_TIM13_CLK_ENABLE();
			break;

		case HAL_TMR_ID_14:
			__HAL_RCC_TIM14_CLK_ENABLE();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el rellotge del temporitzador
/// \param timer: Identificador del temporitzador.
///
static void DisableTimerClock(
	uint8_t timer) {

	switch (timer) {
		case HAL_TMR_ID_1:
			__HAL_RCC_TIM1_CLK_DISABLE();
			break;

		case HAL_TMR_ID_2:
			__HAL_RCC_TIM2_CLK_DISABLE();
			break;

		case HAL_TMR_ID_3:
			__HAL_RCC_TIM3_CLK_DISABLE();
			break;

		case HAL_TMR_ID_4:
			__HAL_RCC_TIM4_CLK_DISABLE();
			break;

		case HAL_TMR_ID_5:
			__HAL_RCC_TIM5_CLK_DISABLE();
			break;

		case HAL_TMR_ID_6:
			__HAL_RCC_TIM6_CLK_DISABLE();
			break;

		case HAL_TMR_ID_7:
			__HAL_RCC_TIM7_CLK_DISABLE();
			break;

		case HAL_TMR_ID_8:
			__HAL_RCC_TIM8_CLK_DISABLE();
			break;

		case HAL_TMR_ID_9:
			__HAL_RCC_TIM9_CLK_DISABLE();
			break;

		case HAL_TMR_ID_10:
			__HAL_RCC_TIM10_CLK_DISABLE();
			break;

		case HAL_TMR_ID_11:
			__HAL_RCC_TIM11_CLK_DISABLE();
			break;

		case HAL_TMR_ID_12:
			__HAL_RCC_TIM12_CLK_DISABLE();
			break;

		case HAL_TMR_ID_13:
			__HAL_RCC_TIM13_CLK_DISABLE();
			break;

		case HAL_TMR_ID_14:
			__HAL_RCC_TIM14_CLK_DISABLE();
			break;
	}
}


static TIM_HandleTypeDef *PrepareTimerHandle(
	const TMRInitializeInfo *info) {

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

	TIM_HandleTypeDef *handle = &handles[info->id];

	handle->Instance = instances[info->id];
	handle->Init.ClockDivision = 1;

	return handle;
}


static TIM_HandleTypeDef *GetTimerHandle(
	uint8_t id) {

	return &handles[id];
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza un temporitzador
/// \param info: Parametres d'inicialitzacio.
///
void halTMRInitialize(
	const TMRInitializeInfo *info) {

	EnableTimerClock(info->id);

	TIM_HandleTypeDef *handle = PrepareTimerHandle(info);
	HAL_TIM_Base_Init(handle);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva un temporitzador
/// \param id: Identificador del temporitzador.
///
void halTMRShutdown(
	uint8_t id) {

	DisableTimerClock(id);
}


void halTMRStartTimer(
	uint8_t id) {

	TIM_HandleTypeDef *handle = GetTimerHandle(id);
	HAL_TIM_Base_Start(handle);
}


/// ----------------------------------------------------------------------
/// \brief Retard en milisegons.
/// \param time: Temps en milisegons.
///
void halTMRDelay(
    uint32_t time) {

	HAL_Delay(time);
}
