#ifndef __STM32_halI2C__
#define	__STM32_halI2C__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


#define HAL_I2C_ID_1              0
#define HAL_I2C_ID_2              1
#define HAL_I2C_ID_3              2
#define HAL_I2C_ID_4              3
#define HAL_I2C_ID_MAX            4


typedef struct {
	uint8_t id;
} I2CInitializeInfo;


void halI2CInitialize(const I2CInitializeInfo *pInfo);

void halI2CWriteMultiple(uint8_t id, uint8_t addr, uint16_t reg, uint16_t memAddress, uint8_t *buffer, uint16_t length);
void halI2CReadMultiple(uint8_t id, uint8_t addr, uint16_t reg, uint16_t memAddress, uint8_t *buffer, uint16_t length);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halI2C__
