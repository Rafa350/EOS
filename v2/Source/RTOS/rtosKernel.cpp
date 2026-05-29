#include "RTOS/rtosKernel.h"

#include "FreeRTOS.h"
#include "task.h"


/// ----------------------------------------------------------------------
/// \brief    Inicia el planificador
///
void rtos::Kernel::startScheduler(){

	if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED)
		vTaskStartScheduler();
}


/// ----------------------------------------------------------------------
/// \brief    Para el planificador
///
void rtos::Kernel::stopScheduler() {

	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
		vTaskEndScheduler();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre de tics desde el inici de l'aplicacio
/// \return   El valor.
///
uint32_t rtos::Kernel::getTickCount() {

	return xTaskGetTickCount();
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat del planificador.
/// \return   L'estat.
///
rtos::Kernel::State rtos::Kernel::getState() {

	switch (xTaskGetSchedulerState()) {
		case taskSCHEDULER_RUNNING:
			return State::running;

		case taskSCHEDULER_SUSPENDED:
			return State::suspended;

		default:
			return State::stopped;
	}
}
