#include "System/Core/eosSemaphore.hpp"
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
    unsigned blockTime) {
    
    return xSemaphoreTake(handle, blockTime);
}


bool eos::BinarySemaphore::give() {
    
    return xSemaphoreGive(handle);
}


void eos::BinarySemaphore::giveISR() {
    
    xSemaphoreGiveFromISR(handle, NULL);
}
