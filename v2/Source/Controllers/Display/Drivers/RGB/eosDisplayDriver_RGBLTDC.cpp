#include "eos.h"

#if !((defined(LTDC) && (defined(EOS_STM32F4) || defined(EOS_STM32F7))))
#error "LTDC hardware unavailable"
#endif


// Utilitza una sola capa (LTDC_Layer1). Pot treballar en modus simple
// o doble buffer.

#include "eosAssert.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "Controllers/Display/Drivers/RGB/eosDisplayDriver_RGBLTDC.h"
#include "HAL/STM32/halDMA2D.h"
#include "HAL/STM32/halGPIO.h"
#include "HTL/STM32/htlLTDC.h"
#include "System/eosMath.h"
#include "System/Graphics/eosColorDefinitions.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
DisplayDriver_RGBLTDC::DisplayDriver_RGBLTDC() {

	constexpr const int frameBufferPitchBytes = (_imageWidth * CI::bytes + 63) & 0xFFFFFFC0;
	constexpr const int frameBufferPitch = frameBufferPitchBytes / CI::bytes;
	constexpr const int frameSize = frameBufferPitchBytes * _imageHeight;

	_frontImageBuffer = (void*)_imageBuffer;
	_frontFrameBuffer = new ColorFrameBuffer_DMA2D(
		_imageWidth,
		_imageHeight,
		DisplayOrientation::normal,
		_frontImageBuffer,
		frameBufferPitch);

	if constexpr (_useDoubleBuffer) {
		_backImageBuffer = (void*)(_imageBuffer + frameSize);
		_backFrameBuffer = new ColorFrameBuffer_DMA2D(
			_imageWidth,
			_imageHeight,
			DisplayOrientation::normal,
			_backImageBuffer,
			frameBufferPitch);
	}
	else {
		_backImageBuffer = _frontImageBuffer;
		_backFrameBuffer = _frontFrameBuffer;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void DisplayDriver_RGBLTDC::initialize() {

	// Inicialitza els pins
	//
	initializeGPIO();

	// Inicialitza el dispositiu LTDC
	//
	initializeLTDC();

    // Inicialitza el dispositiu DMA2D
    //
	halDMA2DInitialize();

	// Inicialitza els buffers a color negre
	//
	_frontFrameBuffer->clear(COLOR_Black);
	if (_useDoubleBuffer)
		_backFrameBuffer->clear(COLOR_Black);
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
	_ltdc.enable();

    // Activa el display
	//
	PinLCDE::set();

	// Activa el backlight
	//
	PinBKE::set();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_RGBLTDC::displayOff() {

	// Desactiva el display
	//
	PinLCDE::clear();

	// Desactiva el backlight
	//
	PinBKE::clear();

	// Desactiva el modul LDTC
    //
	_ltdc.disable();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona l'orientacio de la pantalla.
/// \param    orientation: L'orientacio.
///
void DisplayDriver_RGBLTDC::setOrientation(
	DisplayOrientation orientation) {

	_backFrameBuffer->setOrientation(orientation);
}


/// ----------------------------------------------------------------------
/// \brief    Borra la imatge.
/// \param    color: Color de borrat.
///
void DisplayDriver_RGBLTDC::clear(
	Color color) {

	_backFrameBuffer->clear(color);
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

	_backFrameBuffer->setPixel(x, y, color);
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

	_backFrameBuffer->setPixels(x, y, size, 1, color);
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

	_backFrameBuffer->setPixels(x, y, 1, size, color);
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

	_backFrameBuffer->setPixels(x, y, width, height, color);
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
	const Color* colors,
	int pitch) {

	_backFrameBuffer->setPixels(x, y, width, height, colors, pitch);
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

	_backFrameBuffer->setPixels(x, y, width, height, pixels, format, pitch);
}


/// ----------------------------------------------------------------------
/// \brief Refresca la pantalla.
/// \remarks Si es treballa en doble buffer, intercanvia els frames.
///
void DisplayDriver_RGBLTDC::refresh() {

	if constexpr (_useDoubleBuffer) {

		// Intercanvia els buffers
		//
		Math::swap(_frontFrameBuffer, _backFrameBuffer);
		Math::swap(_frontImageBuffer, _backImageBuffer);

		// Asigna l'adresa de la capa
		//
		htl::LTDCLayer_0::setFramBuffer(_frontImageBuffer);
		htl::LTDCLayer_0::update();
	}
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul GPIO.
///
void DisplayDriver_RGBLTDC::initializeGPIO() {

	PinBKE::initOutput(htl::GPIOSpeed::low, htl::GPIODriver::pushPull, htl::GPIOState::clr);
	PinLCDE::initOutput(htl::GPIOSpeed::low, htl::GPIODriver::pushPull, htl::GPIOState::clr);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul LTDC.
/// \remarks Prepara la capa Layer1, pero no s'activara fins que s'asigni
/// una adressa per buffer de video.
///
void DisplayDriver_RGBLTDC::initializeLTDC() {

	// Inicialitza el modul LTDC
	//
	halLTDCSettings ltdcSettings;
	ltdcSettings.HSYNC = DISPLAY_HSYNC;
	ltdcSettings.VSYNC = DISPLAY_VSYNC;
	ltdcSettings.HBP = DISPLAY_HBP;
	ltdcSettings.HFP = DISPLAY_HFP;
	ltdcSettings.VBP = DISPLAY_VBP;
	ltdcSettings.VFP = DISPLAY_VFP;
	ltdcSettings.polarity.HSYNC = DISPLAY_HSPOL;
	ltdcSettings.polarity.VSYNC = DISPLAY_VSPOL;
	ltdcSettings.polarity.DE = DISPLAY_DEPOL;
	ltdcSettings.polarity.PC = DISPLAY_PCPOL;
	ltdcSettings.width = _imageWidth;
	ltdcSettings.height = _imageHeight;

	_ltdc.initDOTCLKPin<PinDOTCLK>();
	_ltdc.initHSYNCPin<PinHSYNC>();
	_ltdc.initVSYNCPin<PinVSYNC>();
	_ltdc.initDEPin<PinDE>();
	_ltdc.initRPins<PinR0, PinR1, PinR2, PinR3, PinR4, PinR5, PinR6, PinR7>();
	_ltdc.initGPins<PinG0, PinG1, PinG2, PinG3, PinG4, PinG5, PinG6, PinG7>();
	_ltdc.initBPins<PinB0, PinB1, PinB2, PinB3, PinB4, PinB5, PinB6, PinB7>();
	_ltdc.initialize(ltdcSettings);
	_ltdc.setBackgroundColor(COLOR_Blue);

	// Inicialitza la capa 0
	//
	_ltdc.layer0.setWindow(0, 0, _imageWidth, _imageHeight);
	_ltdc.layer0.setFrameFormat(
			htl::LTDCPixelFormatFor<CI::format>::value,
		_imageWidth * CI::bytes,
		((_imageWidth * CI::bytes) + 63) & 0xFFFFFFC0,
		_imageHeight);
	_ltdc.layer0.setFramBuffer(_frontImageBuffer);
	_ltdc.layer0.update();
}
