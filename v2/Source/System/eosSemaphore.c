#include "System/eosSemaphore.h"
#include "FreeRTos.h"
#include "semphr.h"


eosSemaphoreHandle eosSemaphoreCreate(void) {
    
    return xSemaphoreCreateBinary();
}


bool eosSemaphoreTake(
    eosSemaphoreHandle hSemaphore, 
    unsigned timeout) {
    
    return xSemaphoreTake(hSemaphore, timeout);
}


void eosSemaphoreGive(
    eosSemaphoreHandle hSemaphore) {
    
    xSemaphoreGive(hSemaphore);
}


void eosSemaphoreISRGive(
    eosSemaphoreHandle hSemaphore) {
    
    xSemaphoreGiveFromISR(hSemaphore, NULL);
}
