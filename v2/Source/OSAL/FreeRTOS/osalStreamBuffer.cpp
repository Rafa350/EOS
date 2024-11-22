#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalStreamBuffer.h"
#include "FreeRTOS.h"
#include "stream_buffer.h"



HStreamBuffer osalStreamBufferCreate(
    unsigned size) {
    
    HStreamBuffer hBuffer = (HStreamBuffer) xStreamBufferCreate(size, 1);
    eosAssert(hBuffer != NULL);
    
    return hBuffer;
}


unsigned osalStreamBufferSend(
    HStreamBuffer hBuffer, 
    uint8_t* data, 
    unsigned length,
    unsigned blockTime) {
   
    return xStreamBufferSend(hBuffer, data, length, blockTime);
}
