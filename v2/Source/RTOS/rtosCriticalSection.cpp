#include "eos.h"
#include "RTOS/rtosCriticalSection.h"

#include "FreeRTOS.h"
#include "task.h"


/// ----------------------------------------------------------------------
/// \brief    Entrada a una seccio critica.
///
void rtos::CriticalSection::enter() {

	taskENTER_CRITICAL();
}


/// ----------------------------------------------------------------------
/// \brief    Sortida d'una seccio critica.
///
void rtos::CriticalSection::exit() {

    taskEXIT_CRITICAL();
}

