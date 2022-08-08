#include "eos.h"

#if !((defined(LTDC) && (defined(EOS_STM32F4) || defined(EOS_STM32F7))))
#error "LTDC hardware unavailable"
#endif


// Utilitza una sola capa (LTDC_Layer1). Pot treballar en modus simple
// o doble buffer.

#include "eosAssert.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "Controllers/Display/Drivers/RGB/eosDisplayDriver_RGBLTDC.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlLTDC.h"
#include "System/eosMath.h"
#include "System/Graphics/eosColorDefinitions.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
DisplayDriver_RGBLTDC::DisplayDriver_RGBLTDC() {

	constexpr int frameBufferPitchBytes = (_width * Color::bytes + 63) & 0xFFFFFFC0;
	constexpr int frameBufferPitch = frameBufferPitchBytes / Color::bytes;
	constexpr int frameSize = frameBufferPitchBytes * _height;

	_displayFrameBuffer = new ColorFrameBuffer_DMA2D(
		_width,
		_height,
		DisplayOrientation::normal,
		reinterpret_cast<void*>(_buffer),
		frameBufferPitch);

	if constexpr (_useDoubleBuffer)
		_workFrameBuffer = new ColorFrameBuffer_DMA2D(
			_width,
			_height,
			DisplayOrientation::normal,
			reinterpret_cast<void*>(_buffer + frameSize),
			frameBufferPitch);
	else
		_workFrameBuffer = _displayFrameBuffer;
}


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    displayFrameBuffer: Buffer d'imatge de visualitzacio
/// \param    workFrameBuffer: Buffer d'imatge de treball (Pot ser nullptr en
///           cas de buffer simple)
///
DisplayDriver_RGBLTDC::DisplayDriver_RGBLTDC(
	FrameBuffer *displayFrameBuffer,
	FrameBuffer *workFrameBuffer):

	_displayFrameBuffer(displayFrameBuffer),
	_workFrameBuffer(workFrameBuffer == nullptr? displayFrameBuffer : workFrameBuffer) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void DisplayDriver_RGBLTDC::initialize() {

	// Inicialitza els buffers a color negre
	//
	_workFrameBuffer->clear(Colors::black);
	if (_workFrameBuffer != _displayFrameBuffer)
		_displayFrameBuffer->clear(Colors::black);

	initializeGPIO();
	initializeLTDC();
}


/// ---------------------------------------------------------------------
/// \brief    Finalitza el driver.
///
void DisplayDriver_RGBLTDC::shutdown() {

	displayOff();
}


/// ----------------------------------------------------------------------
/// \brief    Activa el display.
///
void DisplayDriver_RGBLTDC::displayOn() {

    // Activa el modul LDTC
    //
	LTDC_1::enable();

    // Activa el display
	//
	GPIO_LCDE::set();

	// Activa el backlight
	//
	GPIO_BKE::set();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_RGBLTDC::displayOff() {

	// Desactiva el display
	//
	GPIO_LCDE::clear();

	// Desactiva el backlight
	//
	GPIO_BKE::clear();

	// Desactiva el modul LDTC
    //
	LTDC_1::disable();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona l'orientacio de la pantalla.
/// \param    orientation: L'orientacio.
///
void DisplayDriver_RGBLTDC::setOrientation(
	DisplayOrientation orientation) {

	_workFrameBuffer->setOrientation(orientation);
}


/// ----------------------------------------------------------------------
/// \brief    Borra la imatge.
/// \param    color: Color de borrat.
///
void DisplayDriver_RGBLTDC::clear(
	Color color) {

	_workFrameBuffer->clear(color);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un color a un pixel.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    color: Color.
///
void DisplayDriver_RGBLTDC::setPixel(
	int x,
	int y,
	Color color) {

	_workFrameBuffer->setPixel(x, y, color);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un color a una linia horitzontal.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    length: Longitut.
/// \param    color: Color.
///
void DisplayDriver_RGBLTDC::setHPixels(
	int x,
	int y,
	int size,
	Color color) {

	_workFrameBuffer->setPixels(x, y, size, 1, color);
}


/// ----------------------------------------------------------------------
/// \brief    Assigna un color a una linia vertical.
/// \param    x: Coordinada x.
/// \param    y: Coordinada x.
/// \param    length: Longitut de la linia.
/// \param    color: Color.
///
void DisplayDriver_RGBLTDC::setVPixels(
	int x,
	int y,
	int size,
	Color color) {

	_workFrameBuffer->setPixels(x, y, 1, size, color);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un color a una regio rectangular.
/// \param    x: Posicio x.
/// \param    y: Posicio y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    color: Color.
///
void DisplayDriver_RGBLTDC::setPixels(
	int x,
	int y,
	int width,
	int height,
	Color color) {

	_workFrameBuffer->setPixels(x, y, width, height, color);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna una llista colors a una regio rectangular. El format
///           de color es el meteix que el del buffer
/// \param    x: Posicio x.
/// \param    y: Posicio y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    colors: Punter als colors.
/// \param    pitch: Pitch dels colors.
///
void DisplayDriver_RGBLTDC::setPixels(
	int x,
	int y,
	int width,
	int height,
	const Color *colors,
	int pitch) {

	_workFrameBuffer->setPixels(x, y, width, height, colors, pitch);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una regio rectangular de pixels.
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio..
/// \param    width: Amplada de la regio
/// \param    height: Alçada de la regio
/// \param    pixels: Els pixels a copiar.
/// \param    format: Format dels pixels.
/// \param    pitch: Amplada de linia del bitmap.
///
void DisplayDriver_RGBLTDC::setPixels(
	int x,
	int y,
	int width,
	int height,
	const void *pixels,
	ColorFormat format,
	int pitch) {

	_workFrameBuffer->setPixels(x, y, width, height, pixels, format, pitch);
}


/// ----------------------------------------------------------------------
/// \brief Refresca la pantalla.
/// \remarks Si es treballa en doble buffer, intercanvia els frames.
///
void DisplayDriver_RGBLTDC::refresh() {

	if (_workFrameBuffer != _displayFrameBuffer) {

		// Intercanvia els buffers
		//
		Math::swap(_displayFrameBuffer, _workFrameBuffer);

		// Asigna l'adresa de la capa
		//
		LTDCLayer_1::setFrameBuffer(_displayFrameBuffer->getImageBuffer());
		LTDC_1::update();
	}
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul GPIO.
///
void DisplayDriver_RGBLTDC::initializeGPIO() {

	GPIO_BKE::initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::low);
	GPIO_LCDE::initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::low);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul LTDC.
/// \remarks Prepara la capa Layer1, pero no s'activara fins que s'asigni
/// una adressa per buffer de video.
///
void DisplayDriver_RGBLTDC::initializeLTDC() {

	// Inicialitza el modul LTDC
	//
	LTDC_1::initPCPin<GPIO_PC>(_pcPol);
	LTDC_1::initHSYNCPin<GPIO_HSYNC>(_hSyncPol);
	LTDC_1::initVSYNCPin<GPIO_VSYNC>(_vSyncPol);
	LTDC_1::initDEPin<GPIO_DE>(_dePol);
	LTDC_1::initRPins<GPIO_R0, GPIO_R1, GPIO_R2, GPIO_R3, GPIO_R4, GPIO_R5, GPIO_R6, GPIO_R7>();
	LTDC_1::initGPins<GPIO_G0, GPIO_G1, GPIO_G2, GPIO_G3, GPIO_G4, GPIO_G5, GPIO_G6, GPIO_G7>();
	LTDC_1::initBPins<GPIO_B0, GPIO_B1, GPIO_B2, GPIO_B3, GPIO_B4, GPIO_B5, GPIO_B6, GPIO_B7>();
	LTDC_1::init(_width, _height, _hSync, _vSync, _hBP, _vBP, _hFP, _vFP);
	LTDC_1::setBackgroundColor(Colors::blue);
	LTDC_1::setInterruptFunction(nullptr, nullptr);

	// Inicialitza la capa 1
	// La capa ocupa tota la superficie de la pantalla
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

	LTDCLayer_1::setWindow(0, 0, _width, _height);
	LTDCLayer_1::setFrameFormat(
		pixelFormat,
		_width * Color::bytes,
		((_width * Color::bytes) + 63) & 0xFFFFFFC0,
		_height);

	LTDCLayer_1::setFrameBuffer(_displayFrameBuffer->getImageBuffer());
	LTDC_1::update();
}
