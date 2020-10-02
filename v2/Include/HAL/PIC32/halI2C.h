#ifndef __PIC32_halI2C__
#define	__PIC32_halI2C__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif
    
    
// Adresses base de cada canal
#define HAL_I2C_ADDR_1            _I2C1_BASE_ADDRESS
#define HAL_I2C_ADDR_2            _I2C2_BASE_ADDRESS
#define HAL_I2C_ADDR_3            _I2C3_BASE_ADDRESS
#define HAL_I2C_ADDR_4            _I2C4_BASE_ADDRESS
#define HAL_I2C_ADDR_5            _I2C5_BASE_ADDRESS
    
// Identificador dels canals
#define HAL_I2C_CHANNEL_1         HAL_I2C_ADDR_1
#ifdef _I2C2
#define HAL_I2C_CHANNEL_2         HAL_I2C_ADDR_2
#endif
#ifdef _I2C3
#define HAL_I2C_CHANNEL_3         HAL_I2C_ADDR_3
#endif
#ifdef _i2C4
#define HAL_I2C_CHANNEL_4         HAL_I2C_ADDR_4
#endif
#ifdef _I2C5
#define HAL_I2C_CHANNEL_5         HAL_I2C_ADDR_5
#endif

// Identificador dels events
#define HAL_I2C_EVENT_MASTER      0x01
#define HAL_I2C_EVENT_SLAVE       0x02
#define HAL_I2C_EVENT_BUS         0x04
#define HAL_I2C_EVENT_ALL         0x07

        
typedef uint32_t I2CChannel;
typedef void (*I2CInterruptFunction)(I2CChannel channel, void* params);

typedef struct {
    I2CChannel channel;
    uint32_t baudRate;
} I2CMasterInitializeInfo;


void halI2CMasterInitialize(const I2CMasterInitializeInfo* info);
void halI2CMasterDeinitialize(I2CChannel channel);

void halI2CMasterStart(I2CChannel channel);
void halI2CMasterStartRepeat(I2CChannel channel);
void halI2CMasterStop(I2CChannel channel);

bool halI2CIsBusIdle(I2CChannel channel);

bool halI2CArbitrationLossHasOccurred(I2CChannel channel);
void halI2CArbitrationLossClear(I2CChannel channel);

void halI2CTransmitterByteSend(I2CChannel channel, uint8_t data);
bool halI2CTransmitterByteWasAcknowledged(I2CChannel channel); 

uint8_t halI2CReceivedByteGet(I2CChannel channel);
void halI2CReceivedByteAcknowledge(I2CChannel channel, bool ack);
void halI2CMasterReceiverClock1Byte(I2CChannel channel);

void halI2CSetInterruptFunction(I2CChannel channel, I2CInterruptFunction function, void* params);
void halI2CEnableInterruptSources(I2CChannel channel, uint32_t sources);
void halI2CDisableInterruptSources(I2CChannel channel, uint32_t sources);
bool halI2CGetInterruptSourceFlag(I2CChannel channel, uint32_t source);
void halI2CClearInterruptSourceFlag(I2CChannel channel, uint32_t source);


#ifdef	__cplusplus
}
#endif


#endif // __halI2C__

