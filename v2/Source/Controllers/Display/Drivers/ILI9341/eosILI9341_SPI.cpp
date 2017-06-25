#include "eos.h"

 
#ifdef ILI9341_IO_TYPE_SPI

#include "Controllers/Display/Drivers/eosILI9341.h"

#ifdef ILI9341_IO_SUBTYPE_SPI_HAL
#include "hal/halSPI.h"
#include "hal/halGPIO.h"
#include "hal/halINT.h"
#include "hal/halTMR.h"
#endif


#if defined(ILI9341_IO_SUBTYPE_SPI_HAL)

// Control del pin RST
//
#ifdef ILI9341_RST_PORT
#define initRST()  halGPIOClearPin(ILI9341_RST_PORT, ILI9341_RST_PIN); \
                   halGPIOInitializePin(ILI9341_RST_PORT, ILI9341_RST_PIN, HAL_GPIO_MODE_OUTPUT)

#define setRST()   halGPIOSetPin(ILI9341_RST_PORT, ILI9341_RST_PIN)

#define clrRST()   halGPIOClearPin(ILI9341_RST_PORT, ILI9341_RST_PIN)
#endif

// Control del pin CS
//
#define initCS()   halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN); \
                   halGPIOInitializePin(ILI9341_CS_PORT, ILI9341_CS_PIN, HAL_GPIO_MODE_OUTPUT)

#define setCS()    halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN)

#define clrCS()    halGPIOClearPin(ILI9341_CS_PORT, ILI9341_CS_PIN)

// Control del pin RS
//
#define initRS()   halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN); \
                   halGPIOInitializePin(ILI9341_RS_PORT, ILI9341_RS_PIN, HAL_GPIO_MODE_OUTPUT)

#define setRS()    halGPIOSetPin(ILI9341_RS_PORT, ILI9341_RS_PIN)

#define clrRS()    halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN)


// Control del modul SPI
//
#define initSPI()  halGPIOInitializePin(ILI9341_CLK_PORT, ILI9341_CLK_PIN, HAL_GPIO_MODE_ALTERNATE | HAL_GPIO_SPEED_HIGH); \
	               halGPIOInitializeAlternatePin(ILI9341_CLK_PORT, ILI9341_CLK_PIN, ILI9341_GPIO_AF_SPI); \
                   halGPIOInitializePin(ILI9341_MISO_PORT, ILI9341_MISO_PIN, HAL_GPIO_MODE_ALTERNATE | HAL_GPIO_SPEED_HIGH); \
	               halGPIOInitializeAlternatePin(ILI9341_MISO_PORT, ILI9341_MISO_PIN, ILI9341_GPIO_AF_SPI); \
                   halGPIOInitializePin(ILI9341_MOSI_PORT, ILI9341_MOSI_PIN, HAL_GPIO_MODE_ALTERNATE | HAL_GPIO_SPEED_HIGH); \
	               halGPIOInitializeAlternatePin(ILI9341_MOSI_PORT, ILI9341_MOSI_PIN, ILI9341_GPIO_AF_SPI); \
				   halSPIInitialize(ILI9341_SPI_MODULE, HAL_SPI_MODE_0 | HAL_SPI_MS_MASTER | HAL_SPI_FIRSTBIT_MSB)

#define sendSPI(d) halSPISend(ILI9341_SPI_MODULE, d)

#define recvSPI()  halSPISend(ILI9341_SPI_MODULE, 0)


#endif


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Inicialitza les comunicacions.
///
void ILI9341_Driver::ioInitialize() {

#ifdef ILI9341_RST_PORT
    initRST();
#endif
    initCS();
    initRS();
    initSPI();
#ifndef ILI9341_INTERFACE_WRITEONLY
    initMISO();
#endif
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ILI9341_Driver::ioReset() {

#ifdef ILI9341_RST_PORT
    halTMRDelay(10);
    setRST();
    halTMRDelay(120);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ILI9341_Driver::ioBegin() {

	clrCS();
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ILI9341_Driver::ioEnd() {

    setCS();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda.
/// \param d: El byte a escriure.
///
void ILI9341_Driver::ioWriteCommand(
    uint8_t d) {

    halINTDisableInterrupts();

    clrRS();
    sendSPI(d);

    halINTEnableInterrupts();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades.
/// \param d: El byte a escriure.
///
void ILI9341_Driver::ioWriteData(
    uint8_t d) {

    halINTDisableInterrupts();

    setRS();
    sendSPI(d);

    halINTEnableInterrupts();
}

/// ----------------------------------------------------------------------
/// \brief Llegeix un byte de dades.
/// \return El byte lleigit.
///
uint8_t ILI9341_Driver::ioReadData() {

#ifdef ILI9341_INTERFACE_WRITEONLY

	return 0;

#else

    uint8_t data = recvSPI();

    return data;

#endif
}


#endif

