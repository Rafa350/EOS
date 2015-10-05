#include "System/eosSemaphore.hpp"
#include "FreeRTos.h"
#include "semphr.h"


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           eos::BinarySemaphore::BinarySemaphore()
 *
 *************************************************************************/

eos::BinarySemaphore::BinarySemaphore() {
    
    handle = xSemaphoreCreateBinary();
}


/*************************************************************************
 *
 *       Destructor
 * 
 *       Funcio:
 *           eos::BinarySemaphore::~BinarySemaphore() 
 *
 *************************************************************************/

eos::BinarySemaphore::~BinarySemaphore() {

    vSemaphoreDelete(handle);
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
