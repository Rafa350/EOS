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


// Opcions: Interrupcio activa
#define HAL_I2C_INT_pos           0
#define HAL_I2C_INT_bits          0x1
#define HAL_I2C_INT_mask          (HAL_I2C_INT_bits << HAL_I2C_INT_pos)

#define HAL_I2C_INT_DISABLE       (0 << HAL_I2C_INT_pos)
#define HAL_I2C_INT_ENABLE        (1 << HAL_I2C_INT_pos)

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
	I2CInterruptFunction isrFunction;
	void* isrParams;
} I2CMasterInitializeInfo;



I2CHandler halI2CMasterInitialize(I2CData* data, const I2CMasterInitializeInfo *info);

void halI2CEnable(I2CHandler handler);
void halI2CDisable(I2CHandler handler);

void halI2CMasterWriteMultiple(I2CHandler handler, uint8_t addr, uint16_t reg, uint16_t memAddress, uint8_t *buffer, uint16_t length);
void halI2CMasterReadMultiple(I2CHandler handler, uint8_t addr, uint16_t reg, uint16_t memAddress, uint8_t *buffer, uint16_t length);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halI2C__
