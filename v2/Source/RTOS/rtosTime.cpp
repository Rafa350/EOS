#include "eos.h"
#include "eosTime.h"
#include "RTOS/rtosTime.h"

#include "FreeRTOS.h"


/// ----------------------------------------------------------------------
/// \brief    Obte el temps en ticks d'un valor de temps en milisegons.
/// \param    Time: El valor de temps
/// \return   El resultat de l'operacio.
///
uint32_t rtos::toTicks(
	eos::Time time) {

    return time.isInfinite() ?
    		portMAX_DELAY :
			time.toMiliseconds() / portTICK_PERIOD_MS;
}
