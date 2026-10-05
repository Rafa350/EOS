module;


#include "HTL/htl.h"


module Eos.Hardware.Clock;


using namespace eos;
using namespace eos::hardware::clock::internal;


static_assert(Platform::is_STM32_G0B1);


/// ---------------------------------------------------------------------------
/// @brief    Habilita el rellotge HSI48
///
void HSI48Interface<true>::enableHSI48() const {

}


/// ---------------------------------------------------------------------------
/// @brief    Desabilita el rellotge HSI48
///
void HSI48Interface<true>::disableHSI48() const {

}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el rellotge HSI48 esta habilitat.
/// @return   True si esta habilitat.
///
bool HSI48Interface<true>::isHSI48Enabled() const {

    return false;
}
