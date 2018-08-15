#include "eos.h"


#ifdef ILI9341_IO_TYPE_SPI


#include "Controllers/Display/Drivers/eosILI9341.h"
#include "hal/halSPI.h"
#include "hal/halGPIO.h"
#include "hal/halTMR.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Inicialitza les comunicacions.
///
void ILI9341Driver::lcdInitialize() {

	static const GPIOInitializePinInfo gpioInit[] = {
#ifdef ILI9341_RST_PORT
		{ILI9341_RST_PORT,  ILI9341_RST_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, 0              },
#endif
		{ILI9341_CS_PORT,   ILI9341_CS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_SET, 0              },
		{ILI9341_RS_PORT,   ILI9341_RS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, 0              },
		{ILI9341_CLK_PORT,  ILI9341_CLK_PIN,
			HAL_GPIO_MODE_ALT_PP,                   ILI9341_CLK_AF },
#ifdef ILI9341_MISO_PORT
		{ILI9341_MISO_PORT, ILI9341_MISO_PIN,
			HAL_GPIO_MODE_ALT_PP,                   ILI9341_MISO_AF},
#endif
		{ILI9341_MOSI_PORT, ILI9341_MOSI_PIN,
			HAL_GPIO_MODE_ALT_PP,                   ILI9341_MOSI_AF}
	};

	static const SPIInitializeInfo spiInit = {
		ILI9341_SPI_ID,
			HAL_SPI_MODE_0 | HAL_SPI_MS_MASTER | HAL_SPI_FIRSTBIT_MSB, HAL_SPI_CLOCKDIV_4, 0, 0
	};

	/// Inicialitza el modul GPIO
	//
	halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));

    // Inicialitza el modul SPI
    //
	halSPIInitialize(&spiInit);
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ILI9341Driver::lcdReset() {

#ifdef ILI9341_RST_PORT
    halTMRDelay(10);
    halGPIOSetPin(ILI9341_RST_PORT, ILI9341_RST_PIN);
    halTMRDelay(120);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ILI9341Driver::lcdOpen() {

    halGPIOClearPin(ILI9341_CS_PORT, ILI9341_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ILI9341Driver::lcdClose() {

    halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda.
/// \param cmd: El byte a escriure.
///
void ILI9341Driver::lcdWriteCommand(
    uint8_t cmd) {

    halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN);
    halSPISendBuffer(ILI9341_SPI_ID, &cmd, sizeof(cmd));
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades.
/// \param data: El byte a escriure.
///
void ILI9341Driver::lcdWriteData(
    uint8_t data) {

    halGPIOSetPin(ILI9341_RS_PORT, ILI9341_RS_PIN);
    halSPISendBuffer(ILI9341_SPI_ID, &data, sizeof(data));
}


/// ----------------------------------------------------------------------
/// \brief Escriu una cadena de dades.
/// \param d: Buffer de dades.
/// \param length: Numero de bytestes en la cadena.
///
void ILI9341Driver::lcdWriteData(
	uint8_t *data,
	int32_t size) {

    halGPIOSetPin(ILI9341_RS_PORT, ILI9341_RS_PIN);
    halSPISendBuffer(ILI9341_SPI_ID, data, size);
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un byte de dades.
/// \return El byte lleigit.
///
uint8_t ILI9341Driver::lcdReadData() {

#ifdef ILI9341_MISO_PORT

	//return halSPIRead(ILI9341_SPI_MODULE);
	return 0;

#else
	return 0;
#endif
}


#endif

