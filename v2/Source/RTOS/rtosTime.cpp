#include "eos.h"
#include "RTOS/rtosTime.h"

#include "FreeRTOS.h"


/// ----------------------------------------------------------------------
/// \brief    Obte el temps en ticks.
/// \return   El resultat de l'operacio.
/// \remarks  Mante el valor MAX_DELAY, durant la conversio.
///
uint32_t rtos::Time::toTicks() const {

    return _ms == portMAX_DELAY ? portMAX_DELAY : _ms / portTICK_PERIOD_MS;
}
