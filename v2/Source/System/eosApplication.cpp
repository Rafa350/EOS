// EOS
#include "System/eosApplication.hpp"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"


void *operator new(size_t size) {
    
    return pvPortMalloc(size);
}


void operator delete(void *ptr) {
    
    vPortFree(ptr);
}


eos::Application::Application() {
    
}


void eos::Application::addProcess(eos::HProcess process) {
    
}


void eos::Application::execute() {
    
    
    vTaskStartScheduler();
}
