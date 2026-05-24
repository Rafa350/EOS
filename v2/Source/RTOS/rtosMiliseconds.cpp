#include "RTOS/rtosMiliseconds.h"
#include "RTOS/rtosTicks.h"

#include "FreeRTOS.h"


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre de ticks.
/// \return   El resultat de l'operacio.
/// \remarks  Mante el valor MAX_DELAY, durant la conversio.
///
rtos::Ticks rtos::Miliseconds::asTicks() const {

    return Ticks(_value == portMAX_DELAY ? portMAX_DELAY : _value / portTICK_PERIOD_MS);
}
