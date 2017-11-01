#ifndef __STM32_halSPI__
#define __STM32_halSPI__


// Standard includes
//
#include <stdint.h>


// STM32 includes
//
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t SPIModule;
typedef uint8_t SPIOptions;
typedef void *SPIInterruptParams;
typedef void (*SPIInterruptFunction)(SPIModule module, SPIInterruptParams params);

typedef struct {                       // Parametres d'inicialitzacio
	SPIModule module;                  // -Modul a inicialitzar
	SPIOptions options;                // -Opcions
	SPIInterruptFunction intFunction;  // -Funcio d'interrupcio
	SPIInterruptParams intParams;      // -Parametres de la funcio d'interrupcio
} SPIInitializeInfo;


#define HAL_SPI_MODULE_1	      0
#define HAL_SPI_MODULE_2          1
#define HAL_SPI_MODULE_3          2
#define HAL_SPI_MODULE_4          3
#define HAL_SPI_MODULE_5          4
#define HAL_SPI_MODULE_6          5
#define HAL_SPI_MAX_MODULES       6

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


extern void halSPIInitialize(const SPIInitializeInfo *info);
extern uint8_t halSPITransmit(SPIModule module, uint8_t data);
extern uint16_t halSPITransmit16(SPIModule module, uint16_t data);


#ifdef __cplusplus
}
#endif


#endif // __STM32_halSPI__
