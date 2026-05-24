#include "RTOS/rtosKernel.h"
#include "RTOS/rtosTicks.h"


#include "FreeRTOS.h"
#include "task.h"


void rtos::Kernel::startScheduler(){

	vTaskStartScheduler();
}


void rtos::Kernel::stopScheduler() {

	vTaskEndScheduler();
}


void rtos::Kernel::enterCritical() {

    taskENTER_CRITICAL();
}


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
