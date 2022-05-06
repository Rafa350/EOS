#ifndef __STM32_halI2C__
#define	__STM32_halI2C__


// HAL includes
//
#include "HAL/hal.h"


// Identificador del canal I2C
#define HAL_I2C_CHANNEL_1         0
#define HAL_I2C_CHANNEL_2         1
#define HAL_I2C_CHANNEL_3         2
#define HAL_I2C_CHANNEL_4         3
#define HAL_I2C_CHANNEL_NONE      ((I2CChannel) -1)


// Opcions: Interrupcio activa
#define HAL_I2C_INT_pos           0
#define HAL_I2C_INT_bits          0x1
#define HAL_I2C_INT_mask          (HAL_I2C_INT_bits << HAL_I2C_INT_pos)

#define HAL_I2C_INT_DISABLE       (0 << HAL_I2C_INT_pos)
#define HAL_I2C_INT_ENABLE        (1 << HAL_I2C_INT_pos)

// Resultats
#define HAL_I2C_OK                0    // Tot correcte
#define HAL_I2C_ERR               1    // Error generic
#define HAL_I2C_ERR_TIMEOUT       2    // Superat el temps limit
#define HAL_I2C_ERR_BUSY          3    // Ocupat


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint32_t halI2CChannel;
typedef uint32_t halI2COptions;
typedef uint32_t halI2CResult;
typedef struct __halI2CData *halI2CHandler;
typedef void (*halI2CInterruptFunction)(halI2CHandler handler, void *params);

struct __halI2CData {
	I2C_TypeDef *device;
	I2C_HandleTypeDef handle;
	halI2CInterruptFunction isrFunction;
	void *isrParams;
};
typedef struct __halI2CData halI2CData;

typedef struct {
	halI2CChannel channel;
	halI2COptions options;
	halI2CInterruptFunction isrFunction;
	void *isrParams;
} halI2CMasterInitializeInfo;



halI2CResult halI2CMasterInitialize(halI2CData *data, const halI2CMasterInitializeInfo *info, halI2CHandler *handler);
halI2CResult halI2CDeinitialize();

halI2CResult halI2CEnable(halI2CHandler handler);
halI2CResult halI2CDisable(halI2CHandler handler);

halI2CResult halI2CMasterSend(halI2CHandler handler, uint8_t addr, const void *data, int size, unsigned blockTime);
halI2CResult halI2CMasterReceive(halI2CHandler handler, uint8_t addr, void *data, int size, unsigned blockTime);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halI2C__
