#include "eos.h"
#include "Controllers/Display/Drivers/ILI9341/eosDisplayDriver_ILI9341LTDC.h"
#include "Controllers/Display/Drivers/ILI9341/eosILI9341Defs.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HAL/halINT.h"
#include "hAL/halTMR.h"
#include "HAL/halGPIO.h"
#include "HAL/STM32/halLTDCTpl.h"
#include "HAL/STM32/halDMA2D.h"
#include "System/eosMath.h"


// Codis d'operacio
//
#define OP_END        0
#define OP_DELAY      255


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
DisplayDriver_ILI9341LTDC::DisplayDriver_ILI9341LTDC() {

	int displayPitch = (((_displayWidth * CI::bytes) + 63) & 0xFFFFFFC0) / CI::bytes;

	_frameBuffer = new ColorFrameBuffer_DMA2D(
		_displayWidth,
		_displayHeight,
		DisplayOrientation::normal,
		(void*) _displayBuffer,
		displayPitch);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void DisplayDriver_ILI9341LTDC::initialize() {

    hwInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el modul.
///
void DisplayDriver_ILI9341LTDC::shutdown() {

	displayOff();
}


/// ----------------------------------------------------------------------
/// \brief    Activa el display
///
void DisplayDriver_ILI9341LTDC::displayOn() {

	halLTDCEnable();

	hwOpen();
	hwWriteCommand(CMD_SLEEP_OUT);
	halTMRDelay(120);
	hwWriteCommand(CMD_DISPLAY_ON);
	hwClose();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_ILI9341LTDC::displayOff() {

	hwOpen();
	hwWriteCommand(CMD_DISPLAY_OFF);
	hwWriteCommand(CMD_ENTER_SLEEP_MODE);
	halTMRDelay(120);
	hwClose();

	halLTDCDisable();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la orientacio.
/// \param    orientation: L'orientacio a seleccionar.
///
void DisplayDriver_ILI9341LTDC::setOrientation(
	DisplayOrientation orientation) {

	_frameBuffer->setOrientation(orientation);
}


/// ----------------------------------------------------------------------
/// \brief    Borra la pantalla.
/// \param    color: Color de borrat.
///
void DisplayDriver_ILI9341LTDC::clear(
	Color color) {

	_frameBuffer->clear(color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada x.
/// \param    y: Coordinada x.
/// \param    color: Color.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_ILI9341LTDC::setPixel(
	int x,
	int y,
	Color color) {

	_frameBuffer->setPixel(x, y, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels horitzontals.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    length: Longitut de la linia.
/// \param    color: Color.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_ILI9341LTDC::setHPixels(
	int x,
	int y,
	int size,
	Color color) {

	_frameBuffer->setPixels(x, y, size, 1, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels en vertical.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    length: Longitut de la linia.
/// \param    color: Color.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_ILI9341LTDC::setVPixels(
	int x,
	int y,
	int size,
	Color color) {

	_frameBuffer->setPixels(x, y, 1, size, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular d'un color
/// \param    x: Posicio x.
/// \param    y: Posicio y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    color: Color.
///
void DisplayDriver_ILI9341LTDC::setPixels(
	int x,
	int y,
	int width,
	int height,
	Color color) {

	_frameBuffer->setPixels(x, y, width, height, color);
}


/// ----------------------------------------------------------------------
/// \brief    Copia una regio rectangular de pixels.
/// \param    x: Posicio x.
/// \param    y: Posicio y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    colors: Colors a copiar.
/// \param    pitch: Pitch dels colors.
///
void DisplayDriver_ILI9341LTDC::setPixels(
	int x,
	int y,
	int width,
	int height,
	const Color* colors,
	int pitch) {

	_frameBuffer->setPixels(x, y, width, height, colors, pitch);
}


void DisplayDriver_ILI9341LTDC::writePixels(
	int x,
	int y,
	int width,
	int height,
	const void* pixels,
	ColorFormat format,
	int pitch) {

	_frameBuffer->setPixels(x, y, width, height, pixels, format, pitch);
}

void DisplayDriver_ILI9341LTDC::readPixels(
	int x,
	int y,
	int width,
	int height,
	void *pixels,
	ColorFormat format,
	int pitch) {

}


void DisplayDriver_ILI9341LTDC::vScroll(
	int delta,
	int x,
	int y,
	int width,
	int height) {

}


void DisplayDriver_ILI9341LTDC::hScroll(
	int delta,
	int x,
	int y,
	int width,
	int height) {

}


/// ----------------------------------------------------------------------
/// \brief    Refresca la pantalla
/// \remarks  La funcio no fa res, ja que el controlador LTDC, fa la
///           transferencia de dades a la pantalla de forma continua
///           i automatica.
///
void DisplayDriver_ILI9341LTDC::refresh() {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el display.
///
void DisplayDriver_ILI9341LTDC::hwInitialize() {

	// Inicialitza el modul GPIO
	//
	static const GPIOPinSettings gpioSettings[] = {
    	{ DISPLAY_DE_PORT,     DISPLAY_DE_PIN,
    		HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_DE_AF    },
		{ DISPLAY_HSYNC_PORT,  DISPLAY_HSYNC_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_HSYNC_AF },
		{ DISPLAY_VSYNC_PORT,  DISPLAY_VSYNC_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_VSYNC_AF },
		{ DISPLAY_DOTCLK_PORT, DISPLAY_DOTCLK_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_DOTCLK_AF},
		{ DISPLAY_R2_PORT,     DISPLAY_R2_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R2_AF    },
		{ DISPLAY_R3_PORT,     DISPLAY_R3_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R3_AF    },
		{ DISPLAY_R4_PORT,     DISPLAY_R4_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R4_AF    },
		{ DISPLAY_R5_PORT,     DISPLAY_R5_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R5_AF    },
		{ DISPLAY_R6_PORT,     DISPLAY_R6_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R6_AF    },
		{ DISPLAY_R7_PORT,     DISPLAY_R7_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R7_AF    },
		{ DISPLAY_G2_PORT,     DISPLAY_G2_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G2_AF    },
		{ DISPLAY_G3_PORT,     DISPLAY_G3_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G3_AF    },
		{ DISPLAY_G4_PORT,     DISPLAY_G4_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G4_AF    },
		{ DISPLAY_G5_PORT,     DISPLAY_G5_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G5_AF    },
		{ DISPLAY_G6_PORT,     DISPLAY_G6_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G6_AF    },
		{ DISPLAY_G7_PORT,     DISPLAY_G7_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G7_AF    },
		{ DISPLAY_B2_PORT,     DISPLAY_B2_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B2_AF    },
		{ DISPLAY_B3_PORT,     DISPLAY_B3_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B3_AF    },
		{ DISPLAY_B4_PORT,     DISPLAY_B4_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B4_AF    },
		{ DISPLAY_B5_PORT,     DISPLAY_B5_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B5_AF    },
		{ DISPLAY_B6_PORT,     DISPLAY_B6_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B6_AF    },
		{ DISPLAY_B7_PORT,     DISPLAY_B7_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B7_AF    },
#ifdef DISPLAY_RST_PIN
		{ DISPLAY_RST_PORT,    DISPLAY_RST_PIN,
			HAL_GPIO_MODE_OUTPUT | HAL_GPIO_INIT_CLR, 0 },
#endif
		{ DISPLAY_CS_PORT,     DISPLAY_CS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_SPEED_FAST | HAL_GPIO_INIT_SET, 0 },
		{ DISPLAY_RS_PORT,     DISPLAY_RS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_SPEED_FAST | HAL_GPIO_INIT_CLR, 0 },
		{ DISPLAY_SCK_PORT,    DISPLAY_SCK_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_SCK_AF },
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
	_hSpi = halSPIInitialize(&_spiData, &spiSettings);

	// Inicialitza el modul LTDC
	//
	static const LTDCSettings ltdcSettings = {
		.HSYNC = DISPLAY_HSYNC,
		.VSYNC = DISPLAY_VSYNC,
		.HBP = DISPLAY_HBP,
		.HFP = DISPLAY_HFP,
		.VBP = DISPLAY_VBP,
		.VFP = DISPLAY_VFP,
		.polarity = {
			.HSYNC = DISPLAY_HSPOL,
			.VSYNC = DISPLAY_VSPOL,
			.DE = DISPLAY_DEPOL,
			.PC = DISPLAY_PCPOL,
		 },
		.width = _displayWidth,
		.height = _displayHeight
	};
	halLTDCInitialize(&ltdcSettings);
	halLTDCSetBackgroundColor(0x000000FF);

	// Inicialitza la capa 0 del modul LTDC
	//
	halLTDCLayerSetWindow(HAL_LTDC_LAYER_0, 0, 0, _displayWidth, _displayHeight);

	halLTDCLayerSetFrameFormat(HAL_LTDC_LAYER_0,
		LTDCPixelFormatFor<CI::format>::value,
		_displayWidth * CI::bytes,
		((_displayWidth * CI::bytes) + 63) & 0xFFFFFFC0,
		_displayHeight);

	halLTDCLayerSetFrameBuffer(HAL_LTDC_LAYER_0, (void*) _displayBuffer);
	halLTDCLayerUpdate(HAL_LTDC_LAYER_0);

	// Inicialitza el controlador del display
	//
#if defined(STM32F429I_DISC1)
    static const uint8_t initCommands[] = {
        __SOFTWARE_RESET,
        OP_DELAY, 250,
        OP_DELAY, 250,
		__PUMP_RATIO_CONTROL(0x20),
		__POWER_CONTROL_A(0x39, 0x2C, 0x00, 0x34, 0x02),
    	__POWER_CONTROL_B(0x00, 0xC1, 0x30),
		__POWER_ON_SEQUENCE_CONTROL(0x64, 0x03, 0x12, 0x81),
    	__POWER_CONTROL_1(0x23),
    	__POWER_CONTROL_2(0x10),
    	__FRAME_RATE_CONTROL_1(0x00, 0x18),
    	__DRIVER_TIMING_CONTROL_A(0x85, 0x00, 0x78),
    	__DRIVER_TIMING_CONTROL_B(0x00, 0x00),
		__VCOM_CONTROL_1(0x3E, 0x28),
		__VCOM_CONTROL_2(0x86),
		__ENABLE_3G(0x00),
		__MEMORY_ACCESS_CONTROL(0x08 | MAC_MX_OFF | MAC_MY_OFF),
		__RGB_INTERFACE_SIGNAL_CONTROL(0xC2),
		__DISPLAY_FUNCTION_CONTROL(0x0A, 0xA7, 0x27, 0x04),
		__INTERFACE_CONTROL(0x01, 0x00, 0x06),
		OP_DELAY, 200,
		__GAMMA_SET(0x01),
		__POSITIVE_GAMMA_CORRECTION(0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
            0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00),
    	__NEGATIVE_GAMMA_CORRECTION(0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
            0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F),
        OP_END
    };

#elif
#error "Display no soportado"
#endif

	hwReset();
    hwOpen();
    uint8_t c;
    const uint8_t *p = initCommands;
    while ((c = *p++) != OP_END) {
        switch (c) {
            case OP_DELAY:
                halTMRDelay(*p++);
                break;

            default:
                hwWriteCommand(*p++);
                while (--c != 0)
                    hwWriteData(*p++);
                break;
        }
    }
    hwClose();
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void DisplayDriver_ILI9341LTDC::hwReset() {

#ifdef DISPLAY_RST_PORT
    halTMRDelay(10);
	halGPIOSetPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN);
    halTMRDelay(120);
#endif

}

/// ----------------------------------------------------------------------
/// \brief    Inicia la comunicacio amb el controlador.
///
void DisplayDriver_ILI9341LTDC::hwOpen() {

	halGPIOClearPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza la comunicacio amb el controlador.
///
void DisplayDriver_ILI9341LTDC::hwClose() {

    halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte de comanda en el controlador
/// \param    cmd: El byte de comanda.
///
void DisplayDriver_ILI9341LTDC::hwWriteCommand(
	uint8_t cmd) {

	halGPIOClearPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
	halSPISendBuffer(_hSpi, &cmd, sizeof(cmd));
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte de dades en el controlador
/// \param    data: El byte de dades.
///
void DisplayDriver_ILI9341LTDC::hwWriteData(
	uint8_t data) {

	halGPIOSetPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
	halSPISendBuffer(_hSpi, &data, sizeof(data));
}
