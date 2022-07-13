#include "eos.h"
#include "Controllers/Display/Drivers/ILI9341/eosDisplayDriver_ILI9341LTDC.h"
#include "Controllers/Display/Drivers/ILI9341/eosILI9341Defs.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HAL/halINT.h"
#include "HAL/halTMR.h"
#include "HTL/STM32/htlLTDC.h"
#include "HTL/STM32/htlGPIO.h"
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

    initializeInterface();
    initializeController();
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

	open();
	writeCommand(CMD_SLEEP_OUT);
	halTMRDelay(120);
	writeCommand(CMD_DISPLAY_ON);
	close();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_ILI9341LTDC::displayOff() {

	open();
	writeCommand(CMD_DISPLAY_OFF);
	writeCommand(CMD_ENTER_SLEEP_MODE);
	halTMRDelay(120);
	close();

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


void DisplayDriver_ILI9341LTDC::setPixels(
	int x,
	int y,
	int width,
	int height,
	const void* pixels,
	ColorFormat format,
	int pitch) {

	_frameBuffer->setPixels(x, y, width, height, pixels, format, pitch);
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
/// \brief    Inicialitza l'interficie amb el controlador.
///
void DisplayDriver_ILI9341LTDC::initializeInterface() {

	// Inicialitza el modul GPIO
	//
	constexpr htl::GPIODriver pp = htl::GPIODriver::pushPull;
	constexpr htl::GPIOSpeed fast = htl::GPIOSpeed::fast;

	GPIO_DE::initAlt(pp, fast, GPIO_DE::GPIOAlt::ltdc_DE);
	GPIO_HSYNC::initAlt(pp, fast, GPIO_HSYNC::GPIOAlt::ltdc_HSYNC);
	GPIO_VSYNC::initAlt(pp, fast, GPIO_VSYNC::GPIOAlt::ltdc_VSYNC);
	GPIO_DOTCLK::initAlt(pp, fast, GPIO_DOTCLK::GPIOAlt::ltdc_DOTCLK);
	GPIO_R2::initAlt(pp, fast, GPIO_R2::GPIOAlt::ltdc_R2);
	GPIO_R3::initAlt(pp, fast, GPIO_R3::GPIOAlt::ltdc_R3);
	GPIO_R4::initAlt(pp, fast, GPIO_R4::GPIOAlt::ltdc_R4);
	GPIO_R5::initAlt(pp, fast, GPIO_R5::GPIOAlt::ltdc_R5);
	GPIO_R6::initAlt(pp, fast, GPIO_R6::GPIOAlt::ltdc_R6);
	GPIO_R7::initAlt(pp, fast, GPIO_R7::GPIOAlt::ltdc_R7);
	GPIO_G2::initAlt(pp, fast, GPIO_G2::GPIOAlt::ltdc_G2);
	GPIO_G3::initAlt(pp, fast, GPIO_G3::GPIOAlt::ltdc_G3);
	GPIO_G4::initAlt(pp, fast, GPIO_G4::GPIOAlt::ltdc_G4);
	GPIO_G5::initAlt(pp, fast, GPIO_G5::GPIOAlt::ltdc_G5);
	GPIO_G6::initAlt(pp, fast, GPIO_G6::GPIOAlt::ltdc_G6);
	GPIO_G7::initAlt(pp, fast, GPIO_G7::GPIOAlt::ltdc_G7);
	GPIO_B2::initAlt(pp, fast, GPIO_B2::GPIOAlt::ltdc_B2);
	GPIO_B3::initAlt(pp, fast, GPIO_B3::GPIOAlt::ltdc_B3);
	GPIO_B4::initAlt(pp, fast, GPIO_B4::GPIOAlt::ltdc_B4);
	GPIO_B5::initAlt(pp, fast, GPIO_B5::GPIOAlt::ltdc_B5);
	GPIO_B6::initAlt(pp, fast, GPIO_B6::GPIOAlt::ltdc_B6);
	GPIO_B7::initAlt(pp, fast, GPIO_B7::GPIOAlt::ltdc_B7);

	GPIO_CS::initOutput(pp, fast);
	GPIO_CS::set();
	GPIO_RS::initOutput(pp, fast);
	GPIO_RS::clear();
#ifdef DISPLAY_RTS_PIN
	GPIO_RST::initOutput(pp, fast);
	GPIO_RST::clear();
#endif

	// Inicialitza el modul SPI
	//
	SPI::initSCKPin<GPIO_SCK>();
	SPI::initMOSIPin<GPIO_MOSI>();
	SPI::init(HAL_SPI_MODE_0 | HAL_SPI_MS_MASTER | HAL_SPI_FIRSTBIT_MSB | HAL_SPI_CLOCKDIV_16);

	// Inicialitza el modul LTDC
	//
	static const halLTDCSettings ltdcSettings = {
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
		htl::LTDCPixelFormatFor<CI::format>::value,
		_displayWidth * CI::bytes,
		((_displayWidth * CI::bytes) + 63) & 0xFFFFFFC0,
		_displayHeight);

	halLTDCLayerSetFrameBuffer(HAL_LTDC_LAYER_0, (void*) _displayBuffer);
	halLTDCLayerUpdate(HAL_LTDC_LAYER_0);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el controlador
///
void DisplayDriver_ILI9341LTDC::initializeController() {

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

#ifdef DISPLAY_RST_PORT
    halTMRDelay(10);
    _pinRST = 1;
    halTMRDelay(120);
#endif

    uint8_t c;
    const uint8_t *p = initCommands;

    open();
    while ((c = *p++) != OP_END) {
        switch (c) {
            case OP_DELAY:
                halTMRDelay(*p++);
                break;

            default:
                writeCommand(*p++);
                while (--c != 0)
                    writeData(*p++);
                break;
        }
    }
    close();
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la comunicacio amb el controlador.
///
void DisplayDriver_ILI9341LTDC::open() {

	GPIO_CS::clear();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza la comunicacio amb el controlador.
///
void DisplayDriver_ILI9341LTDC::close() {

	GPIO_CS::set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte de comanda en el controlador
/// \param    cmd: El byte de comanda.
///
void DisplayDriver_ILI9341LTDC::writeCommand(
	uint8_t cmd) {

	GPIO_RS::clear();
	SPI::send(&cmd, sizeof(cmd));
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte de dades en el controlador
/// \param    data: El byte de dades.
///
void DisplayDriver_ILI9341LTDC::writeData(
	uint8_t data) {

	GPIO_RS::set();
	SPI::send(&data, sizeof(data));
}
