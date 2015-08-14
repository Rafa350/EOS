#include "eos.h"
#include "System/eosTask.h"
#include "System/eosMemory.h"
#include "FreeRTOS.h"
#include "task.h"


typedef struct __eosTask {
    TaskHandle_t rtosHandle;
    
} eosTask;


/*************************************************************************
 *
 *       Crea una tasca
 *
 *       Funcio:
 *           eosTaskHandle eosTaskCreate(eosTaskParams *params) 
 * 
 *       Entrada:
 *           params: Parametres
 * 
 *       Retorn:
 *           Handler de la tasca
 *
 *************************************************************************/

eosTaskHandle eosTaskCreate(eosTaskParams *params) {
    
    eosTaskHandle hTask = eosAlloc(sizeof(struct __eosTask));
    if (hTask != NULL) {
        xTaskCreate(
            params->function, 
            params->name, 
            params->stackSize, 
            params->params, 
            tskIDLE_PRIORITY, 
            &hTask->rtosHandle);
    }
    
    return hTask;
}


/*************************************************************************
 *
 *       Retarda la tasca en numero de milisegons especificat
 *
 *       Funcio:
 *           void eosTaskDelay(unsigned delay) 
 *
 *       Entrada:
 *           delay: Numero de milisegons per retardar
 *
 *************************************************************************/

void eosTaskDelay(unsigned delay) {

    vTaskDelay(delay / portTICK_PERIOD_MS);
}


/*************************************************************************
 *
 *       Posa en marxa el planificador i executa les tasques definides
 *
 *       Funcio:
 *           void eosTaskRun(*) 
 *
 *************************************************************************/

void eosTaskRun(void) {
    
    vTaskStartScheduler();
}