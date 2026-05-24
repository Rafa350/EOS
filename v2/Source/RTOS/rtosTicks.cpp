#include "RTOS/rtosMiliseconds.h"
#include "RTOS/rtosTicks.h"

#include "FreeRTOS.h"


/// ----------------------------------------------------------------------
/// \brief    Converteix el valor en milisegons.
/// \return   El valor en milisegons.
//
rtos::Miliseconds rtos::Ticks::asMiliseconds() const {

	return Miliseconds(_value * portTICK_PERIOD_MS);
}
