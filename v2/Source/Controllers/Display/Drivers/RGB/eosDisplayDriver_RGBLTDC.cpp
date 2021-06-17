#include "eos.h"

#if !((defined(LTDC) && (defined(EOS_STM32F4) || defined(EOS_STM32F7))))
#error Hardware no soportado
#endif


// Utilitza una sola capa (LTDC_Layer1). Pot treballar en modus simple
// o doble buffer.

#include "eosAssert.h"
#include "Controllers/Display/eosFrameBuffer_RGB565_DMA2D.h"
#include "Controllers/Display/Drivers/RGB/eosDisplayDriver_RGBLTDC.h"
#include "HAL/STM32/halDMA2D.h"
#include "HAL/STM32/halGPIO.h"
#include "HAL/STM32/halLTDC.h"
#include "System/eosMath.h"
#include "System/Graphics/eosColorDefinitions.h"


// Parametres depenents del format de pixel
//
#if defined(DISPLAY_COLOR_RGB565)
#define FRAME_BUFFER              FrameBuffer_RGB565_DMA2D
#define HAL_DMA2D_DFMT_DEFAULT    HAL_DMA2D_DFMT_RGB565
//#define LTDC_LxPFCR_PF_DEFAULT    0b010
#define HAL_LTDC_FORMAT_DEFAULT   HAL_LTDC_FORMAT_RGB565
#elif defined(DISPLAY_COLOR_RGB888)
#define FRAME_BUFFER              FrameBuffer_RGB888_DMA2D
#define HAL_DMA2D_DFMT_DEFAULT    HAL_DMA2D_DFMT_RGB888
#define LTDC_LxPFCR_PF_DEFAULT    0b001
#else
#error No se definio DISPLAY_COLOR_xxxx
#endif

#define FRAME1_ADDR          DISPLAY_VRAM_ADDR
#ifdef DISPLAY_DOUBLE_BUFFER
#define FRAME2_ADDR          DISPLAY_VRAM_ADDR + FRAME_SIZE
#else
#define FRAME2_ADDR          DISPLAY_VRAM_ADDR
#endif
#define LINEBUF_ADDR         DISPLAY_FRAME2_ADDR + LINE_SIZE

#define LINE_SIZE            (((DISPLAY_IMAGE_WIDTH * sizeof(PIXEL_TYPE)) + 63) & 0xFFFFFFC0)
#define FRAME_SIZE           (LINE_SIZE * DISPLAY_IMAGE_HEIGHT)


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor
///
DisplayDriver_RGBLTDC::DisplayDriver_RGBLTDC() {

	_frontFrameAddr = FRAME1_ADDR;
	_frontFrameBuffer = new FRAME_BUFFER(
		DISPLAY_IMAGE_WIDTH,
		DISPLAY_IMAGE_HEIGHT,
		DisplayOrientation::normal,
		(void*) _frontFrameAddr);

#ifdef DISPLAY_DOUBLE_BUFFER
	_backFrameAddr = FRAME2_ADDR;
	_backFrameBuffer = new FRAME_BUFFER(
		DISPLAY_IMAGE_WIDTH,
		DISPLAY_IMAGE_HEIGHT,
		DisplayOrientation::normal,
		(void*) _backFrameAddr);
#else
	_backFrameAddr = _frontFrameAddr;
	_backFrameBuffer = _frontFrameBuffer;
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el driver.
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
#ifdef DISPLAY_DOUBLE_BUFFER
	_backFrameBuffer->clear(COLOR_Black);
#endif
}


/// ---------------------------------------------------------------------
/// \brief Finalitza el driver.
///
void DisplayDriver_RGBLTDC::shutdown() {

	displayOff();
}


/// ----------------------------------------------------------------------
/// \brief Activa el display.
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
/// \brief Desactiva el display.
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
/// \brief Selecciona l'orientacio de la pantalla.
/// \param orientation: L'orientacio.
///
void DisplayDriver_RGBLTDC::setOrientation(
	DisplayOrientation orientation) {

	_backFrameBuffer->setOrientation(orientation);
}


/// ----------------------------------------------------------------------
/// \brief Borra la imatge.
/// \param color: Color de borrat.
///
void DisplayDriver_RGBLTDC::clear(
	const Color &color) {

	_backFrameBuffer->clear(color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param color: Color del pixel.
///
void DisplayDriver_RGBLTDC::setPixel(
	int x,
	int y,
	const Color &color) {

	_backFrameBuffer->setPixel(x, y, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels horitzontals.
/// \param x: Coordinada X.
/// \param y: Colordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void DisplayDriver_RGBLTDC::setHPixels(
	int x,
	int y,
	int size,
	const Color &color) {

	_backFrameBuffer->setPixels(x, y, size, 1, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels en vertical.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void DisplayDriver_RGBLTDC::setVPixels(
	int x,
	int y,
	int size,
	const Color &color) {

	_backFrameBuffer->setPixels(x, y, 1, size, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
/// \param color: Color dels pixels.
///
void DisplayDriver_RGBLTDC::setPixels(
	int x,
	int y,
	int width,
	int height,
	const Color &color) {

	_backFrameBuffer->setPixels(x, y, width, height, color);
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
	const uint8_t *pixels,
	ColorFormat format,
	int dx,
	int dy,
	int pitch) {

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
	uint8_t *pixels,
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
#ifdef DISPLAY_DOUBLE_BUFFER

	// Intercanvia els buffers
	//
	Math::swap(_frontFrameBuffer, _backFrameBuffer);
	Math::swap(_frontFrameAddr, _backFrameAddr);

	// Asigna l'adresa de la capa
	//
	halLTDCLayerSetFrameAddress(HAL_LTDC_LAYER_0, _frontFrameAddr);
	halLTDCLayerUpdate(HAL_LTDC_LAYER_0);
#endif
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
		.width = DISPLAY_IMAGE_WIDTH,
		.height = DISPLAY_IMAGE_HEIGHT
	};

	// Inicialitza el modul LTDC
	//
	halLTDCInitialize(&ltdcSettings);
	halLTDCSetBackgroundColor(0x000000FF);

	// Inicialitza la capa 0
	//
	halLTDCLayerSetWindow(HAL_LTDC_LAYER_0, 0, 0, DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT);
	int pixelSize = halLTDCGetPixelSize(HAL_LTDC_FORMAT_DEFAULT);
	halLTDCLayerSetFrameFormat(HAL_LTDC_LAYER_0,
		HAL_LTDC_FORMAT_DEFAULT,
		DISPLAY_IMAGE_WIDTH * pixelSize,
		((DISPLAY_IMAGE_WIDTH * pixelSize) + 63) & 0xFFFFFFC0,
		DISPLAY_IMAGE_HEIGHT);
	halLTDCLayerSetFrameAddress(HAL_LTDC_LAYER_0, _frontFrameAddr);
	halLTDCLayerUpdate(HAL_LTDC_LAYER_0);
}
