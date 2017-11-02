#include "eos.h"


#ifdef ILI9341_IO_TYPE_SPI

#if !defined(ILI9341_IO_SUBTYPE_SPI_HAL) && \
	!defined(ILI9341_IO_SUBTYPE_SPI_DIRECT)
#error No se especifico ILI9341_IO_SUBTYPE_SIO_xxx.
#endif

#include "Controllers/Display/Drivers/eosILI9341.h"

#ifdef ILI9341_IO_SUBTYPE_SPI_HAL
#include "hal/halSPI.h"
#include "hal/halGPIO.h"
#include "hal/halTMR.h"
#endif


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Inicialitza les comunicacions.
///
void ILI9341_Driver::lcdInitialize() {

	static const GPIOInitializePinInfo gpioInit[] = {
#ifdef ILI9341_RST_PORT
		{ILI9341_RST_PORT,  ILI9341_RST_PIN,  HAL_GPIO_MODE_OUTPUT,   0              },
#endif
		{ILI9341_CS_PORT,   ILI9341_CS_PIN,   HAL_GPIO_MODE_OUTPUT,   0              },
		{ILI9341_RS_PORT,   ILI9341_RS_PIN,   HAL_GPIO_MODE_OUTPUT,   0              },
		{ILI9341_CLK_PORT,  ILI9341_CLK_PIN,  HAL_GPIO_MODE_FUNCTION, ILI9341_CLK_AF },
		{ILI9341_MISO_PORT, ILI9341_MISO_PIN, HAL_GPIO_MODE_FUNCTION, ILI9341_MISO_AF},
		{ILI9341_MOSI_PORT, ILI9341_MOSI_PIN, HAL_GPIO_MODE_FUNCTION, ILI9341_MOSI_AF}
	};

	/// Inicialitza el modul GPIO
	//
#ifdef ILI9341_RST_PORT
    halGPIOClearPin(ILI9341_RST_PORT, ILI9341_RST_PIN);
#endif
	halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN);
    halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN);
	halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));

    // Inicialitza el modul SPI
    //
	SPIInitializeInfo spiInfo;
	spiInfo.module = ILI9341_SPI_MODULE;
	spiInfo.options = HAL_SPI_MODE_0 | HAL_SPI_MS_MASTER | HAL_SPI_FIRSTBIT_MSB;
	halSPIInitialize(&spiInfo);
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ILI9341_Driver::lcdReset() {

#ifdef ILI9341_RST_PORT
    halTMRDelay(10);
    halGPIOSetPin(ILI9341_RST_PORT, ILI9341_RST_PIN);
    halTMRDelay(120);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ILI9341_Driver::lcdOpen() {

    halGPIOClearPin(ILI9341_CS_PORT, ILI9341_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ILI9341_Driver::lcdClose() {

    while (halSPIIsBusy(ILI9341_SPI_MODULE))
    	continue;

    halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda.
/// \param d: El byte a escriure.
///
void ILI9341_Driver::lcdWriteCommand(
    uint8_t d) {

    halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN);
    halSPIFastTransmit(ILI9341_SPI_MODULE, d);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades.
/// \param d: El byte a escriure.
///
void ILI9341_Driver::lcdWriteData(
    uint8_t d) {

    halGPIOSetPin(ILI9341_RS_PORT, ILI9341_RS_PIN);
    halSPIFastTransmit(ILI9341_SPI_MODULE, d);
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un byte de dades.
/// \return El byte lleigit.
///
uint8_t ILI9341_Driver::lcdReadData() {

#ifdef ILI9341_INTERFACE_WRITEONLY

	return 0;

#else

    uint8_t data = halSPITransmit(ILI9341_SPI_MODULE, 0);

    return data;

#endif
}


#endif

