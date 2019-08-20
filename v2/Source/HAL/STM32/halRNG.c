#include "eos.h"
#ifdef EOS_STM32F7
#include "stm32f7xx_hal_rng.h"
#endif



static RNG_HandleTypeDef handle;


/// ----------------------------------------------------------------------
/// \brief Inicialitza el generador de nombres aleatoris.
///
void halRNGInitialize() {

	handle.Instance = RNG;
	handle.State = HAL_RNG_STATE_RESET;

	__HAL_RCC_RNG_CLK_ENABLE();
	HAL_RNG_Init(&handle);
}


/// ----------------------------------------------------------------------
/// \brief Obte un nombre aleatori.
/// \raturn El nombre generat.
///
unsigned halRNGGetRandomNumber() {

	uint32_t number;
	if (HAL_RNG_GenerateRandomNumber(&handle, &number) != HAL_ERROR)
		return number;
	else
		return 0;
}
