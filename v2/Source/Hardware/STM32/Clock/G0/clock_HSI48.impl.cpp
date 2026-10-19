module;

#include "hardware.h"


module Eos.Hardware.Clock;


using namespace eos;
using namespace eos::hardware::clock::internal;


static_assert(platformCheck("STM32G0B1xx"));


/// ---------------------------------------------------------------------------
/// @brief    Habilita el rellotge HSI48
///
void Clock_HSI48<true>::enableHSI48() {

}


/// ---------------------------------------------------------------------------
/// @brief    Desabilita el rellotge HSI48
///
void Clock_HSI48<true>::disableHSI48() {

}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el rellotge HSI48 esta habilitat.
/// @return   True si esta habilitat.
///
bool Clock_HSI48<true>::isHSI48Enabled() {

    return false;
}
