#include "eos.h"
#include "OSAL/osalKernel.h"
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

    osalStartScheduler();
}


/// ----------------------------------------------------------------------
/// \brief    Suspen totes les tasques.
///
void Kernel::suspendAll() {

}


/// ----------------------------------------------------------------------
/// \brief    Resumeix totes les tasques.
///
void Kernel::resumeAll() {

}


/// ----------------------------------------------------------------------
/// \brief    Retorna el numero te ticks transcurreguts desde la
///           inicialitzacio del sistema.
/// \return   El numero de ticks.
///
unsigned Kernel::getTickCount() const {

    return osalGetTickCount();
}
