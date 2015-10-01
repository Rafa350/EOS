// EOS
#include "System/eosApplication.hpp"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"


extern "C" void eosInitialize();


void *operator new(size_t size) {
    
    return pvPortMalloc(size);
}

void operator delete(void *ptr) {
    
    vPortFree(ptr);
}


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           eos::Application::Application() 
 *
 *************************************************************************/

eos::Application::Application() {
    
    eosInitialize();
}


void eos::Application::execute() {
        
    vTaskStartScheduler();
}
