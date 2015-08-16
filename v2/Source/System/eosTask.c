#include "eos.h"
#include "System/eosTask.h"
#include "System/eosMemory.h"
#include "FreeRTOS.h"
#include "task.h"


typedef struct __eosTask {
    TaskHandle_t rtosTask;    
} eosTask;


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
    
    eosTaskHandle hTask = eosAlloc(sizeof(struct __eosTask));
    if (hTask != NULL) {
        
        if (xTaskCreate(taskFunction, NULL, stackSize, taskParams, 
            tskIDLE_PRIORITY,  &hTask->rtosTask) != pdPASS) {

            eosFree(hTask);
            hTask = NULL;
        }
    }
    
    return hTask;
}


/*************************************************************************
 *
 *       Retarda la tasca en numero de milisegons especificat
 *
 *       Funcio:
 *           void eosTaskDelay(
 *               unsigned delay) 
 *
 *       Entrada:
 *           delay: Numero de milisegons per retardar
 *
 *************************************************************************/

void eosTaskDelay(
    unsigned delay) {

    vTaskDelay(delay / portTICK_PERIOD_MS);
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