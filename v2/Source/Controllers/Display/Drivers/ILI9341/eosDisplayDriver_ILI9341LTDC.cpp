#include "eos.h"
#include "Controllers/Display/Drivers/ILI9341/eosDisplayDriver_ILI9341LTDC.h"
#include "Controllers/Display/Drivers/ILI9341/eosILI9341Defs.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HAL/halINT.h"
#include "HAL/halTMR.h"
#include "HTL/STM32/htlLTDC.h"
#include "HTL/STM32/htlGPIO.h"
#include "System/eosMath.h"


// Codis d'operacio
//
#define OP_END        0
#define OP_DELAY      255


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
DisplayDriver_ILI9341LTDC::DisplayDriver_ILI9341LTDC(
	FrameBuffer *frameBuffer):
	_frameBuffer(frameBuffer) {
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
void DisplayDriver_ILI9341LTDC::deinitialize() {

	disable();
}


/// ----------------------------------------------------------------------
/// \brief    Activa el display
///
void DisplayDriver_ILI9341LTDC::enable() {

	Ltdc::enable();

	open();
	writeCommand(CMD_SLEEP_OUT);
	halTMRDelay(120);
	writeCommand(CMD_DISPLAY_ON);
	close();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_ILI9341LTDC::disable() {

	open();
	writeCommand(CMD_DISPLAY_OFF);
	writeCommand(CMD_ENTER_SLEEP_MODE);
	halTMRDelay(120);
	close();

	Ltdc::disable();
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
	const Color *colors,
	int pitch) {

	_frameBuffer->setPixels(x, y, width, height, colors, pitch);
}


void DisplayDriver_ILI9341LTDC::setPixels(
	int x,
	int y,
	int width,
	int height,
	const void *pixels,
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
	PinCS::initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::fast);
	PinCS::set();
	PinRS::initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::fast);
	PinRS::clear();
#ifdef DISPLAY_RTS_GPIO
	PinRST::initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::fast);
	PinRST::clear();
#endif

	// Inicialitza el modul SPI
	//
	Spi::initSCKPin<PinSCK>();
	Spi::initMOSIPin<PinMOSI>();
	Spi::initialize(SPIMode::master, SPIClkPolarity::high, SPIClkPhase::edge1,	SPISize::_8, SPIFirstBit::msb, SPIClockDivider::_8);

	// Inicialitza el modul LTDC
	//
	Ltdc::initialize(_width, _height, _hSync, _vSync, _hBP, _vBP, _hFP, _vFP);
	Ltdc::initDEPin<PinDE>(_dePol);
	Ltdc::initHSYNCPin<PinHSYNC>(_hSyncPol);
	Ltdc::initVSYNCPin<PinVSYNC>(_vSyncPol);
	Ltdc::initPCPin<PinPC>(_pcPol);
	Ltdc::initRPins<PinR2, PinR3, PinR4, PinR5, PinR6, PinR7>();
	Ltdc::initGPins<PinG2, PinG3, PinG4, PinG5, PinG6, PinG7>();
	Ltdc::initBPins<PinB2, PinB3, PinB4, PinB5, PinB6, PinB7>();
	Ltdc::setBackgroundColor(RGB(0, 0, 255));

	// Inicialitza la capa 1 del modul LTDC
	//
	constexpr LTDCPixelFormat pixelFormat =
		Color::format == ColorFormat::argb8888 ? LTDCPixelFormat::argb8888 :
		Color::format == ColorFormat::argb4444 ? LTDCPixelFormat::argb4444 :
		Color::format == ColorFormat::argb1555 ? LTDCPixelFormat::argb1555 :
		Color::format == ColorFormat::rgb888 ? LTDCPixelFormat::rgb888 :
		Color::format == ColorFormat::al88 ? LTDCPixelFormat::al88 :
		Color::format == ColorFormat::al44 ? LTDCPixelFormat::al44 :
		Color::format == ColorFormat::l8 ? LTDCPixelFormat::l8 :
		LTDCPixelFormat::rgb565;

	LtdcLayer::setWindow(0, 0, _width, _height);
	LtdcLayer::setFrameFormat(
		pixelFormat,
		_width * Color::bytes,
		((_width * Color::bytes) + 63) & 0xFFFFFFC0,
		_height);
	LtdcLayer::setFrameBuffer(reinterpret_cast<void*>(_buffer));
	LtdcLayer::enable();
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

	#ifdef DISPLAY_RST_GPIO
    	halTMRDelay(10);
    	PinRST::set();
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

	PinCS::clear();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza la comunicacio amb el controlador.
///
void DisplayDriver_ILI9341LTDC::close() {

	PinCS::set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte de comanda en el controlador
/// \param    cmd: El byte de comanda.
///
void DisplayDriver_ILI9341LTDC::writeCommand(
	uint8_t cmd) {

	PinRS::clear();
	//Spi::send(&cmd, sizeof(cmd));
	Spi::write8(cmd);
	while (!Spi::getFlag(SPIFlag::txEmpty))
		continue;
	while (Spi::getFlag(SPIFlag::busy))
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte de dades en el controlador
/// \param    data: El byte de dades.
///
void DisplayDriver_ILI9341LTDC::writeData(
	uint8_t data) {

	PinRS::set();
//	Spi::send(&data, sizeof(data));
	Spi::write8(data);
	while (!Spi::getFlag(SPIFlag::txEmpty))
		continue;
	while (Spi::getFlag(SPIFlag::busy))
		continue;
}
