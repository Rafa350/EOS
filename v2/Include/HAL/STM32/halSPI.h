#ifndef __STM32_halSPI__
#define __STM32_halSPI__


#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t SPIModule;
typedef uint8_t SPIOptions;
typedef void (*SPIInterruptCallback)(SPIModule module, void *param);

typedef struct {
	SPIModule module;
	SPIOptions options;
	SPIInterruptCallback intCallback;
} SPIInitializeInfo;


#define HAL_SPI_MODULE_1	      0
#define HAL_SPI_MODULE_2          1
#define HAL_SPI_MODULE_3          2
#define HAL_SPI_MODULE_4          3
#define HAL_SPI_MODULE_5          4
#define HAL_SPI_MODULE_6          5

// Polaritat del rellotge
#define HAL_SPI_CPOL_MASK         0b00000001
#define HAL_SPI_CPOL_HIGH         0b00000000
#define HAL_SPI_CPOL_LOW          0b00000001

// Fase del rellotge
#define HAL_SPI_CPHA_MASK         0b00000010
#define HAL_SPI_CPHA_EDGE1        0b00000000
#define HAL_SPI_CPHA_EDGE2        0b00000010

#define HAL_SPI_MODE_MASK         (HAL_SPI_CPOL_MASK | HAL_SPI_CPHA_MASK)
#define HAL_SPI_MODE_0            (HAL_SPI_CPOL_LOW | HAL_SPI_CPHA_EDGE1)
#define HAL_SPI_MODE_1            (HAL_SPI_CPOL_LOW | HAL_SPI_CPHA_EDGE2)
#define HAL_SPI_MODE_2            (HAL_SPI_CPOL_HIGH | HAL_SPI_CPHA_EDGE1)
#define HAL_SPI_MODE_3            (HAL_SPI_CPOL_HIGH | HAL_SPI_CPHA_EDGE2)

// Tamany de les dades 8 o 16 bits
#define HAL_SPI_SIZE_MASK         0b00000100
#define HAL_SPI_SIZE_8            0b00000000
#define HAL_SPI_SIZE_16           0b00000100

// Modus Master/Slave
#define HAL_SPI_MS_MASK           0b00001000
#define HAL_SPI_MS_MASTER         0b00000000
#define HAL_SPI_MS_SLAVE          0b00001000

// Primer bit a transmetre o rebre
#define HAL_SPI_FIRSTBIT_MASK     0b00010000
#define HAL_SPI_FIRSTBIT_MSB      0b00000000
#define HAL_SPI_FIRSTBIT_LSB      0b00010000


extern void halSPIInitialize(SPIModule module, SPIOptions options);
extern uint8_t halSPISend(SPIModule module, uint8_t data);
extern uint16_t halSPISend16(SPIModule module, uint16_t data);
extern uint8_t halSPIReceive(SPIModule module);
extern uint16_t halSPIReceive16(SPIModule module);


#ifdef __cplusplus
}
#endif


#endif // __STM32_halSPI__
