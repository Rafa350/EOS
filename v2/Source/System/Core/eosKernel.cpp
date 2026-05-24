#include "eos.h"
#include "RTOS/rtosKernel.h"
#include "RTOS/rtosTicks.h"
#include "System/Core/eosKernel.h"


using namespace eos;


Kernel Kernel::_instance;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Kernel::Kernel() {

}


/// ----------------------------------------------------------------------
/// \brief    Inicia el planificador.
/// \remarks  Ja no retorna mai d'aquest metode.
///
void Kernel::startScheduler() {

    rtos::Kernel::startScheduler();
}


/// ----------------------------------------------------------------------
/// \brief    Suspen totes les tasques.
///
void Kernel::suspendAll() {

	rtos::Kernel::stopScheduler();
}


/// ----------------------------------------------------------------------
/// \brief    Resumeix totes les tasques.
///
void Kernel::resumeAll() {

	rtos::Kernel::resumeAll();
}


/// ----------------------------------------------------------------------
/// \brief    Retorna el numero te ticks transcurreguts desde la
///           inicialitzacio del sistema.
/// \return   El numero de ticks.
///
uint32_t Kernel::getTickCount() const {

    return rtos::Kernel::getTickCount();
}
