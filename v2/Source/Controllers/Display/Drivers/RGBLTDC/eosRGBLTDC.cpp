#include "eos.h"

#if defined(USE_DISPLAY) && defined(DISPLAY_DRV_RGBLTDC)

#if !((defined(LTDC) && (defined(EOS_STM32F4) || defined(EOS_STM32F7))))
#error Hardware no soportado
#endif


// Utilitza una sola capa (LTDC_Layer1). Pot treballar en modus simple
// o doble buffer.

#include "eosAssert.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "HAL/STM32/halDMA2D.h"
#include "HAL/STM32/halGPIO.h"
#include "HAL/STM32/halLTDC.h"
#include "System/eosMath.h"


// Parametres depenents del format de pixel
//
#if defined(DISPLAY_COLOR_RGB565)
#define HAL_DMA2D_DFMT_DEFAULT    HAL_DMA2D_DFMT_RGB565
#define LTDC_LxPFCR_PF_DEFAULT    0b010
#define HAL_LTDC_FORMAT_DEFAULT   HAL_LTDC_FORMAT_RGB565
#elif defined(DISPLAY_COLOR_RGB888)
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
#define LINE_WIDTH           (LINE_SIZE / sizeof(PIXEL_TYPE))
#define FRAME_SIZE           (LINE_SIZE * DISPLAY_IMAGE_HEIGHT)


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Obte l'adressa del pixel en la coordinada especificada.
/// \param base: Adressa base.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \return L'adressa del pixel.
///
static inline pixel_t *addressOf(
	int base,
	int x,
	int y) {

	return (pixel_t*) (base + (((y * LINE_WIDTH) + x) * sizeof(pixel_t)));
}


/// ----------------------------------------------------------------------
/// \brief Converteix un color a format pixel.
/// \param color: El color a convertir.
/// \return El valor del pixel.
///
static inline pixel_t toPixel(
	const Color &color) {

#if defined(DISPLAY_COLOR_RGB565)
	return (pixel_t) color.toRGB565();
#elif defined(DISPLAY_COLOR_ARGB8888)
	return (pixel_t) color.toRGB888();
#endif
}


/// ----------------------------------------------------------------------
/// \brief Compbina dos pixels.
/// \param b: Pixel del fons.
/// \param f: Pixel del primer pla.
/// \param o: Opacitat.
/// \return El valor del pixel combinat.
///
static inline pixel_t combinePixel(
	pixel_t b,
	pixel_t f,
	uint8_t o) {

	uint8_t br = (b & PIXEL_MASK_R) >> PIXEL_SHIFT_R;
	uint8_t bg = (b & PIXEL_MASK_G) >> PIXEL_SHIFT_G;
	uint8_t bb = (b & PIXEL_MASK_B) >> PIXEL_SHIFT_B;

	uint8_t fr = (f & PIXEL_MASK_R) >> PIXEL_SHIFT_R;
	uint8_t fg = (f & PIXEL_MASK_G) >> PIXEL_SHIFT_G;
	uint8_t fb = (f & PIXEL_MASK_B) >> PIXEL_SHIFT_B;

	return (pixel_t)
		((((fr * o) + (br * (255u - o))) >> 8) << PIXEL_SHIFT_R) |
		((((fg * o) + (bg * (255u - o))) >> 8) << PIXEL_SHIFT_G) |
		((((fb * o) + (bb * (255u - o))) >> 8) << PIXEL_SHIFT_B);
}


/// ----------------------------------------------------------------------
/// \brief Constructor
///
RGBDirectDriver::RGBDirectDriver():

	screenWidth(DISPLAY_IMAGE_WIDTH),
	screenHeight(DISPLAY_IMAGE_HEIGHT),
	orientation(DisplayOrientation::normal),
	frontFrameAddr(FRAME1_ADDR),
	backFrameAddr(FRAME2_ADDR) {
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el driver.
///
void RGBDirectDriver::initialize() {

	// Inicialitza els pins
	//
	initializeGPIO();

	// Inicialitza el dispositiu LTDC
	//
	initializeLTDC();
	halLTDCLayerSetFrameAddress(HAL_LTDC_LAYER_0, frontFrameAddr);
	halLTDCLayerUpdate(HAL_LTDC_LAYER_0);

    // Inicialitza el dispositiu DMA2D
    //
	halDMA2DInitialize();

	// Borra els buffers a color negre
	//
	halDMA2DStartFill(FRAME1_ADDR, DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT,
		LINE_WIDTH - DISPLAY_IMAGE_WIDTH, HAL_DMA2D_DFMT_DEFAULT, 0x0000);
	halDMA2DWaitForFinish();
#ifdef DISPLAY_DOUBLE_BUFFER
	halDMA2DStartFill(FRAME2_ADDR, DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT,
		LINE_WIDTH - DISPLAY_IMAGE_WIDTH, HAL_DMA2D_DFMT_DEFAULT, 0x0000);
	halDMA2DWaitForFinish();
#endif
}


/// ---------------------------------------------------------------------
/// \brief Finalitza el driver.
///
void RGBDirectDriver::shutdown() {

	displayOff();
}


/// ----------------------------------------------------------------------
/// \brief Activa el display.
///
void RGBDirectDriver::displayOn() {

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
void RGBDirectDriver::displayOff() {

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
void RGBDirectDriver::setOrientation(
	DisplayOrientation orientation) {

	if (this->orientation != orientation) {
		this->orientation = orientation;
		switch (orientation) {
			case DisplayOrientation::normal:
			case DisplayOrientation::rotate180:
				screenWidth = DISPLAY_IMAGE_WIDTH;
				screenHeight = DISPLAY_IMAGE_HEIGHT;
				break;

			case DisplayOrientation::rotate90:
			case DisplayOrientation::rotate270:
				screenWidth = DISPLAY_IMAGE_HEIGHT;
				screenHeight = DISPLAY_IMAGE_WIDTH;
				break;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief Borra la imatge.
/// \param color: Color de borrat.
///
void RGBDirectDriver::clear(
	const Color &color) {

	fill(0, 0, DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param color: Color del pixel.
///
void RGBDirectDriver::setPixel(
	int x,
	int y,
	const Color &color) {

	if ((x >= 0) && (x < screenWidth) && (y >= 0) && (y < screenHeight)) {
		rotate(x, y);
		put(x, y, color);
	}
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels horitzontals.
/// \param x: Coordinada X.
/// \param y: Colordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void RGBDirectDriver::setHPixels(
	int x,
	int y,
	int size,
	const Color &color) {

	setPixels(x, y, size, 1, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels en vertical.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void RGBDirectDriver::setVPixels(
	int x,
	int y,
	int size,
	const Color &color) {

	setPixels(x, y, 1, size, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
/// \param color: Color dels pixels.
///
void RGBDirectDriver::setPixels(
	int x,
	int y,
	int width,
	int height,
	const Color &color) {

	int x1 = x;
	int y1 = y;
	int x2 = x + width - 1;
	int y2 = y + height - 1;

	// Retalla al tamany de pantalla
	//
	x1 = Math::max(x1, 0);
	y1 = Math::max(y1, 0);
	x2 = Math::min(x2, screenWidth - 1);
	y2 = Math::min(y2, screenHeight - 1);

	// Cas que nomes sigui un pixel
	//
	if ((x1 == x2) && (y1 == y2)) {
		rotate(x1, y1);
		put(x1, y1, color);
	}

	// Cas que hagi una regio rectangular per dibuixar
	//
	else if ((x1 <= x2) && (y1 <= y2)) {
		rotate(x1, y1, x2, y2);
		fill(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
	}
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
void RGBDirectDriver::writePixels(
	int x,
	int y,
	int width,
	int height,
	const uint8_t *pixels,
	ColorFormat format,
	int dx,
	int dy,
	int pitch) {

	// Comprova si es dins dels limits
	//
	if ((x >= 0) && (x + width <= screenWidth) &&
		(y >= 0) && (y + height <= screenHeight) &&
		(width > 0) && (height > 0)) {

		copy(x, y, width, height, pixels, format, dx, dy, pitch);
	}
}


/// ----------------------------------------------------------------------
/// \brief Llegeix una regio rectangular de pixels.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param width: Amplada de la regio.
/// \param height: Al�ada de la regio.
/// \param pixels: Buffer de pixels.
/// \param format: Format de pixels.
///
void RGBDirectDriver::readPixels(
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
void RGBDirectDriver::vScroll(
	int delta,
	int x,
	int y,
	int width,
	int height) {

}


/// ----------------------------------------------------------------------
/// \brief Realitza un scroll horitzontal.
///
void RGBDirectDriver::hScroll(
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
void RGBDirectDriver::refresh() {
#ifdef DISPLAY_DOUBLE_BUFFER

	// Intercanvia els buffers
	//
	Math::swap(frontFrameAddr, backFrameAddr);

	// Asigna l'adresa de la capa
	//
	halLTDCLayerSetFrameAddress(HAL_LTDC_LAYER_0, frontFrameAddr);
	halLTDCLayerUpdate(HAL_LTDC_LAYER_0);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul GPIO.
///
void RGBDirectDriver::initializeGPIO() {

	static const GPIOInitializePinInfo gpioInit[] = {
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

	halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul LTDC.
/// \remarks Prepara la capa Layer1, pero no s'activara fins que s'asigni
/// una adressa per buffer de video.
///
void RGBDirectDriver::initializeLTDC() {

	static const LTDCInitializeInfo ltdcInit = {
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
	halLTDCInitialize(&ltdcInit);
	halLTDCSetBackgroundColor(0x000000FF);

	// Inicialitza la capa 0
	//
	halLTDCLayerSetWindow(HAL_LTDC_LAYER_0, 0, 0, DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT);
	halLTDCLayerSetFrameFormat(HAL_LTDC_LAYER_0,
		HAL_LTDC_FORMAT_DEFAULT,
		DISPLAY_IMAGE_WIDTH * halLTDCGetPixelSize(HAL_LTDC_FORMAT_DEFAULT),
		((DISPLAY_IMAGE_WIDTH * halLTDCGetPixelSize(HAL_LTDC_FORMAT_DEFAULT)) + 63) & 0xFFFFFFC0,
		DISPLAY_IMAGE_HEIGHT);
	halLTDCLayerUpdate(HAL_LTDC_LAYER_0);
}


/// ----------------------------------------------------------------------
/// \brief Rota les coordinades d'un punt.
/// \param x: Coordinada X del punt.
/// \param y: Coordinada Y del punt.
///
void RGBDirectDriver::rotate(
	int &x,
	int &y) {

	int xx = x;
	int yy = y;

	// Realitza la rotacio. D'aquesta manera es mes rapida que
	// fer dues multiplicacione fent servir la formula.
	//
	switch (orientation) {
		case DisplayOrientation::normal:
			break;

		case DisplayOrientation::rotate90:
			xx = (DISPLAY_IMAGE_WIDTH - 1) - y;
			yy = x;
			break;

		case DisplayOrientation::rotate180:
			xx = (DISPLAY_IMAGE_WIDTH - 1) - x;
			yy = (DISPLAY_IMAGE_HEIGHT - 1) - y;
			break;

		case DisplayOrientation::rotate270:
			xx = y;
			yy = (DISPLAY_IMAGE_HEIGHT - 1) - x;
			break;
	}

	x = xx;
	y = yy;
}


/// ----------------------------------------------------------------------
/// \brief Rota les coordinades d'un rectangle.
/// \param x1: Coordinada X esquerra.
/// \param y1: Coordinada Y superior.
/// \param x2: Coordinada X dreta.
/// \param y2: Coordinada Y inferior.
/// \remarks Les coordinades son retornades en forma normalitzada.
///
void RGBDirectDriver::rotate(
	int &x1,
	int &y1,
	int &x2,
	int &y2) {

	int xx1 = x1;
	int yy1 = y1;
	int xx2 = x2;
	int yy2 = y2;

	// Realitza la rotacio. D'aquesta manera es mes rapida que
	// fer dues multiplicacione fent servir la formula.
	//
	switch (orientation) {
		case DisplayOrientation::normal:
			break;

		case DisplayOrientation::rotate90:
			xx1 = (DISPLAY_IMAGE_WIDTH - 1) - y1;
			yy1 = x1;
			xx2 = (DISPLAY_IMAGE_WIDTH - 1) - y2;
			yy2 = x2;
			break;

		case DisplayOrientation::rotate180:
			xx1 = (DISPLAY_IMAGE_WIDTH - 1) - x1;
			yy1 = (DISPLAY_IMAGE_HEIGHT - 1) - y1;
			xx2 = (DISPLAY_IMAGE_WIDTH - 1) - x2;
			yy2 = (DISPLAY_IMAGE_HEIGHT - 1) - y2;
			break;

		case DisplayOrientation::rotate270:
			xx1 = y1;
			yy1 = (DISPLAY_IMAGE_HEIGHT - 1) - x1;
			xx2 = y2;
			yy2 = (DISPLAY_IMAGE_HEIGHT - 1) - x2;
			break;
	}

	// Normalitza el resultat
	//
	x1 = Math::min(xx1, xx2);
	y1 = Math::min(yy1, yy2);
	x2 = Math::max(xx1, xx2);
	y2 = Math::max(yy1, yy2);
}


/// ----------------------------------------------------------------------
/// \brief Aigna un color a un pixel.
/// \param x: Coordinada X del pixel.
/// \param y: Coordinada Y del pixel.
/// \param color: Color en format de pixel fisic;
/// \remarks No es fa cap tipus de verificacio dels parametres.
///
void RGBDirectDriver::put(
	int x,
	int y,
	const Color &color) {

	if (!color.isTransparent()) {

		pixel_t *pPixelAddr = addressOf(backFrameAddr, x, y);

		if (color.isOpaque())
			*pPixelAddr = toPixel(color);
		else
			*pPixelAddr = combinePixel(*pPixelAddr, toPixel(color), color.getOpacity());
	}
}


/// ----------------------------------------------------------------------
/// \brief Ompla amb un color, una regio de la pantalla.
/// \param x: Coordinada x.
/// \param y: Coordinada y.
/// \param width: Amplada del bloc.
/// \param height: Alçada del bloc.
/// \param color: Color.
/// \remarks No es fa cap tipus de verificacio dels parametres.
///
void RGBDirectDriver::fill(
	int x,
	int y,
	int width,
	int height,
	const Color &color) {

	if (color.isOpaque()) {
		halDMA2DStartFill(
			(uint32_t) addressOf(backFrameAddr, x, y),
			width,
			height,
			LINE_WIDTH - width,
			HAL_DMA2D_DFMT_DEFAULT,
			toPixel(color));
		halDMA2DWaitForFinish();
	}
	else
		for (int yy = 0; yy < height; yy++)
			for (int xx = 0; xx < width; xx++)
				put(x + xx, y + yy, color);
}


/// ----------------------------------------------------------------------
/// \brief Copia un bitmap a una regio de la pantalla.
/// \param x: Coordinada X de la posicio.
/// \param y: Coordinada Y de la posicio.
/// \param width: Amplada.
/// \param height: Alçada.
/// \param pixels: Llista de pixels.
/// \param format: Format dels pixels.
/// \param dx: Offset X dins del bitmap.
/// \param dy: offset Y dins del vitmap.
/// \param pitch: Offset a la seguent linia del bitmap. 0 si son consecutives.
///
void RGBDirectDriver::copy(
	int x,
	int y,
	int width,
	int height,
	const uint8_t *pixels,
	ColorFormat format,
	int dx,
	int dy,
	int pitch) {

	DMA2DOptions options = HAL_DMA2D_DFMT_DEFAULT;
	switch (format) {
		default:
		case ColorFormat::rgb565:
			options |= HAL_DMA2D_SFMT_RGB565;
			break;

		case ColorFormat::argb8888:
			options |= HAL_DMA2D_SFMT_ARGB8888;
			break;
	}

	halDMA2DStartCopy(
		(uint32_t) addressOf(backFrameAddr, x, y),
		width,
		height,
		LINE_WIDTH - width,
		options,
		((uint32_t) pixels) + (((dy * height) + dx) * sizeof(uint16_t)),
	    pitch);
	halDMA2DWaitForFinish();
}

#endif // USE_DISPLAY && DISPLAY_DRV_RGBLTDC

