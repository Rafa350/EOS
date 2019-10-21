#ifndef __STM32_halSPI__
#define __STM32_halSPI__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef void (*SPIInterruptCallback)(uint8_t id, void *params);

typedef struct {                       // Parametres d'inicialitzacio
	uint8_t id;                        // -Modul a inicialitzar
	uint32_t options;                  // -Opcions
	uint8_t clockDiv;                  // -Divisor del rellotge
	SPIInterruptCallback intFunction;  // -Funcio d'interrupcio
	void *intParams;                   // -Parametres de la funcio d'interrupcio
} SPIInitializeInfo;


#define HAL_SPI_ID_1	      	  0u
#define HAL_SPI_ID_2          	  1u
#define HAL_SPI_ID_3              2u
#define HAL_SPI_ID_4              3u
#define HAL_SPI_ID_5              4u
#define HAL_SPI_ID_6              5u
#define HAL_SPI_ID_MAX            6u

// Polaritat del rellotge
#define HAL_SPI_CPOL_pos          0u
#define HAL_SPI_CPOL_bits         0b1u
#define HAL_SPI_CPOL_mask         (HAL_SPI_CPOL_bits << HAL_SPI_CPOL_pos)

#define HAL_SPI_CPOL_HIGH         (0u << HAL_SPI_CPOL_pos)
#define HAL_SPI_CPOL_LOW          (1u << HAL_SPI_CPOL_pos)

// Fase del rellotge
#define HAL_SPI_CPHA_pos          1u
#define HAL_SPI_CPHA_bits         0b1u
#define HAL_SPI_CPHA_mask         (HAL_SPI_CPHA_bits << HAL_SPI_CPHA_pos)

#define HAL_SPI_CPHA_EDGE1        (0u << HAL_SPI_CPHA_pos)
#define HAL_SPI_CPHA_EDGE2        (1u << HAL_SPI_CPHA_pos)

// Modus: Combinat de CPOL i CPHA
#define HAL_SPI_MODE_mask         (HAL_SPI_CPOL_mask | HAL_SPI_CPHA_nask)

#define HAL_SPI_MODE_0            (HAL_SPI_CPOL_LOW | HAL_SPI_CPHA_EDGE1)
#define HAL_SPI_MODE_1            (HAL_SPI_CPOL_LOW | HAL_SPI_CPHA_EDGE2)
#define HAL_SPI_MODE_2            (HAL_SPI_CPOL_HIGH | HAL_SPI_CPHA_EDGE1)
#define HAL_SPI_MODE_3            (HAL_SPI_CPOL_HIGH | HAL_SPI_CPHA_EDGE2)

// Tamany de les dades 8 o 16 bits
#define HAL_SPI_SIZE_pos          2u
#define HAL_SPI_SIZE_bits         0b1u
#define HAL_SPI_SIZE_mask         0x00000004u

#define HAL_SPI_SIZE_8            0x00000000u
#define HAL_SPI_SIZE_16           0x00000004u

// Modus Master/Slave
#define HAL_SPI_MS_mask           0x00000008u

#define HAL_SPI_MS_MASTER         0x00000000u
#define HAL_SPI_MS_SLAVE          0x00000008u

// Primer bit a transmetre
#define HAL_SPI_FIRSTBIT_mask     0x00000010u

#define HAL_SPI_FIRSTBIT_MSB      0x00000000u
#define HAL_SPI_FIRSTBIT_LSB      0x00000010u

// CRC automatic
#define HAL_SPI_CRC_mask          0x00000020u

#define HAL_SPI_CRC_DISABLED      0x00000000u
#define HAL_SPI_CRC_ENABLED       0x00000020u

// Divisor del rellotge
#define HAL_SPI_CLOCKDIV_2        0u
#define HAL_SPI_CLOCKDIV_4        1u
#define HAL_SPI_CLOCKDIV_8        2u
#define HAL_SPI_CLOCKDIV_16       3u
#define HAL_SPI_CLOCKDIV_32       4u
#define HAL_SPI_CLOCKDIV_64       5u
#define HAL_SPI_CLOCKDIV_128      6u
#define HAL_SPI_CLOCKDIV_256      7u


// Funcions d'inicialitzacio
void halSPIInitialize(const SPIInitializeInfo *info);
void halSPIShutdown(uint8_t id);

// Funcions de control
bool halSPIIsBusy(uint8_t id);

void halSPISendBuffer(uint8_t id, uint8_t *data, uint16_t size);
void halSPIReceiveBuffer(uint8_t id, uint8_t *data, uint16_t size);
void halSPITransmitBuffer(uint8_t id, uint8_t *txData, uint8_t *rxData, uint16_t size);


#ifdef __cplusplus
}
#endif


#endif // __STM32_halSPI__
