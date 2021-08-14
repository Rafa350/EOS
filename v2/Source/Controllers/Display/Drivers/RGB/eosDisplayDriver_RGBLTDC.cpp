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
#include "HAL/STM32/halLTDCTpl.h"
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
	halLTDCEnable();

    // Activa el display
	//
	_pinLCDE = 1;

	// Activa el backlight
	//
	_pinBKE = 1;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_RGBLTDC::displayOff() {

	// Desactiva el display
	//
	_pinLCDE = 0;

	// Desactiva el backlight
	//
	_pinBKE = 0;

	// Desactiva el modul LDTC
    //
	halLTDCDisable();
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
		halLTDCLayerSetFrameBuffer(HAL_LTDC_LAYER_0, _frontImageBuffer);
		halLTDCLayerUpdate(HAL_LTDC_LAYER_0);
	}
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul GPIO.
///
void DisplayDriver_RGBLTDC::initializeGPIO() {

	_pinBKE.initOutput(GPIOSpeed::low, GPIODriver::pushPull, GPIOState::clr);

	_pinLCDE.initOutput(GPIOSpeed::low, GPIODriver::pushPull, GPIOState::clr);
	_pinHSYNC.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinHSYNC::GPIOAlt::ltdc_HSYNC);
	_pinVSYNC.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinVSYNC::GPIOAlt::ltdc_VSYNC);
	_pinDE.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinDE::GPIOAlt::ltdc_DE);
	_pinDOTCLK.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinDOTCLK::GPIOAlt::ltdc_DOTCLK);

	_pinR0.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinR0::GPIOAlt::ltdc_R0);
	_pinR1.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinR1::GPIOAlt::ltdc_R1);
	_pinR2.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinR2::GPIOAlt::ltdc_R2);
	_pinR3.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinR3::GPIOAlt::ltdc_R3);
	_pinR4.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinR4::GPIOAlt::ltdc_R4);
	_pinR5.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinR5::GPIOAlt::ltdc_R5);
	_pinR6.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinR6::GPIOAlt::ltdc_R6);
	_pinR7.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinR7::GPIOAlt::ltdc_R7);

	_pinG0.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinG0::GPIOAlt::ltdc_G0);
	_pinG1.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinG1::GPIOAlt::ltdc_G1);
	_pinG2.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinG2::GPIOAlt::ltdc_G2);
	_pinG3.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinG3::GPIOAlt::ltdc_G3);
	_pinG4.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinG4::GPIOAlt::ltdc_G4);
	_pinG5.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinG5::GPIOAlt::ltdc_G5);
	_pinG6.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinG6::GPIOAlt::ltdc_G6);
	_pinG7.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinG7::GPIOAlt::ltdc_G7);

	_pinB0.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinB0::GPIOAlt::ltdc_B0);
	_pinB1.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinB1::GPIOAlt::ltdc_B1);
	_pinB2.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinB2::GPIOAlt::ltdc_B2);
	_pinB3.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinB3::GPIOAlt::ltdc_B3);
	_pinB4.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinB4::GPIOAlt::ltdc_B4);
	_pinB5.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinB5::GPIOAlt::ltdc_B5);
	_pinB6.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinB6::GPIOAlt::ltdc_B6);
	_pinB7.initAlt(GPIOSpeed::fast, GPIODriver::pushPull, PinB7::GPIOAlt::ltdc_B7);
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
	halLTDCInitialize(&ltdcSettings);
	halLTDCSetBackgroundColor(0x000000FF);

	// Inicialitza la capa 0
	//
	halLTDCLayerSetWindow(HAL_LTDC_LAYER_0, 0, 0, _imageWidth, _imageHeight);

	halLTDCLayerSetFrameFormat(HAL_LTDC_LAYER_0,
		LTDCPixelFormatFor<CI::format>::value,
		_imageWidth * CI::bytes,
		((_imageWidth * CI::bytes) + 63) & 0xFFFFFFC0,
		_imageHeight);
	halLTDCLayerSetFrameBuffer(HAL_LTDC_LAYER_0, _frontImageBuffer);
	halLTDCLayerUpdate(HAL_LTDC_LAYER_0);
}
