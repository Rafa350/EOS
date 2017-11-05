#ifndef __STM32_halSPI__
#define __STM32_halSPI__


// Standard includes
//
#include <stdint.h>
#include <stdbool.h>


#ifdef	__cplusplus
extern "C" {
#endif


typedef void (*SPIInterruptCallback)(uint8_t module, void *params);

typedef struct {                       // Parametres d'inicialitzacio
	uint8_t id;                        // -Modul a inicialitzar
	uint32_t options;                  // -Opcions
	uint8_t clockDiv;                  // -Divisor del rellotge
	SPIInterruptCallback intFunction;  // -Funcio d'interrupcio
	void *intParams;                   // -Parametres de la funcio d'interrupcio
} SPIInitializeInfo;


#define HAL_SPI_ID_1	      	  0
#define HAL_SPI_ID_2          	  1
#define HAL_SPI_ID_3              2
#define HAL_SPI_ID_4              3
#define HAL_SPI_ID_5              4
#define HAL_SPI_ID_6              5
#define HAL_SPI_ID_MAX            6

// Polaritat del rellotge
#define HAL_SPI_CPOL_MASK         0x00000001
#define HAL_SPI_CPOL_HIGH         0x00000000
#define HAL_SPI_CPOL_LOW          0x00000001

// Fase del rellotge
#define HAL_SPI_CPHA_MASK         0x00000002
#define HAL_SPI_CPHA_EDGE1        0x00000000
#define HAL_SPI_CPHA_EDGE2        0x00000002

// Modus: Combinat de CPOL i CPHA
#define HAL_SPI_MODE_MASK         (HAL_SPI_CPOL_MASK | HAL_SPI_CPHA_MASK)
#define HAL_SPI_MODE_0            (HAL_SPI_CPOL_LOW | HAL_SPI_CPHA_EDGE1)
#define HAL_SPI_MODE_1            (HAL_SPI_CPOL_LOW | HAL_SPI_CPHA_EDGE2)
#define HAL_SPI_MODE_2            (HAL_SPI_CPOL_HIGH | HAL_SPI_CPHA_EDGE1)
#define HAL_SPI_MODE_3            (HAL_SPI_CPOL_HIGH | HAL_SPI_CPHA_EDGE2)

// Tamany de les dades 8 o 16 bits
#define HAL_SPI_SIZE_MASK         0x00000004
#define HAL_SPI_SIZE_8            0x00000000
#define HAL_SPI_SIZE_16           0x00000004

// Modus Master/Slave
#define HAL_SPI_MS_MASK           0x00000008
#define HAL_SPI_MS_MASTER         0x00000000
#define HAL_SPI_MS_SLAVE          0x00000008

// Primer bit a transmetre
#define HAL_SPI_FIRSTBIT_MASK     0x00000010
#define HAL_SPI_FIRSTBIT_MSB      0x00000000
#define HAL_SPI_FIRSTBIT_LSB      0x00000010

// CRC automatic
#define HAL_SPI_CRC_MASK          0x00000020
#define HAL_SPI_CRC_DISABLED      0x00000000
#define HAL_SPI_CRC_ENABLED       0x00000020

// Divisor del rellotge
#define HAL_SPI_CLOCKDIV_2        0
#define HAL_SPI_CLOCKDIV_4        1
#define HAL_SPI_CLOCKDIV_8        2
#define HAL_SPI_CLOCKDIV_16       3
#define HAL_SPI_CLOCKDIV_32       4
#define HAL_SPI_CLOCKDIV_64       5
#define HAL_SPI_CLOCKDIV_128      6
#define HAL_SPI_CLOCKDIV_256      7


// Funcions d'inicialitzacio
void halSPIInitialize(const SPIInitializeInfo *info);
void halSPIShutdown(uint8_t id);

// Funcions de control
bool halSPIIsBusy(uint8_t id);

void halSPISendBuffer(uint8_t id, uint8_t *data, uint16_t size);
void halSPIReceiveBuffer(uint8_t id, uint8_t *data, uint16_t size);
void halSPITransmitBuffer(uint8_t id, uint8_t *txDatar, uint8_t *rxDatar, uint16_t size);


#ifdef __cplusplus
}
#endif


#endif // __STM32_halSPI__
