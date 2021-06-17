#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halSPI.h"
#include "HAL/halTMR.h"
#include "Controllers/Display/Drivers/SSD1306/eosDisplayDriver_SSD1306.h"
#include "Controllers/Display/Drivers/SSD1306/eosSSD1306Defs.h"


using namespace eos;


IDisplayDriver* DisplayDriver_SSD1306::_instance = nullptr;
static SPIData __spiData;
static SPIHandler __hSpi;


/// ----------------------------------------------------------------------
/// \brief    Obte una instancia del driver
/// �\return  La instancia.
///
IDisplayDriver* DisplayDriver_SSD1306::getInstance() {

	if (_instance == nullptr)
		_instance = new DisplayDriver_SSD1306();
	return _instance;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
DisplayDriver_SSD1306::DisplayDriver_SSD1306() :
	_imageWidth(DISPLAY_IMAGE_WIDTH),
	_imageHeight(DISPLAY_IMAGE_HEIGHT) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void DisplayDriver_SSD1306::initialize() {

	hwInitialize();
}

void DisplayDriver_SSD1306::shutdown() {

}

void DisplayDriver_SSD1306::displayOn() {

}

void DisplayDriver_SSD1306::displayOff() {

}

void DisplayDriver_SSD1306::setOrientation(
    DisplayOrientation orientation) {

}

void DisplayDriver_SSD1306::clear(
    const Color &color) {

}

void DisplayDriver_SSD1306::setPixel(
    int x,
    int y,
    const Color &color) {

}


void DisplayDriver_SSD1306::setHPixels(
    int x,
    int y,
    int size,
    const Color &color) {

}


void DisplayDriver_SSD1306::setVPixels(
    int x,
    int y,
    int size,
    const Color &color) {

}


void DisplayDriver_SSD1306::setPixels(
    int x,
    int y,
    int width,
    int height,
    const Color &color) {

}


void DisplayDriver_SSD1306::writePixels(
    int x,
    int y,
    int width,
    int height,
    const uint8_t *pixels,
    ColorFormat format,
    int dx,
    int dy,
    int pitch) {

}


void DisplayDriver_SSD1306::readPixels(
    int x,
    int y,
    int width,
    int height,
    uint8_t *pixels,
    ColorFormat format,
    int dx,
    int dy,
    int pitch) {

}

void DisplayDriver_SSD1306::vScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

}

void DisplayDriver_SSD1306::hScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

}


void DisplayDriver_SSD1306::refresh() {

}


void DisplayDriver_SSD1306::hwInitialize() {

	// Inicialitza modul GPIO
	//
	static const GPIOPinSettings gpioSettings[] = {
#ifdef DISPLAY_RST_PIN
		{ DISPLAY_RST_PORT,    DISPLAY_RST_PIN,
			HAL_GPIO_MODE_OUTPUT | HAL_GPIO_INIT_CLR, 0 },
#endif
		{ DISPLAY_CS_PORT,     DISPLAY_CS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_SPEED_FAST | HAL_GPIO_INIT_SET, 0 },
		{ DISPLAY_RS_PORT,     DISPLAY_RS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_SPEED_FAST | HAL_GPIO_INIT_CLR, 0 },
		{ DISPLAY_CLK_PORT,    DISPLAY_CLK_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_CLK_AF },
#ifdef DISPLAY_MISO_PORT
		{ DISPLAY_MISO_PORT,   DISPLAY_MISO_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_MISO_AF},
#endif
		{ DISPLAY_MOSI_PORT,   DISPLAY_MOSI_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_MOSI_AF}
	};
	halGPIOInitializePins(gpioSettings, sizeof(gpioSettings) / sizeof(gpioSettings[0]));


	// Inicialitza el modul SPI
	//
	static const SPISettings spiSettings = {
		DISPLAY_SPI_ID,
			HAL_SPI_MODE_0 | HAL_SPI_MS_MASTER | HAL_SPI_FIRSTBIT_MSB | HAL_SPI_CLOCKDIV_16, 0, 0
	};
	__hSpi = halSPIInitialize(&__spiData, &spiSettings);


	// Inicialitza el display OLED
	//
	static const uint8_t oledCommands[] = {
		OP_CMD_DISPLAY_OFF,
		OP_CMD_SET_DISPLAY_CLOCK(0x80),
		OP_CMD_SET_MULTIPLEX_RATIO(DISPLAY_IMAGE_HEIGHT - 1),
		OP_CMD_SET_DISPLAY_OFFSET(0),
		OP_CMD_SET_START_LINE(0),
		OP_CMD_SET_MEMORY_MODE(0),
		OP_CMD_SET_SEGMENT_REMAP(1),
		OP_CMD_SET_COM_SCAN_DIR(1),
		OP_CMD_SET_COM_HARDWARE_CFG(0x12),
		OP_CMD_SET_CONTRAST_CONTROL(0x7F),
		OP_CMD_SET_PRECHARGE_PERIOD(0xF1),
		OP_END
	};

	hwOpen();
    const uint8_t *p = oledCommands;
	uint8_t c;
    while ((c = *p++) != OP_END) {
        switch (c) {
            case OP_DELAY:
                halTMRDelay(*p++);
                break;

            default:
                hwWriteCommand(*p++);
                while (--c != 0)
                    hwWriteCommand(*p++);
                break;
        }
    }
	hwClose();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el controlador OLED
///
void DisplayDriver_SSD1306::hwOpen() {

	halGPIOClearPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief    Deselecciona el controlador OLED
///
void DisplayDriver_SSD1306::hwClose() {

	halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte de comanda.
/// \param    cmd: La comanda.
///
void DisplayDriver_SSD1306::hwWriteCommand(
    uint8_t cmd) {

	halGPIOClearPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
	halSPISendBuffer(__hSpi, &cmd, sizeof(cmd));
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte de dades.
/// \param    cmd: Les dades.
///
void DisplayDriver_SSD1306::hwWriteData(
    uint8_t data) {

	halGPIOSetPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
	halSPISendBuffer(__hSpi, &data, sizeof(data));
}
