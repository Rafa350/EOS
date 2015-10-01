// EOS
#include "System/eosSemaphore.hpp"

// FreeRTOS
#include "FreeRTos.h"
#include "semphr.h"


eos::BinarySemaphore::BinarySemaphore() {
    
    handle = xSemaphoreCreateBinary();
}


bool eos::BinarySemaphore::take(
    unsigned timeout) {
    
    return xSemaphoreTake(handle, timeout);
}


bool eos::BinarySemaphore::give() {
    
    return xSemaphoreGive(handle);
}


void eos::BinarySemaphore::giveISR() {
    
    xSemaphoreGiveFromISR(handle, NULL);
}
