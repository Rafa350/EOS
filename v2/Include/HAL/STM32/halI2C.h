#ifndef __STM32_halI2C__
#define	__STM32_halI2C__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif

typedef uint8_t I2CModule;

typedef struct {
	I2CModule module;
} I2CMasterInitializeInfo;


#define HAL_I2C_I2C1              ((I2CModule) 0)
#define HAL_I2C_I2C2              ((I2CModule) 1)
#define HAL_I2C_I2C3              ((I2CModule) 2)
#define HAL_I2C_I2C4              ((I2CModule) 3)

#define HAL_I2C_ID_MAX            4


void halI2CMasterInitialize(const I2CMasterInitializeInfo *info);

void halI2CMasterWriteMultiple(uint8_t id, uint8_t addr, uint16_t reg, uint16_t memAddress, uint8_t *buffer, uint16_t length);
void halI2CMasterReadMultiple(uint8_t id, uint8_t addr, uint16_t reg, uint16_t memAddress, uint8_t *buffer, uint16_t length);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halI2C__
