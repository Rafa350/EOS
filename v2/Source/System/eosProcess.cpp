// EOS 
#include "System/eosProcess.hpp"

// FreeRTOS 
#include "FreeRTOS.h"
#include "task.h"


eos::Process::Process(unsigned stackSize, unsigned priority) {
    
    void *hTask;
    
    xTaskCreate(eos::Process::function, "", stackSize, this, tskIDLE_PRIORITY + priority, &hTask);
}


void eos::Process::function(void *params) {
    
    eos::Process *process = (eos::Process*) params;
    while (true)
        process->run();
}


unsigned eos::Process::getTickCount() {

    return xTaskGetTickCount();   
}


void eos::Process::delay(unsigned time) {

    if (time > 0)
        vTaskDelay((TickType_t) time);    
}


void eos::Process::delayUntil(unsigned time, unsigned *lastTick) {
    
    if (time > 0)
        vTaskDelayUntil((TickType_t*) lastTick, (TickType_t) time);
}