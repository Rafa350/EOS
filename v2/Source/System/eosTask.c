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

    vTaskDelay(delay);
}


/*************************************************************************
 *
 *       Retarda la tasca el numero de tics especificat
 *
 *       Funcio:
 *           void eosTaskDelay(
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
    
    vTaskDelayUntil(lastTick, delay);
}


/*************************************************************************
 *
 *       Obte el numero de tick actual
 * 
 *       Funcio:
 *           unsigned eosTaskGetTickCount(void) 
 * 
 *       Retorn:
 *           Numero de tick actual
 *
 *************************************************************************/

unsigned eosTaskGetTickCount(void) {
    
    return xTaskGetTickCount();
}


/*************************************************************************
 *
 *       Posa en marxa el planificador i executa les tasques definides
 *
 *       Funcio:
 *           void eosTaskRun(void) 
 *
 *************************************************************************/

void eosTaskRun(void) {
    
    vTaskStartScheduler();
}


void eosTaskEnterCriticalSection(void) {
    
    taskENTER_CRITICAL();
}


void eosTaskExitCriticalSection(void) {
    
    taskEXIT_CRITICAL();
}


void eosTaskSuspendAll(void) {
    
    vTaskSuspendAll();
}


void eosTaskResumeAll(void) {
    
    xTaskResumeAll();
}
