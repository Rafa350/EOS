#include "hal/halSYS.h"
#if defined(EOS_STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx_hal.h"
#else
#error hardware no soportado
#endif


/// ----------------------------------------------------------------------
/// \brief Inicialitza el sistema
///
void halSYSInitialize() {

	HAL_Init();
}
