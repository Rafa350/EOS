module;


#include "eos.h"
#include "eosTime.h"
#include "FreeRTOS.h"


export module Eos.System.Core.RTOSUtils;


export namespace eos {

    uint32_t toTicks(Time time);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el temps en ticks d'un valor de temps en milisegons.
/// \param    Time: El valor de temps
/// \return   El resultat de l'operacio.
///
uint32_t eos::toTicks(
    Time time) {

    return time.isInfinite() ?
            portMAX_DELAY :
            time.toMiliseconds() / portTICK_PERIOD_MS;
}
