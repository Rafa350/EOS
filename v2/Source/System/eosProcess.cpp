// EOS 
#include "System/eosProcess.hpp"

// FreeRTOS 
#include "FreeRTOS.h"
#include "task.h"


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           eos::Process::Process(
 *               unsigned stackSize, 
 *               unsigned priority) 
 * 
 *       Entrada:
 *           stackSize: Tamsny de la pila
 *           priority : Prioritat del proces
 *
 *************************************************************************/

eos::Process::Process(
    unsigned stackSize, 
    unsigned priority) {
    
    xTaskCreate(eos::Process::function, "", stackSize, this, tskIDLE_PRIORITY + priority, &taskHandle);
}


/*************************************************************************
 *
 *       Destructor
 * 
 *       Funcio:
 *           eos::Process::~Process() 
 *
 *************************************************************************/

eos::Process::~Process() {
    
    vTaskDelete(taskHandle);
}


void eos::Process::function(
    void *params) {
    
    eos::HProcess process = (eos::HProcess) params;
    while (true)
        process->run();
}


unsigned eos::Process::getTickCount() {

    return xTaskGetTickCount();   
}


void eos::Process::delay(
    unsigned time) {

    if (time > 0)
        vTaskDelay((TickType_t) time);    
}


void eos::Process::delayUntil(
    unsigned time, 
    unsigned *lastTick) {
    
    if (time > 0)
        vTaskDelayUntil((TickType_t*) lastTick, (TickType_t) time);
}


void eos::Process::enterCriticalSection() {

    taskENTER_CRITICAL();
}


void eos::Process::exitCriticalSection() {
    
    taskEXIT_CRITICAL();
}


void eos::Process::suspendAllThreads() {
    
    vTaskSuspendAll();
}


void eos::Process::resumeAllThreads() {

    xTaskResumeAll();
}