// EOS 
#include "System/eosTask.hpp"

// FreeRTOS 
#include "FreeRTOS.h"
#include "task.h"


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           eos::Task::Task(
 *               unsigned stackSize, 
 *               unsigned priority) 
 * 
 *       Entrada:
 *           stackSize: Tamsny de la pila
 *           priority : Prioritat del proces
 *
 *************************************************************************/

eos::Task::Task(
    unsigned stackSize, 
    unsigned priority) {
    
    xTaskCreate(eos::Task::function, "", stackSize, this, tskIDLE_PRIORITY + priority, &handle);
}


/*************************************************************************
 *
 *       Destructor
 * 
 *       Funcio:
 *           eos::Task::~Task() 
 *
 *************************************************************************/

eos::Task::~Task() {
    
    vTaskDelete(handle);
}


void eos::Task::function(
    void *params) {
    
    eos::Task *task = reinterpret_cast<eos::Task*>(params);
    while (true)
        task->run();
}


unsigned eos::Task::getTickCount() {

    return xTaskGetTickCount();   
}


void eos::Task::delay(
    unsigned time) {

    if (time > 0)
        vTaskDelay((TickType_t) time);    
}


void eos::Task::delayUntil(
    unsigned time, 
    unsigned *lastTick) {
    
    if (time > 0)
        vTaskDelayUntil((TickType_t*) lastTick, (TickType_t) time);
}


void eos::Task::enterCriticalSection() {

    taskENTER_CRITICAL();
}


void eos::Task::exitCriticalSection() {
    
    taskEXIT_CRITICAL();
}


void eos::Task::suspendAllThreads() {
    
    vTaskSuspendAll();
}


void eos::Task::resumeAllThreads() {

    xTaskResumeAll();
}