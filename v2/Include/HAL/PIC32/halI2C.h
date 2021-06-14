#ifndef __PIC32_halI2C__
#define	__PIC32_halI2C__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


// Identificador dels canals
#define HAL_I2C_CHANNEL_1         0
#ifdef _I2C2
#define HAL_I2C_CHANNEL_2         1
#endif
#ifdef _I2C3
#define HAL_I2C_CHANNEL_3         2
#endif
#ifdef _i2C4
#define HAL_I2C_CHANNEL_4         3
#endif
#ifdef _I2C5
#define HAL_I2C_CHANNEL_5         4
#endif
#define HAL_I2C_CHANNEL_NONE      0xFFFFFFFF


// Identificador dels events
#define HAL_I2C_EVENT_MASTER      0x01
#define HAL_I2C_EVENT_SLAVE       0x02
#define HAL_I2C_EVENT_BUS         0x04
#define HAL_I2C_EVENT_ALL         0x07


typedef struct  __attribute__((packed , aligned(4))) {
   __I2C1CONbits_t I2CxCON;
   volatile uint32_t I2CxCONCLR;
   volatile uint32_t I2CxCONSET;
   volatile uint32_t I2CxCONINV;
   __I2C1STATbits_t I2CxSTAT;
   volatile uint32_t I2CxSTATCLR;
   volatile uint32_t I2CxSTATSET;
   volatile uint32_t I2CxSTATINV;
   volatile uint32_t I2CxADD;
   uint32_t DONTUSE1[3];
   volatile uint32_t I2CxMSK;
   uint32_t DONTUSE2[3];
   volatile uint32_t I2CxBRG;
   uint32_t DONTUSE3[3];
   volatile uint32_t I2CxTRN;
   uint32_t DONTUSE4[3];
   volatile uint32_t I2CxRCV;
   uint32_t DONTUSE5[3];
} I2CRegisters;

typedef uint32_t I2CChannel;
typedef struct __I2CData* I2CHandler;
typedef void (*I2CInterruptFunction)(I2CHandler handler, void* params);

struct __I2CData {
    I2CRegisters* regs;
    I2CInterruptFunction isrFunction;
    void* isrParams;
};
typedef struct __I2CData I2CData;

typedef struct {
    I2CChannel channel;
    uint32_t baudRate;
} I2CMasterSettings;


I2CHandler halI2CMasterInitialize(I2CData* data, const I2CMasterSettings *settings);
void halI2CMasterDeinitialize(I2CHandler handler);

void halI2CMasterStart(I2CHandler hander);
void halI2CMasterStartRepeat(I2CHandler handler);
void halI2CMasterStop(I2CHandler handler);

bool halI2CIsBusIdle(I2CHandler handler);

bool halI2CArbitrationLossHasOccurred(I2CHandler handler);
void halI2CArbitrationLossClear(I2CHandler handler);

void halI2CTransmitterByteSend(I2CHandler handler, uint8_t data);
bool halI2CTransmitterByteWasAcknowledged(I2CHandler handler);

uint8_t halI2CReceivedByteGet(I2CHandler handler);
void halI2CReceivedByteAcknowledge(I2CHandler handler, bool ack);
void halI2CMasterReceiverClock1Byte(I2CHandler handler);

void halI2CSetInterruptFunction(I2CHandler handler, I2CInterruptFunction function, void* params);
void halI2CInterruptHandler(I2CHandler handler);

void halI2CEnableInterrupts(I2CHandler handler, uint32_t sources);
uint32_t halI2CDisableInterrupts(I2CHandler handler, uint32_t sources);

bool halI2CGetInterruptFlag(I2CHandler handler, uint32_t source);
void halI2CClearInterruptFlags(I2CHandler handler, uint32_t sources);


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halI2C__
