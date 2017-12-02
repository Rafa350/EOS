#ifndef __EOS_HAL_I2C_H
#define	__EOS_HAL_I2C_H


#ifdef	__cplusplus
extern "C" {
#endif

    
#include <stdint.h>
#include <stdbool.h>
    
    
#define HAL_I2C_I2C1         0
#define HAL_I2C_I2C2         1
#define HAL_I2C_I2C3         2
#define HAL_I2C_I2C4         3
    
    
typedef void *I2CInterruptParam;   
typedef void (*I2CInterruptCallback)(uint8_t moduleId, I2CInterruptParam param);

void halI2CMasterInitialize(uint8_t moduleId, unsigned baudRate, 
    I2CInterruptCallback callback, I2CInterruptParam param);

void halI2CMasterStart(uint8_t moduleId);
void halI2CMasterStartRepeat(uint8_t moduleId);
void halI2CMasterStop(uint8_t id);

bool halI2CIsBusIdle(uint8_t moduleId);

bool halI2CArbitrationLossHasOccurred(uint8_t moduleId);
void halI2CArbitrationLossClear(uint8_t moduleId);

void halI2CTransmitterByteSend(uint8_t moduleId, uint8_t data);
bool halI2CTransmitterByteWasAcknowledged(uint8_t moduleIdid); 

uint8_t halI2CReceivedByteGet(uint8_t moduleId);
void halI2CReceivedByteAcknowledge(uint8_t moduleId, bool ack);
void halI2CMasterReceiverClock1Byte(uint8_t moduleId);


#ifdef	__cplusplus
}
#endif


#endif

