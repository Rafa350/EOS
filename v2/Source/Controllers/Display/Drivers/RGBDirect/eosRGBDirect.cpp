#include "Controllers/Display/Drivers/eosRGBDirect.h"
#include "HAL/halGPIO.h"


#if !defined(STM32F4) && !defined(STM32F7)
#error Hardware no soportado
#endif


#if defined(STM32F4)
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_ltdc.h"
#include "stm32f4xx_hal_dma2d.h"
#elif defined(STM32F7)
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_ltdc.h"
#include "stm32f7xx_hal_dma2d.h"
#endif


// Format de pixel
//
#if defined(RGBDIRECT_COLORMODE_565)
#define PIXEL_TYPE           uint16_t
#define PIXEL_FORMAT         LTDC_PIXEL_FORMAT_RGB565;
#endif

// Format de la imatge+
//
#define IMAGE_WIDTH          ((int32_t)RGBDIRECT_SCREEN_WIDTH)
#define IMAGE_HEIGHT         ((int32_t)RGBDIRECT_SCREEN_HEIGHT)
#define IMAGE_PAGES          ((int32_t)1)
#define IMAGE_SIZE           ((int32_t)(RGBDIRECT_SCREEN_WIDTH * RGBDIRECT_SCREEN_HEIGHT * IMAGE_PAGES * sizeof(PIXEL_TYPE)))
#define IMAGE_BUFFER		 RGBDIRECT_VRAM

#define  FREQUENCY_DIVIDER    5


using namespace eos;


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


void RGBDirect_Driver::clear(
	const Color &color) {

	dma2dFill(image, IMAGE_WIDTH, IMAGE_HEIGHT, color);
}


void RGBDirect_Driver::setPixel(
	int16_t x,
	int16_t y,
	const Color &color) {

}


void RGBDirect_Driver::setHPixels(
	int16_t x,
	int16_t y,
	int16_t size,
	const Color &color) {

}


void RGBDirect_Driver::setVPixels(
	int16_t x,
	int16_t y,
	int16_t size,
	const Color &color) {

}


void RGBDirect_Driver::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color &color) {

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
		{RGBDIRECT_BKE_PORT, RGBDIRECT_BKE_PIN, HAL_GPIO_MODE_OUTPUT_PP, 0 }
	};

	halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));

	  GPIO_InitTypeDef GPIO_Init_Structure;

	  /* Enable GPIOs clock */
	  __HAL_RCC_GPIOE_CLK_ENABLE();
	  __HAL_RCC_GPIOG_CLK_ENABLE();
	  __HAL_RCC_GPIOI_CLK_ENABLE();
	  __HAL_RCC_GPIOJ_CLK_ENABLE();
	  __HAL_RCC_GPIOK_CLK_ENABLE();

	  /*** LTDC Pins configuration ***/
	  /* GPIOE configuration */
	  GPIO_Init_Structure.Pin       = GPIO_PIN_4;
	  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
	  GPIO_Init_Structure.Pull      = GPIO_NOPULL;
	  GPIO_Init_Structure.Speed     = GPIO_SPEED_FAST;
	  GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;
	  HAL_GPIO_Init(GPIOE, &GPIO_Init_Structure);

	  /* GPIOG configuration */
	  GPIO_Init_Structure.Pin       = GPIO_PIN_12;
	  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
	  GPIO_Init_Structure.Alternate = GPIO_AF9_LTDC;
	  HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure);

	  /* GPIOI LTDC alternate configuration */
	  GPIO_Init_Structure.Pin       = GPIO_PIN_9 | GPIO_PIN_10 | \
	                                  GPIO_PIN_14 | GPIO_PIN_15;
	  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
	  GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;
	  HAL_GPIO_Init(GPIOI, &GPIO_Init_Structure);

	  /* GPIOJ configuration */
	  GPIO_Init_Structure.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
	                                  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | \
	                                  GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | \
	                                  GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
	  GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;
	  HAL_GPIO_Init(GPIOJ, &GPIO_Init_Structure);

	  /* GPIOK configuration */
	  GPIO_Init_Structure.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | \
	                                  GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
	  GPIO_Init_Structure.Alternate = GPIO_AF14_LTDC;
	  HAL_GPIO_Init(GPIOK, &GPIO_Init_Structure);

	  /* LCD_DISP GPIO configuration */
	  GPIO_Init_Structure.Pin       = GPIO_PIN_12;     /* LCD_DISP pin has to be manually controlled */
	  GPIO_Init_Structure.Mode      = GPIO_MODE_OUTPUT_PP;
	  HAL_GPIO_Init(GPIOI, &GPIO_Init_Structure);

	  /* LCD_BL_CTRL GPIO configuration */
	  GPIO_Init_Structure.Pin       = GPIO_PIN_3;  /* LCD_BL_CTRL pin has to be manually controlled */
	  GPIO_Init_Structure.Mode      = GPIO_MODE_OUTPUT_PP;
	  HAL_GPIO_Init(GPIOK, &GPIO_Init_Structure);

	  /* Assert display enable LCD_DISP pin */
	  //HAL_GPIO_WritePin(LCD_DISP_GPIO_PORT, LCD_DISP_PIN, GPIO_PIN_SET);

	  /* Assert backlight LCD_BL_CTRL pin */
	  //HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_PORT, LCD_BL_CTRL_PIN, GPIO_PIN_SET);
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
	layerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
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
	HAL_LTDC_ConfigLayer(&ltdcHandler, &layerCfg, 1);
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
	dma2dHandle.Init.ColorMode    = DMA2D_OUTPUT_RGB565;
	dma2dHandle.Init.OutputOffset = IMAGE_WIDTH - width;

	// DMA2D Callbacks Configuration
	dma2dHandle.XferCpltCallback  = NULL;
	dma2dHandle.XferErrorCallback = NULL;

	// Foreground Configuration
	dma2dHandle.LayerCfg[curLayer].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	dma2dHandle.LayerCfg[curLayer].InputAlpha = 0xFF;
	dma2dHandle.LayerCfg[curLayer].InputColorMode = DMA2D_INPUT_RGB565;
	dma2dHandle.LayerCfg[curLayer].InputOffset = 0x0;

	dma2dHandle.Instance = DMA2D;

	HAL_DMA2D_Init(&dma2dHandle);
	HAL_DMA2D_ConfigLayer(&dma2dHandle, 0);

	HAL_DMA2D_Start(&dma2dHandle, color.toARGB8888(), (uint32_t) addr, width, height);
	HAL_DMA2D_PollForTransfer(&dma2dHandle, 20);
}

