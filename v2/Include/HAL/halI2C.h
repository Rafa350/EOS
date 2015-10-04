#ifndef __HAL_I2C_H
#define	__HAL_I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#include <stdint.h>
#include <stdbool.h>
    
    
typedef void *I2CInterruptParam;   
typedef void (*I2CInterruptCallback)(unsigned moduleId, I2CInterruptParam param);

void halI2CMasterInitialize(unsigned moduleId, unsigned baudRate, 
            I2CInterruptCallback callback, I2CInterruptParam param);

void halI2CMasterStart(unsigned moduleId);
void halI2CMasterStartRepeat(unsigned moduleId);
void halI2CMasterStop(unsigned id);

bool halI2CIsBusIdle(unsigned moduleId);

bool halI2CArbitrationLossHasOccurred(unsigned moduleId);
void halI2CArbitrationLossClear(unsigned moduleId);

void halI2CTransmitterByteSend(unsigned moduleId, uint8_t data);
bool halI2CTransmitterByteWasAcknowledged(unsigned moduleIdid); 

uint8_t halI2CReceivedByteGet(unsigned moduleId);
void halI2CReceivedByteAcknowledge(unsigned moduleId, bool ack);
void halI2CMasterReceiverClock1Byte(unsigned moduleId);


#ifdef	__cplusplus
}
#endif

#endif

