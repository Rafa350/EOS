#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/eosRGBDirect.h"
#include "HAL/halGPIO.h"
#include "stdint.h"


#if !defined(EOS_STM32F4) && !defined(EOS_STM32F7)
#error Hardware no soportado
#endif


#if defined(EOS_STM32F4)
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_ltdc.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_ltdc.h"
#endif


// Format de pixel
//
#if defined(DISPLAY_COLOR_RGB565)
#define PIXEL_TYPE           uint16_t
#define PIXEL_VALUE(c)       c.toRGB565()
#define LTDC_PIXEL_FORMAT    LTDC_PIXEL_FORMAT_RGB565
#elif defined(DISPLAY_COLOR_RGB888)
#define PIXEL_TYPE           uint32_t
#define PIXEL_VALUE(c)       c.toRGB888()
#define LTDC_PIXEL_FORMAT    LTDC_PIXEL_FORMAT_RGB888
#else
#error No se definio DISPLAY_COLOR_xxxx
#endif
#define PIXEL_SIZE           ((int) sizeof(PIXEL_TYPE))

#define FREQUENCY_DIVIDER    5


using namespace eos;


IDisplayDriver *RGBDirectDriver::instance = nullptr;

static LTDC_HandleTypeDef ltdcHandler;


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

	orientation(DisplayOrientation::normal),
	vRamAddr(DISPLAY_VRAM_ADDR) {

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el driver.
///
void RGBDirectDriver::initialize() {

	gpioInitialize();
	ltdcInitialize();
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

	this->orientation = orientation;
	switch (orientation) {
		case DisplayOrientation::normal:
			break;

		case DisplayOrientation::rotate90:
			break;

		case DisplayOrientation::rotate180:
			break;

		case DisplayOrientation::rotate270:
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
/// \param color: Color de borrat.
///
void RGBDirectDriver::clear(
	const Color &color) {

	dma2dFill(0, 0, DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT, color);
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

	if ((x >= 0) && (x < DISPLAY_SCREEN_WIDTH) && (y >= 0) && (y < DISPLAY_SCREEN_HEIGHT)) {

		int addr = vRamAddr + (y * DISPLAY_SCREEN_WIDTH + x) * PIXEL_SIZE;
		*((PIXEL_TYPE*)addr) = PIXEL_VALUE(color);
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

	if ((y >= 0) && (y < DISPLAY_SCREEN_HEIGHT)) {

		int x2 = x + size - 1;
		if (x < 0)
			x = 0;
		if (x2 >= DISPLAY_SCREEN_WIDTH)
			x2 = DISPLAY_SCREEN_WIDTH - 1;
		size = x2 - x + 1;

		if (size > 0)
			dma2dFill(x, y, size, 1, color);
	}
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

	if ((x >= 0) && (x < DISPLAY_SCREEN_WIDTH)) {

		int y2 = y + size - 1;
		if (y < 0)
			y = 0;
		if (y2 >= DISPLAY_SCREEN_HEIGHT)
			y2 = DISPLAY_SCREEN_HEIGHT - 1;
		size = y2 - y + 1;

		if (size > 0)
			dma2dFill(x, y, 1, size, color);
	}

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

    dma2dFill(x, y, width, height, color);
}


void RGBDirectDriver::writePixels(
	int x,
	int y,
	int width,
	int height,
	const Color *colors) {

	dma2dCopy(x, y, width, height, colors);
}


void RGBDirectDriver::readPixels(
	int x,
	int y,
	int width,
	int height,
	Color *colors) {

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

	// Configura el rellotge
	// PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
	// PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz
	// PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz
	// LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_4 = 38.4/4 = 9.6Mhz
	//
	RCC_PeriphCLKInitTypeDef clkInit;
	clkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	clkInit.PLLSAI.PLLSAIN = 192;
	clkInit.PLLSAI.PLLSAIR = FREQUENCY_DIVIDER;
	clkInit.PLLSAIDivR = RCC_PLLSAIDIVR_4;
	HAL_RCCEx_PeriphCLKConfig(&clkInit);

	// Configura el LTDC
	//
	ltdcHandler.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	ltdcHandler.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	ltdcHandler.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	ltdcHandler.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	ltdcHandler.Init.HorizontalSync = DISPLAY_HSYNC - 1;
	ltdcHandler.Init.VerticalSync = DISPLAY_VSYNC - 1;
	ltdcHandler.Init.AccumulatedHBP = DISPLAY_HSYNC + DISPLAY_HBP - 1;
	ltdcHandler.Init.AccumulatedVBP = DISPLAY_VSYNC + DISPLAY_VBP - 1;
	ltdcHandler.Init.AccumulatedActiveH = DISPLAY_SCREEN_HEIGHT + DISPLAY_VSYNC + DISPLAY_VBP - 1;
	ltdcHandler.Init.AccumulatedActiveW = DISPLAY_SCREEN_WIDTH + DISPLAY_HSYNC + DISPLAY_HBP - 1;
	ltdcHandler.Init.TotalHeigh = DISPLAY_SCREEN_HEIGHT + DISPLAY_VSYNC + DISPLAY_VBP + DISPLAY_VFP - 1;
	ltdcHandler.Init.TotalWidth = DISPLAY_SCREEN_WIDTH + DISPLAY_HSYNC + DISPLAY_HBP + DISPLAY_HFP - 1;
	ltdcHandler.Init.Backcolor.Blue = 0;
	ltdcHandler.Init.Backcolor.Green = 0;
	ltdcHandler.Init.Backcolor.Red = 0;
	ltdcHandler.Instance = LTDC;

	__HAL_RCC_LTDC_CLK_ENABLE();
	HAL_LTDC_Init(&ltdcHandler);

    // Configura les pagines
	//
	LTDC_LayerCfgTypeDef layerCfg;
	layerCfg.WindowX0 = 0;
	layerCfg.WindowX1 = DISPLAY_SCREEN_WIDTH;
	layerCfg.WindowY0 = 0;
	layerCfg.WindowY1 = DISPLAY_SCREEN_HEIGHT;
	layerCfg.PixelFormat = LTDC_PIXEL_FORMAT;
	layerCfg.FBStartAdress = vRamAddr;
	layerCfg.Alpha = 255;
	layerCfg.Alpha0 = 0;
	layerCfg.Backcolor.Blue = 0;
	layerCfg.Backcolor.Green = 0;
	layerCfg.Backcolor.Red = 0;
	layerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
	layerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
	layerCfg.ImageWidth  = DISPLAY_SCREEN_WIDTH;
	layerCfg.ImageHeight = DISPLAY_SCREEN_HEIGHT;

	for (uint_fast8_t pageNum = 0; pageNum < 1; pageNum++) {
		layerCfg.FBStartAdress = vRamAddr;
		HAL_LTDC_ConfigLayer(&ltdcHandler, &layerCfg, pageNum);
	}
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
	int addr = vRamAddr + (y * DISPLAY_SCREEN_WIDTH + x) * PIXEL_SIZE;

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
	DMA2D->OOR = DISPLAY_SCREEN_WIDTH - width;        // Offset entre linies
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
/// \brief Copia un bitmap.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param width: Amplada.
/// \param height: Alçada.
/// \param colors: Llista de colors a copiar (Amplada * Alçada).
///
void RGBDirectDriver::dma2dCopy(
	int x,
	int y,
	int width,
	int height,
	const Color *colors) {

	// Calcula l'adresa inicial
	//
	int addr = vRamAddr + (y * DISPLAY_SCREEN_WIDTH + x) * PIXEL_SIZE;

	// Inicialitza el controlador DMA2D
	//
	DMA2D->CR = 0b01 << DMA2D_CR_MODE_Pos;            // Modus de transferencia M2M/PFC
#if defined(DISPLAY_COLOR_RGB565)
	DMA2D->OPFCCR = 0b010 << DMA2D_OPFCCR_CM_Pos;     // Format desti RGB565
#elif defined(DISPLAY_COLOR_RGB888)
	DMA2D->OPFCCR = 0b001 << DMA2D_OPFCCR_CM_Pos;     // Format desti RGB888
#else
#error No se especifico DISPLAY_COLOR_xxxx
#endif
	DMA2D->FGPFCCR = 0b0000 << DMA2D_FGPFCCR_CM_Pos;  // Format origen ARGB8888
	DMA2D->FGMAR = (uint32_t)colors;                  // Adressa origen
	DMA2D->OMAR = addr;                               // Adressa desti
	DMA2D->FGOR = 0;                                  // Offset origen
	DMA2D->OOR = DISPLAY_SCREEN_WIDTH - width;        // Offset desti
	DMA2D->NLR =
		(width << DMA2D_NLR_PL_Pos) |                 // Amplada
		(height << DMA2D_NLR_NL_Pos);                 // Alçada

	// Inicia la transferencia
	//
	DMA2D->CR |= 1 << DMA2D_CR_START_Pos;             // Inicia la transferencia

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

