#ifndef __STM32_halI2C__
#define	__STM32_halI2C__


// EOS includes
//
#include "eos.h"


// Identificador del canal I2C
#define HAL_I2C_CHANNEL_1         0
#define HAL_I2C_CHANNEL_2         1
#define HAL_I2C_CHANNEL_3         2
#define HAL_I2C_CHANNEL_4         3
#define HAL_I2C_CHANNEL_NONE      0xFFFFFFFF


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint32_t I2CChannel;
typedef uint32_t I2COptions;
typedef struct __I2CData* I2CHandler;
typedef void (*I2CInterruptFunction)(I2CHandler handler, void *params);

struct __I2CData {
	I2C_TypeDef* device;
	I2C_HandleTypeDef handle;
	I2CInterruptFunction isrFunction;
	void* isrParams;
};
typedef struct __I2CData I2CData;

typedef struct {
	I2CChannel channel;
	I2COptions options;
} I2CMasterInitializeInfo;


I2CHandler halI2CMasterInitialize(I2CData* data, const I2CMasterInitializeInfo *info);

void halI2CMasterWriteMultiple(I2CHandler handler, uint8_t addr, uint16_t reg, uint16_t memAddress, uint8_t *buffer, uint16_t length);
void halI2CMasterReadMultiple(I2CHandler handler, uint8_t addr, uint16_t reg, uint16_t memAddress, uint8_t *buffer, uint16_t length);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halI2C__
