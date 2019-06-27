#include "eos.h"

#ifdef DISPLAY_DRV_RGBLTDC

#if !((defined(LTDC) && (defined(EOS_STM32F4) || defined(EOS_STM32F7))))
#error Hardware no soportado
#endif


// Utilitza una sola capa (LTDC_Layer1). Pot treballar en modus simple
// o doble buffer.

#include "eosAssert.h"
#include "System/eosMath.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "HAL/STM32/halGPIO.h"
#include "HAL/STM32/halLTDC.h"
#include "HAL/STM32/halDMA2D.h"


// Parametres depenents del format de pixel
//
#if defined(DISPLAY_COLOR_RGB565)
#define HAL_DMA2D_DFMT_DEFAULT    HAL_DMA2D_DFMT_RGB565
#define LTDC_LxPFCR_PF_DEFAULT    0b010
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


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Obte l'adressa del pixel en la coordinada especificada.
/// \param base: Adressa base.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \return L'adressa del pixel.
///
static inline int addressOf(
	int base,
	int x,
	int y) {

	return base + (((y * LINE_WIDTH) + x) * sizeof(pixel_t));
}


/// ----------------------------------------------------------------------
/// \brief Converteix un color a format de pixel.
/// \param color: El color a convertir.
/// \return El color en format de piuxel.
///
static inline pixel_t toPixel(
	const Color &color) {

#if defined(DISPLAY_COLOR_RGB565)
	return (pixel_t) color.toRGB565();
#elif defined(DISPLAY_COLOR_RGB888)
	return (pixel_t) color.toRGB888();
#endif
}


IDisplayDriver *RGBDirectDriver::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief Obte una instancia unica del driver.
/// \return La instancia del driver.
///
IDisplayDriver *RGBDirectDriver::getInstance() {

	if (instance == nullptr)
		instance = new RGBDirectDriver();
	return instance;
}


/// ----------------------------------------------------------------------
/// \brief Contructor
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
	gpioInitialize();

	// Inicialitza el dispositiu LTDC
	//
	ltdcInitialize();
	halLTDCSetFrameAddress(HAL_LTDC_LAYER_0, frontFrameAddr);

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

	fill(0, 0, DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT, toPixel(color));
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
		put(x, y, toPixel(color));
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
		put(x1, y1, toPixel(color));
	}

	// Cas que hagi una regio rectangular per dibuixar
	//
	else if ((x1 <= x2) && (y1 <= y2)) {
		rotate(x1, y1, x2, y2);
		fill(x1, y1, x2 - x1 + 1, y2 - y1 + 1, toPixel(color));
	}
}


/// ----------------------------------------------------------------------
/// \brief Escriu una regio rectangular de pixels.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param width: Amplada.
/// \param height: Alçada.
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
	PixelFormat format,
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
/// \param height: Alçada de la regio.
/// \param pixels: Buffer de pixels.
/// \param format: Format de pixels.
///
void RGBDirectDriver::readPixels(
	int x,
	int y,
	int width,
	int height,
	uint8_t *pixels,
	PixelFormat format,
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
	halLTDCSetFrameAddress(HAL_LTDC_LAYER_0, frontFrameAddr);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul GPIO.
///
void RGBDirectDriver::gpioInitialize() {

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
void RGBDirectDriver::ltdcInitialize() {

	uint32_t tmp;

	// Configura el rellotge
	// PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
	// PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz
	// PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz
	// LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_4 = 38.4/4 = 9.6Mhz
	//
	RCC_PeriphCLKInitTypeDef clkInit;
	clkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	clkInit.PLLSAI.PLLSAIN = 192;
	clkInit.PLLSAI.PLLSAIR = DISPLAY_FDIV;
	clkInit.PLLSAIDivR = RCC_PLLSAIDIVR_4;
	HAL_RCCEx_PeriphCLKConfig(&clkInit);

    // Activa el modul LTDC
    //
    RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;

    // Configure el registre GCR (General Configuration Register)
    // -Polaritat HSYNC, VSYNC, DE i PC
    //
    tmp = LTDC->GCR;
    tmp &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL);
    tmp |= DISPLAY_HSPOL << LTDC_GCR_HSPOL_Pos;
    tmp |= DISPLAY_VSPOL << LTDC_GCR_VSPOL_Pos;
    tmp |= DISPLAY_DEPOL << LTDC_GCR_DEPOL_Pos;
    tmp |= DISPLAY_PCPOL << LTDC_GCR_PCPOL_Pos;
    LTDC->GCR = tmp;

    // Configura el registre SSCR (Sinchronization Size Configuration Register)
    //
    tmp = LTDC->SSCR;
    tmp &= ~(LTDC_SSCR_HSW | LTDC_SSCR_VSH);
    tmp |= (DISPLAY_HSYNC - 1) << LTDC_SSCR_HSW_Pos;
    tmp |= (DISPLAY_VSYNC - 1) << LTDC_SSCR_VSH_Pos;
    LTDC->SSCR = tmp;

    // Configura el registre BPCR (Back Porch Configuration Register)
    //
    tmp = LTDC->BPCR;
    tmp &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
    tmp |= (DISPLAY_HSYNC + DISPLAY_HBP - 1) << LTDC_BPCR_AHBP_Pos;
    tmp |= (DISPLAY_VSYNC + DISPLAY_VBP - 1) << LTDC_BPCR_AVBP_Pos;
    LTDC->BPCR = tmp;

    // Configura el registre AWCR (Active Width Configuration Register)
    // -AAH = HSYNC + HBP + WIDTH - 1
    // -AAW = VSYNC + VBP + HEIGHT - 1
    //
    tmp = LTDC->AWCR;
    tmp &= ~(LTDC_AWCR_AAW | LTDC_AWCR_AAH);
    tmp |= (DISPLAY_HSYNC + DISPLAY_HBP + DISPLAY_IMAGE_WIDTH - 1) << LTDC_AWCR_AAW_Pos;
    tmp |= (DISPLAY_VSYNC + DISPLAY_VBP + DISPLAY_IMAGE_HEIGHT - 1) << LTDC_AWCR_AAH_Pos;
    LTDC->AWCR = tmp;

    // Configura el registre TWCR (Total Width Configuration Register)
    // -TOTALW = HSYNC + HBP + WIDTH + HFP - 1
    // -TOTALH = VSYNC + VBP + HEIGHT + VFP - 1
    //
    tmp = LTDC->TWCR;
    tmp &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
    tmp |= (DISPLAY_HSYNC + DISPLAY_HBP + DISPLAY_IMAGE_WIDTH + DISPLAY_HFP - 1) << LTDC_TWCR_TOTALW_Pos;
    tmp |= (DISPLAY_VSYNC + DISPLAY_VBP + DISPLAY_IMAGE_HEIGHT + DISPLAY_VFP - 1) << LTDC_TWCR_TOTALH_Pos;
    LTDC->TWCR = tmp;

    // Configura el registre BCCR (Back Color Configuration Register)
    //
    tmp = LTDC->BCCR;
    tmp &= ~(LTDC_BCCR_BCRED | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCBLUE);
    tmp |= 0 << LTDC_BCCR_BCRED_Pos;
    tmp |= 0 << LTDC_BCCR_BCGREEN_Pos;
    tmp |= 255 << LTDC_BCCR_BCBLUE_Pos;
    LTDC->BCCR = tmp;

    // Configura Lx_WHPCR (Window Horizontal Position Configuration Register)
    // -Tamany horitzontal de la finestra
    //
    tmp = LTDC_Layer1->WHPCR;
    tmp &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
    tmp |= ((DISPLAY_HSYNC + DISPLAY_HBP - 1) + 1) << LTDC_LxWHPCR_WHSTPOS_Pos;
    tmp |= ((DISPLAY_HSYNC + DISPLAY_HBP - 1) + DISPLAY_IMAGE_WIDTH) << LTDC_LxWHPCR_WHSPPOS_Pos;
    LTDC_Layer1->WHPCR = tmp;

    // Configura Lx_WHPCR (Window Vertical Position Configuration Register)
    // -Tamany vertical de la finestra
    //
    tmp = LTDC_Layer1->WVPCR;
    tmp &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
    tmp |= ((DISPLAY_VSYNC + DISPLAY_VBP - 1) + 1) << LTDC_LxWVPCR_WVSTPOS_Pos;
    tmp |= ((DISPLAY_VSYNC + DISPLAY_VBP - 1) + DISPLAY_IMAGE_HEIGHT) << LTDC_LxWVPCR_WVSPPOS_Pos;
    LTDC_Layer1->WVPCR = tmp;

    // Configura Lx_DCCR (Default Color Configuration Register)
    // -Color per defecte ARGB(255, 0, 0, 0)
    //
    LTDC_Layer1->DCCR = 0xFF0000FF;

    // Configura Lx_PFCR (Pixel Format Configuration Register)
    //
    tmp = LTDC_Layer1->PFCR;
    tmp &= ~(LTDC_LxPFCR_PF);
    tmp |= LTDC_LxPFCR_PF_DEFAULT << LTDC_LxPFCR_PF_Pos;
    LTDC_Layer1->PFCR = tmp;

    // Configura Lx_CACR (Constant Alpha Configuration Register)
    //
    tmp = LTDC_Layer1->CACR;
    tmp &= ~(LTDC_LxCACR_CONSTA);
    tmp |= 255u;
    LTDC_Layer1->CACR;

    // Configura Lx_BFCR
    // -Specifies the blending factors
    //
    tmp = LTDC_Layer1->BFCR;
    tmp &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
    tmp |= 6 << LTDC_LxBFCR_BF1_Pos;
    tmp |= 7 << LTDC_LxBFCR_BF2_Pos;
    LTDC_Layer1->BFCR = tmp;

    // Configura Lx_CFBLR (Color Frame Buffer Length Register)
    // -Longitut de la linia en bytes.
    //
    tmp = LTDC_Layer1->CFBLR;
    tmp &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
    tmp |= LINE_SIZE << LTDC_LxCFBLR_CFBP_Pos;
    tmp |= ((DISPLAY_IMAGE_WIDTH * sizeof(pixel_t)) + 3) << LTDC_LxCFBLR_CFBLL_Pos;
    LTDC_Layer1->CFBLR = tmp;

    // Configura Lx_CFBLNR (Color Frame Buffer Line Number Register)
    //
    tmp = LTDC_Layer1->CFBLNR;
    tmp  &= ~(LTDC_LxCFBLNR_CFBLNBR);
    tmp |= DISPLAY_IMAGE_HEIGHT;
    LTDC_Layer1->CFBLNR = tmp;

    // Actualitza els parametres de la capa inmediatament
    //
	LTDC->SRCR |= LTDC_SRCR_IMR;
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
/// \param c: Color en format de pixel fisic;
/// \remarks No es fa cap tipus de verificacio dels parametres.
///
void RGBDirectDriver::put(
	int x,
	int y,
	pixel_t c) {

	*((pixel_t*) addressOf(backFrameAddr, x, y)) = c;
}


/// ----------------------------------------------------------------------
/// \brief Ompla un area de memoria amb un color.
/// \param x: Coordinada x.
/// \param y: Coordinada y.
/// \param width: Amplada del bloc.
/// \param height: Alçada del bloc.
/// \param c: Color en format de pixel fisic.
/// \remarks No es fa cap tipus de verificacio dels parametres.
///
void RGBDirectDriver::fill(
	int x,
	int y,
	int width,
	int height,
	pixel_t c) {

	halDMA2DStartFill(
		addressOf(backFrameAddr, x, y),
		width,
		height,
		LINE_WIDTH - width,
		HAL_DMA2D_DFMT_DEFAULT,
		c);
	halDMA2DWaitForFinish();
}


/// ----------------------------------------------------------------------
/// \brief Copia un bitmap de la memoria a la pantalla.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param width: Amplada.
/// \param height: Alçada.
/// \param pixels: Llista de pixels.
/// \param format: Format dels pixels.
/// \param dx: Offset X dins del bitmap.
/// \param dy: offset Y dins del vitmap.
/// \param pitch: Amplada de linia del bitmap.
///
void RGBDirectDriver::copy(
	int x,
	int y,
	int width,
	int height,
	const uint8_t *pixels,
	PixelFormat format,
	int dx,
	int dy,
	int pitch) {

	// Inicialitza el controlador DMA2D
	// -Modus de transferencia M2M/PFC
	//
	DMA2D->CR = 0b01 << DMA2D_CR_MODE_Pos;

	// Format de color de desti
	//
#if defined(DISPLAY_COLOR_RGB565)
	DMA2D->OPFCCR = 0b010 << DMA2D_OPFCCR_CM_Pos;
#elif defined(DISPLAY_COLOR_RGB888)
	DMA2D->OPFCCR = 0b001 << DMA2D_OPFCCR_CM_Pos;
#else
#error No se especifico DISPLAY_COLOR_xxxx
#endif

	// Adressa i pitch de desti
	//
	int dstAddr = addressOf(backFrameAddr, x, y);
	DMA2D->OMAR = dstAddr;
	DMA2D->OOR = LINE_WIDTH - width;

	// Format de color d'origen
	//
	switch (format) {
		case PixelFormat::rgb888:
			DMA2D->FGPFCCR = 0b0001 << DMA2D_FGPFCCR_CM_Pos;
			break;

		case PixelFormat::rgb565:
			DMA2D->FGPFCCR = 0b0010 << DMA2D_FGPFCCR_CM_Pos;
			break;

		default:
		case PixelFormat::argb8888:
			DMA2D->FGPFCCR = 0b0000 << DMA2D_FGPFCCR_CM_Pos;
			break;
	}

	// Adressa i pitch d'origen
	//
	int orgAddr = (dy * pitch) + dx;
	switch (format) {
		default:
		case PixelFormat::rgb888:
		case PixelFormat::argb8888:
			orgAddr *= sizeof(uint32_t);
			break;

		case PixelFormat::rgb565:
			orgAddr *= sizeof(uint16_t);
			break;
	}
	orgAddr += (int) pixels;
	DMA2D->FGMAR = orgAddr;
	DMA2D->FGOR = pitch - width;

	// Tamany de la finestra
	//
	DMA2D->NLR =
		(width << DMA2D_NLR_PL_Pos) |
		(height << DMA2D_NLR_NL_Pos);

	// Inicia la transferencia
	//
	DMA2D->CR |= 1 << DMA2D_CR_START_Pos;

	/// Espera que acabi
	///
	halDMA2DWaitForFinish();
}

#endif // DISPLAY_DRV_RGBLTDC

