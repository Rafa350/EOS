#include "eos.h"
#include "OSAL/osalKernel.h"
#include "HAL/halINT.h"



/// -------------------------------------------------------------------
/// \brief    Entra en una seccio critica
///
void osalEnterCritical() {

	__halINTDisableInterrupts();
}


/// ----------------------------------------------------------------------
/// \brief    Surt d'una seccio critica
///
void osalExitCritical() {

	__halINTEnableInterrupts();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio TICK del sistema.
///
void osalSysTickHandler() {

	HAL_IncTick();
}
