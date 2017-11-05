#include "hal/halTMR.h"
#include "stm32f4xx_hal.h"


/// ----------------------------------------------------------------------
/// \brief Retard en milisegons.
/// \param time: Temps en milisegons.
///
void halTMRDelay(
    uint32_t time) {

	HAL_Delay(time);
}
