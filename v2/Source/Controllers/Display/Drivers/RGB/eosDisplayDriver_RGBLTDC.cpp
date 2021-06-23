#include "eos.h"

#if !((defined(LTDC) && (defined(EOS_STM32F4) || defined(EOS_STM32F7))))
#error Hardware no soportado
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

	constexpr const int frameBufferPitchBytes = (_screenWidth * CI::bytes + 63) & 0xFFFFFFC0;
	constexpr const int frameBufferPitch = frameBufferPitchBytes / CI::bytes;
	constexpr const int frameSize = frameBufferPitchBytes * _screenHeight;

	_frontImageBuffer = (void*)_imageBuffer;
	_frontFrameBuffer = new ColorFrameBuffer_DMA2D(
		_screenWidth,
		_screenHeight,
		DisplayOrientation::normal,
		_frontImageBuffer,
		frameBufferPitch);

	if (_useDoubleBuffer) {
		_backImageBuffer = (void*)(_imageBuffer + frameSize);
		_backFrameBuffer = new ColorFrameBuffer_DMA2D(
			_screenWidth,
			_screenHeight,
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
	halGPIOSetPin(DISPLAY_LCDE_PORT, DISPLAY_LCDE_PIN);

	// Activa el backlight
	//
	halGPIOSetPin(DISPLAY_BKE_PORT, DISPLAY_BKE_PIN);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_RGBLTDC::displayOff() {

	// Desactiva el display
	//
	halGPIOClearPin(DISPLAY_LCDE_PORT, DISPLAY_LCDE_PIN);

	// Desactiva el backlight
	//
	halGPIOClearPin(DISPLAY_BKE_PORT, DISPLAY_BKE_PIN);

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
/// \brief    Asigna una llista colors a una regio rectangular.
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

	_backFrameBuffer->setPixels(x, y, width, height, colors, pitch);
}

/// ----------------------------------------------------------------------
/// \brief Escriu una regio rectangular de pixels.
/// \param x: Coordinada X de la posicio.
/// \param y: Coordinada Y de la posicio.
/// \param width: Amplada de la regio
/// \param height: Alçada de la regio
/// \param pixels: Els pixels a copiar.
/// \param format: Format dels pixels.
/// \param dx: Offset X dins del bitmap.
/// \param dy: offset Y dins del vitmap.
/// \param pitch: Aplada de linia del bitmap.
///
void DisplayDriver_RGBLTDC::writePixels(
	int x,
	int y,
	int width,
	int height,
	const void *pixels,
	ColorFormat format,
	int dx,
	int dy,
	int pitch) {

	Color *colors;
	_backFrameBuffer->setPixels(x, y, width, height, colors, pitch);
}


/// ----------------------------------------------------------------------
/// \brief Llegeix una regio rectangular de pixels.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
/// \param pixels: Buffer de pixels.
/// \param format: Format de pixels.
///
void DisplayDriver_RGBLTDC::readPixels(
	int x,
	int y,
	int width,
	int height,
	void *pixels,
	ColorFormat format,
	int dc,
	int dy,
	int pitch) {

}


/// ----------------------------------------------------------------------
/// \brief Realitza un scroll vertical
///
void DisplayDriver_RGBLTDC::vScroll(
	int delta,
	int x,
	int y,
	int width,
	int height) {

}


/// ----------------------------------------------------------------------
/// \brief Realitza un scroll horitzontal.
///
void DisplayDriver_RGBLTDC::hScroll(
	int delta,
	int x,
	int y,
	int width,
	int height) {

}


/// ----------------------------------------------------------------------
/// \brief Refresca la pantalla.
/// \remarks Si es treballa en doble buffer, intercanvia els frames.
///
void DisplayDriver_RGBLTDC::refresh() {

	if (_useDoubleBuffer) {

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

	static const GPIOPinSettings gpioSettings[] = {
		{DISPLAY_LCDE_PORT, DISPLAY_LCDE_PIN, HAL_GPIO_MODE_OUTPUT_PP, 0 },
		{DISPLAY_BKE_PORT, DISPLAY_BKE_PIN, HAL_GPIO_MODE_OUTPUT_PP, 0 },

		{DISPLAY_HSYNC_PORT, DISPLAY_HSYNC_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_HSYNC_AF},
		{DISPLAY_VSYNC_PORT, DISPLAY_VSYNC_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_VSYNC_AF},
		{DISPLAY_DOTCLK_PORT, DISPLAY_DOTCLK_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_DOTCLK_AF},
		{DISPLAY_DE_PORT, DISPLAY_DE_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_DE_AF},

		{DISPLAY_R0_PORT, DISPLAY_R0_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_R0_AF},
		{DISPLAY_R1_PORT, DISPLAY_R1_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_R1_AF},
		{DISPLAY_R2_PORT, DISPLAY_R2_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_R2_AF},
		{DISPLAY_R3_PORT, DISPLAY_R3_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_R3_AF},
		{DISPLAY_R4_PORT, DISPLAY_R4_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_R4_AF},
		{DISPLAY_R5_PORT, DISPLAY_R5_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_R5_AF},
		{DISPLAY_R6_PORT, DISPLAY_R6_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_R6_AF},
		{DISPLAY_R7_PORT, DISPLAY_R7_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_R7_AF},

		{DISPLAY_G0_PORT, DISPLAY_G0_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_G0_AF},
		{DISPLAY_G1_PORT, DISPLAY_G1_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_G1_AF},
		{DISPLAY_G2_PORT, DISPLAY_G2_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_G2_AF},
		{DISPLAY_G3_PORT, DISPLAY_G3_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_G3_AF},
		{DISPLAY_G4_PORT, DISPLAY_G4_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_G4_AF},
		{DISPLAY_G5_PORT, DISPLAY_G5_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_G5_AF},
		{DISPLAY_G6_PORT, DISPLAY_G6_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_G6_AF},
		{DISPLAY_G7_PORT, DISPLAY_G7_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_G7_AF},

		{DISPLAY_B0_PORT, DISPLAY_B0_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_B0_AF},
		{DISPLAY_B1_PORT, DISPLAY_B1_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_B1_AF},
		{DISPLAY_B2_PORT, DISPLAY_B2_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_B2_AF},
		{DISPLAY_B3_PORT, DISPLAY_B3_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_B3_AF},
		{DISPLAY_B4_PORT, DISPLAY_B4_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_B4_AF},
		{DISPLAY_B5_PORT, DISPLAY_B5_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_B5_AF},
		{DISPLAY_B6_PORT, DISPLAY_B6_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_B6_AF},
		{DISPLAY_B7_PORT, DISPLAY_B7_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_B7_AF}
	};

	halGPIOInitializePins(gpioSettings, sizeof(gpioSettings) / sizeof(gpioSettings[0]));
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul LTDC.
/// \remarks Prepara la capa Layer1, pero no s'activara fins que s'asigni
/// una adressa per buffer de video.
///
void DisplayDriver_RGBLTDC::initializeLTDC() {

	// Inicialitza el modul LTDC
	//
	LTDCSettings ltdcSettings;
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
	ltdcSettings.width = _screenWidth;
	ltdcSettings.height = _screenHeight;
	halLTDCInitialize(&ltdcSettings);
	halLTDCSetBackgroundColor(0x000000FF);

	// Inicialitza la capa 0
	//
	halLTDCLayerSetWindow(HAL_LTDC_LAYER_0, 0, 0, _screenWidth, _screenHeight);

	halLTDCLayerSetFrameFormat(HAL_LTDC_LAYER_0,
		LTDCPixelFormatFor<CI::format>::value,
		_screenWidth * CI::bytes,
		((_screenWidth * CI::bytes) + 63) & 0xFFFFFFC0,
		_screenHeight);
	halLTDCLayerSetFrameBuffer(HAL_LTDC_LAYER_0, _frontImageBuffer);
	halLTDCLayerUpdate(HAL_LTDC_LAYER_0);
}
