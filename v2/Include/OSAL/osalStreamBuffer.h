#ifndef __osalStreamBuffer__
#define __osalStreamBuffer__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct OSAL_STREAM_STREAMBUF_DATA *HStreamBuffer;


HStreamBuffer osalStreamBufferCrearte(unsigned size);
void osalStreamBufferDestroy(HStreamBuffer hBuffer);

unsigned osalStreamBufferSend(HStreamBuffer hBuffer, uint8_t* data, unsigned length, unsigned blockTime);
unsigned osalStreamBufferSendISR(HStreamBuffer hBuffer, uint8_t* data, unsigned length, unsigned blockTime);


#ifdef	__cplusplus
}
#endif


#endif // __osalStreamBuffer__
