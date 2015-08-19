#include "eos.h"
#include "System/eosTask.h"
#include "FreeRTOS.h"
#include "task.h"


/*************************************************************************
 *
 *       Crea una tasca
 *
 *       Funcio:
 *           eosTaskHandle eosTaskCreate(
 *               unsigned priority, 
 *               unsigned stackSize, 
 *               eosTaskFunction taskFunction, 
 *               void *taskParams) 
 * 
 *       Entrada:
 *           priority : Prioritat
 *           stackSize: Tamany de la pila
 *           taskFunction: Funcio de la tasca
 *           taskParams  : Parametres de la tasca
 * 
 *       Retorn:
 *           Handler de la tasca
 *
 *************************************************************************/

eosTaskHandle eosTaskCreate(
    unsigned priority, 
    unsigned stackSize, 
    eosTaskFunction taskFunction, 
    void *taskParams) {
    
    if (stackSize < configMINIMAL_STACK_SIZE)
        stackSize = configMINIMAL_STACK_SIZE;
    
    eosTaskHandle hTask;
    if (xTaskCreate(taskFunction, "", stackSize, taskParams, 
        tskIDLE_PRIORITY, &hTask) == pdPASS)
        return hTask;
    else
        return NULL;
}


/*************************************************************************
 *
 *       Retarda la tasca el numero de tics especificat
 *
 *       Funcio:
 *           void eosTaskDelay(
 *               unsigned delay) 
 *
 *       Entrada:
 *           delay: Numero de tics a retardar
 *
 *************************************************************************/

void eosTaskDelay(
    unsigned delay) {
    
    if (delay > 0)
        vTaskDelay(delay);
}


/*************************************************************************
 *
 *       Retarda la tasca el numero de tics especificat
 *
 *       Funcio:
 *           void eosTaskDelayUntil(
 *               unsigned delay,
 *               unsigned *lastTick) 
 *
 *       Entrada:
 *           delay   : Numero de tick a retardar
 *           lastTick: Numero de tick actual
 * 
 *       Sortida:
 *           lastTick: El numero de tick actualitzat
 *
 *************************************************************************/

void eosTaskDelayUntil(unsigned delay, unsigned *lastTick) {
    
    if (delay > 0)
        vTaskDelayUntil(lastTick, delay);
}


/*************************************************************************
 *
 *       Obte el numero de tick actual
 * 
 *       Funcio:
 *           unsigned eosGetTickCount(void) 
 * 
 *       Retorn:
 *           Numero de tick actual
 *
 *************************************************************************/

unsigned eosGetTickCount(void) {
    
    return xTaskGetTickCount();
}


/*************************************************************************
 *
 *       Posa en marxa el planificador i executa les tasques definides
 *
 *       Funcio:
 *           void eosStartScheduler(void) 
 *
 *************************************************************************/

void eosStartScheduler(void) {
    
    vTaskStartScheduler();
}


/*************************************************************************
 *
 *       Obte l'estat del planificador
 * 
 *       Funcio:
 *           eosSchedulerState eosGetSchedulerState(void)
 * 
 *       Return:
 *           Estat del planificador
 *
 *************************************************************************/

eosSchedulerState eosGetSchedulerState(void) {

    switch (xTaskGetSchedulerState()) {
        case taskSCHEDULER_RUNNING:
            return eosSchedulerStateRunning;
            
        case taskSCHEDULER_SUSPENDED:
            return eosSchedulerStateSuspended;
            
        case taskSCHEDULER_NOT_STARTED:
        default:
            return eosSchedulerStateNotStarted;
    }
}


/*************************************************************************
 *
 *       Entra en una seccio critica
 * 
 *       Funcio:
 *           void eosEnterCriticalSection(
 *               eosCriticalSectionSeverity severity,
 *               eosCriticalSectionInfo *info) 
 *
 *       Entrada:
 *           severity: Nivell de severitat
 *           info    : punter a la informacio de recuperacio
 * 
 *************************************************************************/

void eosEnterCriticalSection(
    eosCriticalSectionSeverity severity,
    eosCriticalSectionInfo *info) {
    
    switch (severity) {
        case eosCriticalSectionSeverityHigh:
            portENTER_CRITICAL();
            break;

        case eosCriticalSectionSeverityLow:
        default:
            vTaskSuspendAll();
            break;
    }

    info->severity = severity;
}


/*************************************************************************
 *
 *       Surt de la seccio critica
 * 
 *       Funcio:
 *           void eosLeaveCriticalSection(
 *               eosCriticalSectionInfo *info) 
 *
 *       Entrada:
 *           info: Informacio de recuperacio obtinguda de la
 *                 funcio 'eosEnterCriticalSection'
 *
 *************************************************************************/

void eosLeaveCriticalSection(
    eosCriticalSectionInfo *info) {
    
    switch (info->severity) {
        case eosCriticalSectionSeverityHigh:
            portEXIT_CRITICAL();
            break;
            
        case eosCriticalSectionSeverityLow:
        default:
            xTaskResumeAll();
            break;
    }
}
