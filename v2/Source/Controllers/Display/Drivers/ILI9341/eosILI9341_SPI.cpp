#include "eos.h"

#ifdef DISPLAY_DRV_ILI9341

#include "Controllers/Display/Drivers/eosILI9341.h"
#include "HAL/halSPI.h"
#include "HAL/halGPIO.h"


using namespace eos;


static SPIData spiData;
static SPIHandler hSPI = NULL;


/// ----------------------------------------------------------------------
/// \brief    Inicialitza les comunicacions.
/// \remarks  SPI baudrate is set to 5.6 MHz (PCLK2/SPI_BaudRatePrescaler = 90/16 = 5.625 MHz)
///           to verify these constraints:
///           - ILI9341 LCD SPI interface max baudrate is 10MHz for write and 6.66MHz for read
///           - PCLK2 frequency is set to 90 MHz
///
void ILI9341Driver::lcdInitialize() {

	static GPIOInitializePinInfo const gpioInit[] = {
#ifdef DISPLAY_RST_PORT
		{DISPLAY_RST_PORT,  DISPLAY_RST_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, 0                        },
#endif
		{DISPLAY_CS_PORT,   DISPLAY_CS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_SPEED_FAST | HAL_GPIO_INIT_SET, 0  },
		{DISPLAY_RS_PORT,   DISPLAY_RS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_SPEED_FAST | HAL_GPIO_INIT_CLR, 0  },
		{DISPLAY_CLK_PORT,  DISPLAY_CLK_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_CLK_AF            },
#ifdef DISPLAY_MISO_PORT
		{DISPLAY_MISO_PORT, DISPLAY_MISO_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_MISO_AF           },
#endif
		{DISPLAY_MOSI_PORT, DISPLAY_MOSI_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_MOSI_AF           }
	};

	static SPIInitializeInfo const spiInit = {
		DISPLAY_SPI_ID,
			HAL_SPI_MODE_0 | HAL_SPI_SIZE_8 | HAL_SPI_MS_MASTER |
			HAL_SPI_FIRSTBIT_MSB | HAL_SPI_CLOCKDIV_16, 0, 0
	};

	/// Inicialitza el modul GPIO
	//
	halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));

    // Inicialitza el modul SPI
    //
	hSPI = halSPIInitialize(&spiData, &spiInit);
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ILI9341Driver::lcdReset() {

#ifdef DISPLAY_RST_PORT
    halTMRDelay(10);
    halGPIOSetPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN);
    halTMRDelay(120);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ILI9341Driver::lcdOpen() {

    halGPIOClearPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ILI9341Driver::lcdClose() {

    halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda.
/// \param cmd: El byte a escriure.
///
void ILI9341Driver::lcdWriteCommand(
    uint8_t cmd) {

    halGPIOClearPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
    halSPISendBuffer(hSPI, &cmd, sizeof(cmd));
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades.
/// \param data: El byte a escriure.
///
void ILI9341Driver::lcdWriteData(
    uint8_t data) {

    halGPIOSetPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
    halSPISendBuffer(hSPI, &data, sizeof(data));
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una cadena de dades.
/// \param    data: Buffer de dades.
/// \param    cocunt: Numero de bytes en el buffer.
///
void ILI9341Driver::lcdWriteData(
	uint8_t *data,
	int count) {

    halGPIOSetPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
    halSPISendBuffer(hSPI, data, count);
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un byte de dades.
/// \return El byte lleigit.
///
uint8_t ILI9341Driver::lcdReadData() {

#ifdef DISPLAY_MISO_PORT

	//return halSPIRead(DISPLAY_SPI_MODULE);
	return 0;

#else
	return 0;
#endif
}


#endif // USE_DISPLAY_ILI9341
