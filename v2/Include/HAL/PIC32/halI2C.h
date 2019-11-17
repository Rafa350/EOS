#ifndef __PIC32_halI2C__
#define	__PIC32_halI2C__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif

    
typedef uint8_t I2CModule;
typedef void (*I2CInterruptCallback)(I2CModule module, void *param);

typedef struct {
    I2CModule module;
    int baudRate;
    I2CInterruptCallback irqCallback;
    void *irqParam;
} I2CMasterInitializeInfo;


#define HAL_I2C_I2C1         ((I2CModule) 0)
#ifdef _I2C2
#define HAL_I2C_I2C2         ((I2CModule) 1)
#endif
#ifdef _I2C3
#define HAL_I2C_I2C3         ((I2CModule) 2)
#endif
#ifdef _i2C4
#define HAL_I2C_I2C4         ((I2CModule) 3)
#endif
#ifdef _I2C5
#define HAL_I2C_I2C5         ((I2CModule) 4)
#endif


void halI2CMasterInitialize(const I2CMasterInitializeInfo *info);
void halI2CMasterShutdown(I2CModule module);

void halI2CMasterStart(I2CModule module);
void halI2CMasterStartRepeat(I2CModule module);
void halI2CMasterStop(I2CModule module);

bool halI2CIsBusIdle(I2CModule module);

bool halI2CArbitrationLossHasOccurred(I2CModule module);
void halI2CArbitrationLossClear(I2CModule module);

void halI2CTransmitterByteSend(I2CModule module, uint8_t data);
bool halI2CTransmitterByteWasAcknowledged(I2CModule module); 

uint8_t halI2CReceivedByteGet(I2CModule module);
void halI2CReceivedByteAcknowledge(I2CModule module, bool ack);
void halI2CMasterReceiverClock1Byte(I2CModule module);


#ifdef	__cplusplus
}
#endif


#endif // __halI2C__

