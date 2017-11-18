#include "Controllers/Display/Drivers/eosRGBDirect.h"
#include "HAL/halGPIO.h"


#if !defined(EOS_STM32F4) && !defined(EOS_STM32F7)
#error Hardware no soportado
#endif


#if defined(EOS_STM32F4)
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_ltdc.h"
#include "stm32f4xx_hal_dma2d.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_ltdc.h"
#include "stm32f7xx_hal_dma2d.h"
#endif


// Format de pixel
//
#if defined(RGBDIRECT_COLORMODE_565)
#define PIXEL_TYPE           uint16_t
#define PIXEL_VALUE(c)       c.toRGB565()
#define LTDC_PIXEL_FORMAT    LTDC_PIXEL_FORMAT_RGB565
#define DMA2D_INPUT          DMA2D_INPUT_RGB565
#define DMA2D_OUTPUT         DMA2D_OUTPUT_RGB565

#elif defined(RGBDIRECT_COLOTMODE_RGB888)
#define PIXEL_TYPE           uint32_t
#define PIXEL_VALUE(c)       c.toRGB888()
#define LTDC_PIXEL_FORMAT    LTDC_PIXEL_FORMAT_RGB888
#define DMA2D_INPUT          DMA2D_INPUT_RGB888
#define DMA2D_OUTPUT         DMA2D_OUTPUT_RGB888

#endif

// Format de la imatge
//
#define IMAGE_WIDTH          ((int32_t)RGBDIRECT_SCREEN_WIDTH)
#define IMAGE_HEIGHT         ((int32_t)RGBDIRECT_SCREEN_HEIGHT)
#define IMAGE_PAGES          ((int32_t)1)
#define IMAGE_SIZE           ((int32_t)(RGBDIRECT_SCREEN_WIDTH * RGBDIRECT_SCREEN_HEIGHT * IMAGE_PAGES * sizeof(PIXEL_TYPE)))
#define IMAGE_BUFFER		 RGBDIRECT_VRAM

#define  FREQUENCY_DIVIDER    5


using namespace eos;


IDisplayDriver *RGBDirect_Driver::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief Obte una instancia unica del driver.
/// \return La instancia del driver.
///
IDisplayDriver *RGBDirect_Driver::getInstance() {

	if (instance == nullptr)
		instance = new RGBDirect_Driver();
	return instance;
}


/// ----------------------------------------------------------------------
/// \brief Contructor
///
RGBDirect_Driver::RGBDirect_Driver():

	screenWidth(RGBDIRECT_SCREEN_WIDTH),
	screenHeight(RGBDIRECT_SCREEN_HEIGHT),
	curLayer(0),
	image((uint8_t*)IMAGE_BUFFER) {

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el driver.
///
void RGBDirect_Driver::initialize() {

	gpioInitialize();
	ltdcInitialize();
	dma2dInitialize();
}


/// ---------------------------------------------------------------------
/// \brief Finalitza el driver.
///
void RGBDirect_Driver::shutdown() {

	displayOff();
}


/// ----------------------------------------------------------------------
/// \brief Activa el display.
///
void RGBDirect_Driver::displayOn() {

	// Activa el display
	//
	halGPIOSetPin(RGBDIRECT_LCDE_PORT, RGBDIRECT_LCDE_PIN);

	// Activa el backlight
	//
	halGPIOSetPin(RGBDIRECT_BKE_PORT, RGBDIRECT_BKE_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el display.
///
void RGBDirect_Driver::displayOff() {

	// Desactiva el display
	//
	halGPIOClearPin(RGBDIRECT_LCDE_PORT, RGBDIRECT_LCDE_PIN);

	// Desactiva el backlight
	//
	halGPIOClearPin(RGBDIRECT_BKE_PORT, RGBDIRECT_BKE_PIN);
}


void RGBDirect_Driver::setOrientation(
	DisplayOrientation orientation) {

}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
/// \param color: Color de borrat.
///
void RGBDirect_Driver::clear(
	const Color &color) {

	dma2dFill(image, IMAGE_WIDTH, IMAGE_HEIGHT, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param color: Color del pixel.
///
void RGBDirect_Driver::setPixel(
	int16_t x,
	int16_t y,
	const Color &color) {

	if ((x >= 0) && (x < IMAGE_WIDTH) && (y >= 0) && (y < IMAGE_HEIGHT)) {
		uint32_t offset = (y * IMAGE_WIDTH + x) * sizeof(PIXEL_TYPE);
		*((PIXEL_TYPE*)(image + offset + (curLayer * IMAGE_SIZE))) = PIXEL_VALUE(color);
	}
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels horitzontals.
/// \param x: Coordinada X.
/// \param y: Colordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void RGBDirect_Driver::setHPixels(
	int16_t x,
	int16_t y,
	int16_t size,
	const Color &color) {

	if ((y >= 0) && (y < IMAGE_HEIGHT)) {

		int16_t x2 = x + size - 1;
		if (x < 0)
			x = 0;
		if (x2 >= IMAGE_WIDTH)
			x2 = IMAGE_WIDTH - 1;
		size = x2 - x + 1;

		if (size > 0) {
			uint32_t offset = (y * IMAGE_WIDTH + x) * sizeof(PIXEL_TYPE);
			uint8_t *addr = (uint8_t*) (image + offset + (curLayer * IMAGE_SIZE));
			dma2dFill(addr, size, 1, color);
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels en vertical.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void RGBDirect_Driver::setVPixels(
	int16_t x,
	int16_t y,
	int16_t size,
	const Color &color) {

	if ((x >= 0) && (x < IMAGE_WIDTH)) {

		int16_t y2 = y + size - 1;
		if (y < 0)
			y = 0;
		if (y2 >= IMAGE_HEIGHT)
			y2 = IMAGE_HEIGHT - 1;
		size = y2 - y + 1;

		if (size > 0) {
			uint32_t offset = (y * IMAGE_WIDTH + x) * sizeof(PIXEL_TYPE);
			uint8_t *addr = (uint8_t*) (image + offset + (curLayer * IMAGE_SIZE));
			dma2dFill(addr, 1, size, color);
		}
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
void RGBDirect_Driver::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color &color) {

	uint32_t offset = (y * IMAGE_WIDTH + x) * sizeof(PIXEL_TYPE);
	uint8_t *addr = (uint8_t*) (image + offset + (curLayer * IMAGE_SIZE));
    dma2dFill(addr, width, height, color);
}


void RGBDirect_Driver::writePixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color *colors) {
}


void RGBDirect_Driver::readPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	Color *colors) {

}


void RGBDirect_Driver::vScroll(
	int16_t delta,
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height) {

}


void RGBDirect_Driver::hScroll(
	int16_t delta,
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height) {

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul GPIO.
///
void RGBDirect_Driver::gpioInitialize() {

	static const GPIOInitializePinInfo gpioInit[] = {
		{RGBDIRECT_LCDE_PORT, RGBDIRECT_LCDE_PIN, HAL_GPIO_MODE_OUTPUT_PP, 0 },
		{RGBDIRECT_BKE_PORT, RGBDIRECT_BKE_PIN, HAL_GPIO_MODE_OUTPUT_PP, 0 },

		{RGBDIRECT_HSYNC_PORT, RGBDIRECT_HSYNC_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_HSYNC_AF},
		{RGBDIRECT_VSYNC_PORT, RGBDIRECT_VSYNC_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_VSYNC_AF},
		{RGBDIRECT_DOTCLK_PORT, RGBDIRECT_DOTCLK_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_DOTCLK_AF},
		{RGBDIRECT_DE_PORT, RGBDIRECT_DE_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_DE_AF},

		{RGBDIRECT_R0_PORT, RGBDIRECT_R0_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_R0_AF},
		{RGBDIRECT_R1_PORT, RGBDIRECT_R1_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_R1_AF},
		{RGBDIRECT_R2_PORT, RGBDIRECT_R2_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_R2_AF},
		{RGBDIRECT_R3_PORT, RGBDIRECT_R3_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_R3_AF},
		{RGBDIRECT_R4_PORT, RGBDIRECT_R4_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_R4_AF},
		{RGBDIRECT_R5_PORT, RGBDIRECT_R5_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_R5_AF},
		{RGBDIRECT_R6_PORT, RGBDIRECT_R6_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_R6_AF},
		{RGBDIRECT_R7_PORT, RGBDIRECT_R7_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_R7_AF},

		{RGBDIRECT_G0_PORT, RGBDIRECT_G0_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_G0_AF},
		{RGBDIRECT_G1_PORT, RGBDIRECT_G1_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_G1_AF},
		{RGBDIRECT_G2_PORT, RGBDIRECT_G2_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_G2_AF},
		{RGBDIRECT_G3_PORT, RGBDIRECT_G3_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_G3_AF},
		{RGBDIRECT_G4_PORT, RGBDIRECT_G4_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_G4_AF},
		{RGBDIRECT_G5_PORT, RGBDIRECT_G5_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_G5_AF},
		{RGBDIRECT_G6_PORT, RGBDIRECT_G6_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_G6_AF},
		{RGBDIRECT_G7_PORT, RGBDIRECT_G7_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_G7_AF},

		{RGBDIRECT_B0_PORT, RGBDIRECT_B0_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_B0_AF},
		{RGBDIRECT_B1_PORT, RGBDIRECT_B1_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_B1_AF},
		{RGBDIRECT_B2_PORT, RGBDIRECT_B2_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_B2_AF},
		{RGBDIRECT_B3_PORT, RGBDIRECT_B3_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_B3_AF},
		{RGBDIRECT_B4_PORT, RGBDIRECT_B4_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_B4_AF},
		{RGBDIRECT_B5_PORT, RGBDIRECT_B5_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_B5_AF},
		{RGBDIRECT_B6_PORT, RGBDIRECT_B6_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_B6_AF},
		{RGBDIRECT_B7_PORT, RGBDIRECT_B7_PIN, HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, RGBDIRECT_B7_AF}
	};

	halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul LTDC.
///
void RGBDirect_Driver::ltdcInitialize() {

	static LTDC_HandleTypeDef ltdcHandler;
	LTDC_LayerCfgTypeDef layerCfg;
	RCC_PeriphCLKInitTypeDef clkInit;

	// Configura el rellotge
	// PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
	// PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz
	// PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz
	// LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_4 = 38.4/4 = 9.6Mhz
	//
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
	ltdcHandler.Init.HorizontalSync = RGBDIRECT_HSYNC - 1;
	ltdcHandler.Init.VerticalSync = RGBDIRECT_VSYNC - 1;
	ltdcHandler.Init.AccumulatedHBP = RGBDIRECT_HSYNC + RGBDIRECT_HBP - 1;
	ltdcHandler.Init.AccumulatedVBP = RGBDIRECT_VSYNC + RGBDIRECT_VBP - 1;
	ltdcHandler.Init.AccumulatedActiveH = RGBDIRECT_SCREEN_HEIGHT + RGBDIRECT_VSYNC + RGBDIRECT_VBP - 1;
	ltdcHandler.Init.AccumulatedActiveW = RGBDIRECT_SCREEN_WIDTH + RGBDIRECT_HSYNC + RGBDIRECT_HBP - 1;
	ltdcHandler.Init.TotalHeigh = RGBDIRECT_SCREEN_HEIGHT + RGBDIRECT_VSYNC + RGBDIRECT_VBP + RGBDIRECT_VFP - 1;
	ltdcHandler.Init.TotalWidth = RGBDIRECT_SCREEN_WIDTH + RGBDIRECT_HSYNC + RGBDIRECT_HBP + RGBDIRECT_HFP - 1;
	ltdcHandler.Init.Backcolor.Blue = 0;
	ltdcHandler.Init.Backcolor.Green = 0;
	ltdcHandler.Init.Backcolor.Red = 0;
	ltdcHandler.Instance = LTDC;

    // Configura la pagina
	//
	layerCfg.WindowX0 = 0;
	layerCfg.WindowX1 = 480;
	layerCfg.WindowY0 = 0;
	layerCfg.WindowY1 = 272;
	layerCfg.PixelFormat = LTDC_PIXEL_FORMAT;
	layerCfg.FBStartAdress = RGBDIRECT_VRAM;
	layerCfg.Alpha = 255;
	layerCfg.Alpha0 = 0;
	layerCfg.Backcolor.Blue = 0;
	layerCfg.Backcolor.Green = 0;
	layerCfg.Backcolor.Red = 0;
	layerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
	layerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
	layerCfg.ImageWidth  = RGBDIRECT_SCREEN_WIDTH;
	layerCfg.ImageHeight = RGBDIRECT_SCREEN_HEIGHT;

	__HAL_RCC_LTDC_CLK_ENABLE();
	HAL_LTDC_Init(&ltdcHandler);
	HAL_LTDC_ConfigLayer(&ltdcHandler, &layerCfg, 0);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul DMA2D.
///
void RGBDirect_Driver::dma2dInitialize() {

	__HAL_RCC_DMA2D_CLK_ENABLE();
}


/// ----------------------------------------------------------------------
/// \brief Ompla un area de memoria amb un color.
/// \param addr: Direccio de memoria.
/// \param width: Amplada del bloc.
/// \param height: Alçada del bloc.
/// \param color: El color per omplir.
///
void RGBDirect_Driver::dma2dFill(
	const uint8_t *addr,
	int16_t width,
	int16_t height,
	const Color &color) {

	DMA2D_HandleTypeDef dma2dHandle;

	// Configure the DMA2D Mode, Color Mode and output offset
	dma2dHandle.Init.Mode         = DMA2D_R2M;
	dma2dHandle.Init.ColorMode    = DMA2D_OUTPUT;
	dma2dHandle.Init.OutputOffset = IMAGE_WIDTH - width;

	// DMA2D Callbacks Configuration
	dma2dHandle.XferCpltCallback  = NULL;
	dma2dHandle.XferErrorCallback = NULL;

	// Foreground Configuration
	dma2dHandle.LayerCfg[curLayer].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	dma2dHandle.LayerCfg[curLayer].InputAlpha = 0xFF;
	dma2dHandle.LayerCfg[curLayer].InputColorMode = DMA2D_INPUT;
	dma2dHandle.LayerCfg[curLayer].InputOffset = 0x0;

	dma2dHandle.Instance = DMA2D;

	HAL_DMA2D_Init(&dma2dHandle);
	HAL_DMA2D_ConfigLayer(&dma2dHandle, 0);

	HAL_DMA2D_Start(&dma2dHandle, color.toARGB8888(), (uint32_t) addr, width, height);
	HAL_DMA2D_PollForTransfer(&dma2dHandle, 20);
}

