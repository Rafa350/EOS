#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halSPI.h"
#include "HAL/halTMR.h"
#include "Controllers/Display/Drivers/eosSSD1306.h"
#include "Controllers/Display/Drivers/eosSSD1306Defs.h"


using namespace eos;


IDisplayDriver* SSD1306Driver::_instance = nullptr;
SPIData spiData;


/// ----------------------------------------------------------------------
/// \brief    Obte una instancia del driver
/// �\return  La instancia.
///
IDisplayDriver* SSD1306Driver::getInstance() {

	if (_instance == nullptr)
		_instance = new SSD1306Driver();
	return _instance;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
SSD1306Driver::SSD1306Driver() :
	_screenWidth(DISPLAY_SCREEN_WIDTH),
	_screenHeight(DISPLAY_SCREEN_HEIGHT) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SSD1306Driver::initialize() {

	oledInitialize();
}

void SSD1306Driver::shutdown() {

}

void SSD1306Driver::displayOn() {

}

void SSD1306Driver::displayOff() {

}

void SSD1306Driver::setOrientation(
    DisplayOrientation orientation) {

}

void SSD1306Driver::clear(
    const Color &color) {

}

void SSD1306Driver::setPixel(
    int x,
    int y,
    const Color &color) {

}


void SSD1306Driver::setHPixels(
    int x,
    int y,
    int size,
    const Color &color) {

}


void SSD1306Driver::setVPixels(
    int x,
    int y,
    int size,
    const Color &color) {

}


void SSD1306Driver::setPixels(
    int x,
    int y,
    int width,
    int height,
    const Color &color) {

}


void SSD1306Driver::writePixels(
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


void SSD1306Driver::readPixels(
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

void SSD1306Driver::vScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

}

void SSD1306Driver::hScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

}


void SSD1306Driver::refresh() {

}


void SSD1306Driver::oledInitialize() {

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
	_hSpi = halSPIInitialize(&spiData, &spiSettings);


	// Inicialitza el display OLED
	//
	static const uint8_t oledCommands[] = {
		OP_CMD_DISPLAY_OFF,
		OP_CMD_SET_DISPLAY_CLOCK(0x80),
		OP_CMD_SET_MULTIPLEX_RATIO(DISPLAY_SCREEN_HEIGHT - 1),
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

	oledSelect();
    const uint8_t *p = oledCommands;
	uint8_t c;
    while ((c = *p++) != OP_END) {
        switch (c) {
            case OP_DELAY:
                halTMRDelay(*p++);
                break;

            default:
                oledWriteCommand(*p++);
                while (--c != 0)
                    oledWriteData(*p++);
                break;
        }
    }
	oledUnselect();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el controlador OLED
///
void SSD1306Driver::oledSelect() {

	halGPIOClearPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief    Deselecciona el controlador OLED
///
void SSD1306Driver::oledUnselect() {

	halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte de comanda.
/// \param    cmd: La comanda.
///
void SSD1306Driver::oledWriteCommand(
    uint8_t cmd) {

	halGPIOClearPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
	halSPISendBuffer(_hSpi, &cmd, sizeof(cmd));
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte de dades.
/// \param    cmd: Les dades.
///
void SSD1306Driver::oledWriteData(
    uint8_t data) {

	halGPIOSetPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
	halSPISendBuffer(_hSpi, &data, sizeof(data));
}
