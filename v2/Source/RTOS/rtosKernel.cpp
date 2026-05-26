#include "RTOS/rtosKernel.h"
#include "RTOS/rtosTicks.h"


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
/// \brief    Entra en una seccio critica.
///
void rtos::Kernel::enterCritical() {

    taskENTER_CRITICAL();
}


/// ----------------------------------------------------------------------
/// \brief    Surt d'una seccio critica.
///
void rtos::Kernel::exitCritical() {

	taskEXIT_CRITICAL();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre de tics desde el inici de l'aplicacio
/// \return   El valor.
///
rtos::Ticks rtos::Kernel::getTickCount() {

	return rtos::Ticks(xTaskGetTickCount());
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat del planificador.
/// \return   L'estat.
///
rtos::Kernel::State rtos::Kernel::getState() {

	switch (xTaskGetSchedulerState()) {
		case taskSCHEDULER_RUNNING: return State::running;
		case taskSCHEDULER_SUSPENDED: return State::suspended;
		default: return State::stopped;
	}
}
