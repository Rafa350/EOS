#ifndef __PIC32_halSPI__
#define __PIC32_halSPI__


// EOS includes
//
#include "eos.h"


// Identificador dels canals
#define HAL_SPI_CHANNEL_1         0
#ifdef _SPI2
#define HAL_SPI_CHANNEL_2         1
#endif
#ifdef _SPI3
#define HAL_SPI_CHANNEL_3         2
#endif
#ifdef _SPI4
#define HAL_SPI_CHANNEL_4         3
#endif
#ifdef _SPI5
#define HAL_SPI_CHANNEL_5         4
#endif
#define HAL_SPI_CHANNEL_NONE      0xFFFFFFFF


// Opcions: Polaritat del rellotge (CPOL)
#define HAL_SPI_CPOL_pos          0
#define HAL_SPI_CPOL_bits         0b1
#define HAL_SPI_CPOL_mask         (HAL_SPI_CPOL_bits << HAL_SPI_CPOL_pos)

#define HAL_SPI_CPOL_HIGH         (0 << HAL_SPI_CPOL_pos)
#define HAL_SPI_CPOL_LOW          (1 << HAL_SPI_CPOL_pos)

// Opcions: Fase del rellotge (CPHA)
#define HAL_SPI_CPHA_pos          1
#define HAL_SPI_CPHA_bits         0b1
#define HAL_SPI_CPHA_mask         (HAL_SPI_CPHA_bits << HAL_SPI_CPHA_pos)

#define HAL_SPI_CPHA_EDGE1        (0 << HAL_SPI_CPHA_pos)
#define HAL_SPI_CPHA_EDGE2        (1 << HAL_SPI_CPHA_pos)

// Opcions: Modus (Combinat de CPOL i CPHA)
#define HAL_SPI_MODE_mask         (HAL_SPI_CPOL_mask | HAL_SPI_CPHA_nask)

#define HAL_SPI_MODE_0            (HAL_SPI_CPOL_LOW | HAL_SPI_CPHA_EDGE1)
#define HAL_SPI_MODE_1            (HAL_SPI_CPOL_LOW | HAL_SPI_CPHA_EDGE2)
#define HAL_SPI_MODE_2            (HAL_SPI_CPOL_HIGH | HAL_SPI_CPHA_EDGE1)
#define HAL_SPI_MODE_3            (HAL_SPI_CPOL_HIGH | HAL_SPI_CPHA_EDGE2)

// Opcions: Tamany de les dades 8 o 16 bits
#define HAL_SPI_SIZE_pos          2
#define HAL_SPI_SIZE_bits         0b1
#define HAL_SPI_SIZE_mask         (HAL_SPI_SIZE_bits << HAL_SPI_SIZE_pos)

#define HAL_SPI_SIZE_8            (0 << HAL_SPI_SIZE_pos)
#define HAL_SPI_SIZE_16           (1 << HAL_SPI_SIZE_pos)

// Opcions: Modus Master/Slave
#define HAL_SPI_MS_pos            3
#define HAL_SPI_MS_bits           0b1
#define HAL_SPI_MS_mask           (HAL_SPI_MS_bits << HAL_SPI_MS_pos)

#define HAL_SPI_MS_MASTER         (0 << HAL_SPI_MS_pos)
#define HAL_SPI_MS_SLAVE          (1 << HAL_SPI_MS_pos)

// Opcions: Primer bit a transmetre
#define HAL_SPI_FIRSTBIT_pos      4
#define HAL_SPI_FIRSTBIT_bits     0b1
#define HAL_SPI_FIRSTBIT_mask     (HAL_SPI_FIRSTBIT_bits << HAL_SPI_FIRSTBIT_pos)

#define HAL_SPI_FIRSTBIT_MSB      (0 << HAL_SPI_FIRSTBIT_pos)
#define HAL_SPI_FIRSTBIT_LSB      (1 << HAL_SPI_FIRSTBIT_pos)

// Opcions: CRC automatic
#define HAL_SPI_CRC_pos           5
#define HAL_SPI_CRC_bits          0b1
#define HAL_SPI_CRC_mask          (HAL_SPI_CRC_bits << HAL_SPI_CRC_pos)

#define HAL_SPI_CRC_DISABLED      (0 << HAL_SPI_CRC_pos)
#define HAL_SPI_CRC_ENABLED       (0 << HAL_SPI_CRC_pos)

// Opcions: Divisor del rellotge
#define HAL_SPI_CLOCKDIV_pos      6
#define HAL_SPI_CLOCKDIV_bits     0b111
#define HAL_SPI_CLOCKDIV_mask     (HAL_SPI_CLOCKDIV_bits << HAL_SPI_CLOCKDIV_pos)

#define HAL_SPI_CLOCKDIV_2        (0 << HAL_SPI_CLOCKDIV_pos)
#define HAL_SPI_CLOCKDIV_4        (1 << HAL_SPI_CLOCKDIV_pos)
#define HAL_SPI_CLOCKDIV_8        (2 << HAL_SPI_CLOCKDIV_pos)
#define HAL_SPI_CLOCKDIV_16       (3 << HAL_SPI_CLOCKDIV_pos)
#define HAL_SPI_CLOCKDIV_32       (4 << HAL_SPI_CLOCKDIV_pos)
#define HAL_SPI_CLOCKDIV_64       (5 << HAL_SPI_CLOCKDIV_pos)
#define HAL_SPI_CLOCKDIV_128      (6 << HAL_SPI_CLOCKDIV_pos)
#define HAL_SPI_CLOCKDIV_256      (7 << HAL_SPI_CLOCKDIV_pos)


#ifdef	__cplusplus
extern "C" {
#endif

typedef uint32_t SPIChannel;
typedef uint32_t SPIOptions;
typedef struct __SPIData* SPIHandler;
typedef void (*SPIInterruptFunction)(SPIHandler handler, void *params);

typedef struct  __attribute__((packed , aligned(4))) {
    volatile uint32_t SPIxCON;
    volatile uint32_t SPIxCONCLR;
    volatile uint32_t SPIxCONSET;
    volatile uint32_t SPIxCONINV;
#ifdef SPI1CON2
    volatile uint32_t SPIxCON2;
    volatile uint32_t SPIxCON2CLR;
    volatile uint32_t SPIxCON2SET;
    volatile uint32_t SPIxCON2INV;
#endif
    volatile uint32_t SPIxSTAT;
    volatile uint32_t SPIxSTATCLR;
    volatile uint32_t SPIxSTATSET;
    volatile uint32_t SPIxSTATINV;
    volatile uint32_t SPIxBUF;
    volatile uint32_t stace[3];
    volatile uint32_t SPIxBRG;
    volatile uint32_t SPIxBRGCLR;
    volatile uint32_t SPIxBRGSET;
    volatile uint32_t SPIxBRGINV;
} SPIRegisters;

struct __SPIData {
    SPIRegisters *regs;
    SPIInterruptFunction isrFunction;
    void* isrParams;
};
typedef struct __SPIData SPIData;

typedef struct {                       // Parametres d'inicialitzacio
	SPIChannel channel;                // -Identificador del dispositiu.
	SPIOptions options;                // -Opcions
	SPIInterruptFunction isrFunction;  // -Funcio d'interrupcio
	void *isrParams;                   // -Parametres de la funcio d'interrupcio
} SPISettings;



SPIHandler halSPIInitialize(SPIData* data, const SPISettings *settings);
void halSPIDeinitialize(SPIHandler handler);

bool halSPIIsBusy(SPIHandler handler);

void halSPISendBuffer(SPIHandler handler, uint8_t *data, uint32_t size);
void halSPIReceiveBuffer(SPIHandler handler, uint8_t *data, uint32_t size);
void halSPITransmitBuffer(SPIHandler handler, uint8_t *txData, uint8_t *rxData, uint32_t size);

void halSPISetInterruptFunction(SPIHandler handler, SPIInterruptFunction function, void* params);
void halSPIInterruptHandler(SPIHandler handler);

void halSPIEnableInterrupts(SPIHandler handler, uint32_t events);
uint32_t halSPIDisableInterrupts(SPIHandler handler, uint32_t events);

bool halSPIGetInterruptFlag(SPIHandler handler, uint32_t event);
void halSPIClearInterruptFlags(SPIHandler handler, uint32_t events);


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halSPI__

