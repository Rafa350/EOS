#include "eos.h"

#ifdef DISPLAY_DRV_RGBLTDC

#include "eosAssert.h"
#include "System/eosMath.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "HAL/halGPIO.h"


#if !((defined(LTDC) && (defined(EOS_STM32F4) || defined(EOS_STM32F7))))
#error Hardware no soportado
#endif



// Format de pixel
//
#if defined(DISPLAY_COLOR_RGB565)
#define PIXEL_VALUE(c)       c.toRGB565()
#elif defined(DISPLAY_COLOR_RGB888)
#define PIXEL_VALUE(c)       c.toRGB888()
#else
#error No se definio DISPLAY_COLOR_xxxx
#endif



/// ----------------------------------------------------------------------
/// \brief Obte l'adressa del pixel en la coordinada especificada.
/// \param base: Adressa base.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \return L'adressa del pixel.
///
static inline int addressAt(
	int base,
	int x,
	int y) {

	return base + (((y * LINE_WIDTH) + x) * PIXEL_SIZE);
}


using namespace eos;


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
	sin(0),
	cos(1),
	dx(0),
	dy(0),
	orientation(DisplayOrientation::normal),
	layer1Addr(DISPLAY_VRAM_ADDR) {
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el driver.
///
void RGBDirectDriver::initialize() {

	gpioInitialize();
	ltdcInitialize();
	ltdcInitializeLayer(LTDC_Layer1, layer1Addr);
	//ltdcInitializeLayer(LTDC_Layer2, layer2Addr);
	ltdcActivateLayer(LTDC_Layer1, true);
	dma2dInitialize();
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
				screenWidth = DISPLAY_IMAGE_WIDTH;
				screenHeight = DISPLAY_IMAGE_HEIGHT;
				sin = 0;
				cos = 1;
				dx = 0;
				dy = 0;
				break;

			case DisplayOrientation::rotate90:
				screenWidth = DISPLAY_IMAGE_HEIGHT;
				screenHeight = DISPLAY_IMAGE_WIDTH;
				sin = 1;
				cos = 0;
				dx = DISPLAY_IMAGE_WIDTH - 1;
				dy = 0;
				break;

			case DisplayOrientation::rotate180:
				screenWidth = DISPLAY_IMAGE_WIDTH;
				screenHeight = DISPLAY_IMAGE_HEIGHT;
				sin = 0;
				cos = -1;
				dx = DISPLAY_IMAGE_WIDTH - 1;
				dy = DISPLAY_IMAGE_HEIGHT - 1;
				break;

			case DisplayOrientation::rotate270:
				screenWidth = DISPLAY_IMAGE_HEIGHT;
				screenHeight = DISPLAY_IMAGE_WIDTH;
				sin = -1;
				cos = 0;
				dx = 0;
				dy = DISPLAY_IMAGE_HEIGHT - 1;
				break;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
/// \param color: Color de borrat.
///
void RGBDirectDriver::clear(
	const Color &color) {

	dma2dFill(0, 0, DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT, color);
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

	// Comprova si es dins dels limits
	//
	if ((x >= 0) && (x < screenWidth) && (y >= 0) && (y < screenHeight)) {

		// Rotacio
		//
		int xx = dx + (x * cos) - (y * sin);
		int yy = dy + (x * sin) + (y * cos);

		// Dibuixa el pixel
		//
		*((PIXEL_TYPE*) addressAt(layer1Addr, xx, yy)) = PIXEL_VALUE(color);
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

	// Comprova si es dins dels limits
	//
	if ((x >= 0) && (x + width <= screenWidth) &&
		(y >= 0) && (y + height <= screenHeight) &&
		(width > 0) && (height > 0)) {

		// Si es del tamany d'un pixel, utilitza la funcio setPixel
		//
		if ((width == 1) && (height == 1))
			setPixel(x, y, color);

		else {

			int x2 = x + width - 1;
			int y2 = y + height - 1;

			int xx1 = dx + (x * cos) - (y * sin);
			int xx2 = dx + (x2 * cos) - (y2 * sin);
			int yy1 = dy + (x * sin) + (y * cos);
			int yy2 = dy + (x2 * sin) + (y2 * cos);

			int xx = Math::min(xx1, xx2);
			int yy = Math::min(yy1, yy2);
			int ww = Math::abs(xx2 - xx1) + 1;
			int hh = Math::abs(yy2 - yy1) + 1;

			dma2dFill(xx, yy, ww, hh, color);
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief Escriu pixels en la pantalla.
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

		dma2dCopy(x, y, width, height, pixels, format, dx, dy, pitch);
	}
}


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


void RGBDirectDriver::vScroll(
	int delta,
	int x,
	int y,
	int width,
	int height) {

}


void RGBDirectDriver::hScroll(
	int delta,
	int x,
	int y,
	int width,
	int height) {

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

    // Inicialitza el modul LTDC
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

    // Activa el controlador
    //
    LTDC->GCR |= LTDC_GCR_LTDCEN;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la capa especificada.
/// \param: layer: Bloc de registres de la capa.
/// \param frameAddr: Adressa de la memoria de video.
/// \remarks La capa s'inicialitza desactivada.
///
void RGBDirectDriver::ltdcInitializeLayer(
	LTDC_Layer_TypeDef *layer,
	int frameAddr) {

	uint32_t tmp;

    // Configura la Layer-1 WHPCR (Window Horizontal Position Configuration Register)
    // -Tamany horitzontal de la finestra
    //
    tmp = layer->WHPCR;
    tmp &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
    tmp |= ((DISPLAY_HSYNC + DISPLAY_HBP - 1) + 1) << LTDC_LxWHPCR_WHSTPOS_Pos;
    tmp |= ((DISPLAY_HSYNC + DISPLAY_HBP - 1) + DISPLAY_IMAGE_WIDTH) << LTDC_LxWHPCR_WHSPPOS_Pos;
    layer->WHPCR = tmp;

    // Configura Lx_WHPCR (Window Vertical Position Configuration Register)
    // -Tamany vertical de la finestra
    //
    tmp = layer->WVPCR;
    tmp &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
    tmp |= ((DISPLAY_VSYNC + DISPLAY_VBP - 1) + 1) << LTDC_LxWVPCR_WVSTPOS_Pos;
    tmp |= ((DISPLAY_VSYNC + DISPLAY_VBP - 1) + DISPLAY_IMAGE_HEIGHT) << LTDC_LxWVPCR_WVSPPOS_Pos;
    layer->WVPCR = tmp;

    // Configura Lx_DCCR (Default Color Configuration Register)
    // -Color per defecte ARGB(255, 0, 0, 0)
    //
    layer->DCCR = 0xFF0000FF;

    // Configura Lx_PFCR (Pixel Format Configuration Register)
    //
    tmp = layer->PFCR;
    tmp &= ~(LTDC_LxPFCR_PF);
#if defined(DISPLAY_COLOR_RGB565)
    tmp |= 0b010 << LTDC_LxPFCR_PF_Pos;
#elif defined(DISPLAY_COLOR_RGB888)
    tmp |= 0b001 << LTDC_LxPFCR_PF_Pos;
#else
#error No se especifico DISPLAY_COLOR_xxxx
#endif
    layer->PFCR = tmp;

    // Configura Lx_CACR (Constant Alpha Configuration Register)
    //
    tmp = layer->CACR;
    tmp &= ~(LTDC_LxCACR_CONSTA);
    tmp |= 255u;
    layer->CACR;

    // Configura Lx_BFCR
    // -Specifies the blending factors
    //
    tmp = layer->BFCR;
    tmp &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
    tmp |= 6 << LTDC_LxBFCR_BF1_Pos;
    tmp |= 7 << LTDC_LxBFCR_BF2_Pos;
    layer->BFCR = tmp;

    // Configura Lx_CFBAR (Color Frame Buffer Address Register)
    // -Adressa del buffer de video
    //
    layer->CFBAR = frameAddr;

    // Configura Lx_CFBLR (Color Frame Buffer Length Register)
    // -Longitut de la linia en bytes.
    //
    tmp = layer->CFBLR;
    tmp &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
    tmp |= LINE_SIZE << LTDC_LxCFBLR_CFBP_Pos;
    tmp |= ((DISPLAY_IMAGE_WIDTH * PIXEL_SIZE) + 3) << LTDC_LxCFBLR_CFBLL_Pos;
    layer->CFBLR = tmp;

    // Configura Lx_CFBLNR (Color Frame Buffer Line Number Register)
    //
    tmp = layer->CFBLNR;
    tmp  &= ~(LTDC_LxCFBLNR_CFBLNBR);
    tmp |= DISPLAY_IMAGE_HEIGHT;
    layer->CFBLNR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief Activa una capa.
/// \param layer: Bloc de registres de la capa.
/// \param active: True per activar, false per desactivar.
///
void RGBDirectDriver::ltdcActivateLayer(
	LTDC_Layer_TypeDef *layer,
	bool activate) {

	if (activate)
		layer->CR |= (uint32_t) LTDC_LxCR_LEN;
	else
		layer->CR &= (uint32_t) ~(LTDC_LxCR_LEN);
    LTDC->SRCR |= LTDC_SRCR_IMR;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul DMA2D.
///
void RGBDirectDriver::dma2dInitialize() {

    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;
}


/// ----------------------------------------------------------------------
/// \brief Ompla un area de memoria amb un color.
/// \param x: Coordinada x.
/// \param y: Coordinada y.
/// \param width: Amplada del bloc.
/// \param height: Alçada del bloc.
/// \param color: El color per omplir.
///
void RGBDirectDriver::dma2dFill(
	int x,
	int y,
	int width,
	int height,
	const Color &color) {

	// Calcula l'adresa inicial
	//
	int addr = addressAt(layer1Addr, x, y);

	// Inicialitza el controlador DMA2D
	//
	DMA2D->CR = 0b11 << DMA2D_CR_MODE_Pos;            // Modus de transferencia R2M
#if defined(DISPLAY_COLOR_RGB565)
	DMA2D->OPFCCR = 0b010 << DMA2D_OPFCCR_CM_Pos;     // Format de color RGB565
	DMA2D->OCOLR = color.toRGB565();                  // Color en format RGB565
#elif defined(DISPLAY_COLOR_RGB888)
	DMA2D->OPFCCR = 0b001 << DMA2D_OPFCCR_CM_Pos;     // Format de color RGB888
	DMA2D->OCOLR = color.toRGB888();                  // Color en format RGB888
#else
#error No se especifico DISPLAY_COLOR_xxxx
#endif
	DMA2D->OMAR = addr;                               // Adressa del primer pixel
	DMA2D->OOR = LINE_WIDTH - width;                  // Offset entre linies
	DMA2D->NLR =
		(width << DMA2D_NLR_PL_Pos) |                 // Amplada
		(height << DMA2D_NLR_NL_Pos);                 // Alçada

	// Inicia la transferencia
	//
	DMA2D->CR |= 1 << DMA2D_CR_START_Pos;             // Inicia la transferencia

	// Espera que acabi
	//
	dma2dWaitFinish();
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
/// \param pitch: Aplada de linia del bitmap.
///
void RGBDirectDriver::dma2dCopy(
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
	int dstAddr = addressAt(layer1Addr, x, y);
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
	dma2dWaitFinish();
}


/// ----------------------------------------------------------------------
/// \brief Espera que acabi la transaccio.
///
void RGBDirectDriver::dma2dWaitFinish() {

	// Espera que acabi
	//
	while ((DMA2D->ISR & DMA2D_ISR_TCIF_Msk) == 0) {

		// Si troba errors, finalitza
		//
		volatile uint32_t isr = DMA2D->ISR;
		if (((isr & DMA2D_ISR_CEIF_Msk) != 0) | ((isr & DMA2D_ISR_TEIF_Msk) != 0)) {
			DMA2D->IFCR |=
					1 << DMA2D_IFCR_CCEIF_Pos |
					1 << DMA2D_IFCR_CTEIF_Pos;
			return;
		}
	}
	DMA2D->IFCR |= 1 << DMA2D_IFCR_CTCIF_Pos;
}


#endif // USE_DISPLAY_RGB
