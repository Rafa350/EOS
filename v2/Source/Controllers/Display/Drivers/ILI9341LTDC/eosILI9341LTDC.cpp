#include "eos.h"
#include "Controllers/Display/Drivers/eosILI9341LTDC.h"
#include "hAL/halTMR.h"
#include "hAL/halGPIO.h"
#include "hAL/halSPI.h"

#include "stm32f4xx.h"
#include "stm32f4xx_ltdc.h"
#include "stm32f4xx_rcc.h"


// Parametres de la pantalla
//
#define MAX_COLUMNS          240
#define MAX_ROWS             320


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
ILI9341LTDC_Driver::ILI9341LTDC_Driver() {

    screenWidth = MAX_COLUMNS;
    screenHeight = MAX_ROWS;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void ILI9341LTDC_Driver::initialize() {

	static GPIOInitializeInfo gpioInit[] = {
	    { ILI9341LTDC_HSYNC_PORT,  ILI9341LTDC_HSYNC_PIN,  HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_HSYNC_PORT,  ILI9341LTDC_HSYNC_PIN,  HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_VSYNC_PORT,  ILI9341LTDC_VSYNC_PIN,  HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_DOTCLK_PORT, ILI9341LTDC_DOTCLK_PIN, HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_R2_PORT,     ILI9341LTDC_R2_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_R3_PORT,     ILI9341LTDC_R3_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_R4_PORT,     ILI9341LTDC_R4_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_R5_PORT,     ILI9341LTDC_R5_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_R6_PORT,     ILI9341LTDC_R6_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_R7_PORT,     ILI9341LTDC_R7_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_G2_PORT,     ILI9341LTDC_G2_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_G3_PORT,     ILI9341LTDC_G3_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_G4_PORT,     ILI9341LTDC_G4_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_G5_PORT,     ILI9341LTDC_G5_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_G6_PORT,     ILI9341LTDC_G6_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_G7_PORT,     ILI9341LTDC_G7_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_B2_PORT,     ILI9341LTDC_B2_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_B3_PORT,     ILI9341LTDC_B3_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_B4_PORT,     ILI9341LTDC_B4_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_B5_PORT,     ILI9341LTDC_B5_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_B6_PORT,     ILI9341LTDC_B6_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
		{ ILI9341LTDC_B7_PORT,     ILI9341LTDC_B7_PIN,     HAL_GPIO_MODE_ALTERNATE, HAL_GPIO_AF_LTDC       },
#ifdef ILI9341LTDC_RST_PIN
		{ ILI9341LTDC_RST_PORT,    ILI9341LTDC_TSR_PIN,    HAL_GPIO_MODE_OUTPUT,    0                      },
#endif
		{ ILI9341LTDC_CS_PORT,     ILI9341LTDC_CS_PIN,     HAL_GPIO_MODE_OUTPUT,    0                      },
		{ ILI9341LTDC_RS_PORT,     ILI9341LTDC_RS_PIN,     HAL_GPIO_MODE_OUTPUT,    0                      },
		{ ILI9341LTDC_CLK_PORT,    ILI9341LTDC_CLK_PIN,    HAL_GPIO_MODE_ALTERNATE, ILI9341LTDC_GPIO_AF_SPI},
		{ ILI9341LTDC_MISO_PORT,   ILI9341LTDC_MISO_PIN,   HAL_GPIO_MODE_ALTERNATE, ILI9341LTDC_GPIO_AF_SPI},
		{ ILI9341LTDC_MOSI_PORT,   ILI9341LTDC_MOSI_PIN,   HAL_GPIO_MODE_ALTERNATE, ILI9341LTDC_GPIO_AF_SPI}
	};

	// Inicialitza el modul GPIO
	//
	halGPIOInitialize(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));
	halGPIOSetPin(ILI9341LTDC_CS_PORT, ILI9341LTDC_CS_PIN);
#ifdef ILI9341LTDC_RST_PIN
	halGPIOClearPin(ILI9341LTDC_RST_PORT, ILI9341LTDC_RST_PIN);
#endif

	// Inicialitza el modul SPI
	//
    halSPIInitialize(ILI9341LTDC_SPI_MODULE, HAL_SPI_MODE_0 | HAL_SPI_MS_MASTER | HAL_SPI_FIRSTBIT_MSB);

	// Inicialitza el modul LDTC
	//
	RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;

	LTDC_InitTypeDef ltdcInit;
	ltdcInit.LTDC_HSPolarity = LTDC_HSPolarity_AL;
	ltdcInit.LTDC_VSPolarity = LTDC_VSPolarity_AL;
	ltdcInit.LTDC_DEPolarity = LTDC_DEPolarity_AL;
	ltdcInit.LTDC_PCPolarity = LTDC_PCPolarity_IPC;
	ltdcInit.LTDC_BackgroundRedValue = 0;
	ltdcInit.LTDC_BackgroundGreenValue = 0;
	ltdcInit.LTDC_BackgroundBlueValue = 0;
    ltdcInit.LTDC_HorizontalSync = 9;
    ltdcInit.LTDC_VerticalSync = 1;
    ltdcInit.LTDC_AccumulatedHBP = 29;
    ltdcInit.LTDC_AccumulatedVBP = 3;
    ltdcInit.LTDC_AccumulatedActiveW = 269;
    ltdcInit.LTDC_AccumulatedActiveH = 323;
    ltdcInit.LTDC_TotalWidth = 279;
    ltdcInit.LTDC_TotalHeigh = 327;

	/* Configure PLLSAI prescalers for LCD */
	/* Enable Pixel Clock */
	/* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
	/* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAI_N = 192 Mhz */
	/* PLLLCDCLK = PLLSAI_VCO Output/PLLSAI_R = 192/4 = 96 Mhz */
	/* LTDC clock frequency = PLLLCDCLK / RCC_PLLSAIDivR = 96/4 = 24 Mhz */
	RCC_PLLSAIConfig(192, 7, 4);
	RCC_LTDCCLKDivConfig(RCC_PLLSAIDivR_Div4);

	/* Enable PLLSAI Clock */
    RCC_PLLSAICmd(ENABLE);

    /* Wait for PLLSAI activation */
	while (RCC_GetFlagStatus(RCC_FLAG_PLLSAIRDY) == RESET) {
	}

	LTDC_Init(&ltdcInit);

	// Inicialitza les capes
	//
	LTDC_Layer_InitTypeDef layerInit;
	/* 	Windowing configuration */
	/* 	Horizontal start = horizontal synchronization + Horizontal back porch = 43
		Vertical start   = vertical synchronization + vertical back porch     = 12
		Horizontal stop = Horizontal start + LCD_PIXEL_WIDTH - 1
		Vertical stop   = Vertical start + LCD_PIXEL_HEIGHT - 1
	*/
	layerInit.LTDC_HorizontalStart = 30;
	layerInit.LTDC_HorizontalStop = 269;
	layerInit.LTDC_VerticalStart = 4;
	layerInit.LTDC_VerticalStop = 323;

	/* Pixel Format configuration*/
	layerInit.LTDC_PixelFormat = LTDC_Pixelformat_RGB565;
    /* Alpha constant (255 totally opaque) */
	layerInit.LTDC_ConstantAlpha = 255;
    /* Default Color configuration (configure A,R,G,B component values) */
	layerInit.LTDC_DefaultColorBlue = 0;
	layerInit.LTDC_DefaultColorGreen = 0;
	layerInit.LTDC_DefaultColorRed = 0;
	layerInit.LTDC_DefaultColorAlpha = 0;

    /* Configure blending factors */
	layerInit.LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_CA;
	layerInit.LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_CA;

    /* the length of one line of pixels in bytes + 3 then :
    Line Lenth = Active high width x number of bytes per pixel + 3
    Active high width         = LCD_PIXEL_WIDTH
    number of bytes per pixel = 2    (pixel_format : RGB565)
    */
	layerInit.LTDC_CFBLineLength = 240 * 2 + 3;

	/* the pitch is the increment from the start of one line of pixels to the
    start of the next line in bytes, then :
    Pitch = Active high width x number of bytes per pixel
    */
	layerInit.LTDC_CFBPitch = 240 * 2;
	/* Configure the number of lines */
	layerInit.LTDC_CFBLineNumber = 320;

	/* Start Address configuration : the LCD Frame buffer is defined on SDRAM */
	layerInit.LTDC_CFBStartAdress = ILI9341_FRAME_BUFFER;
	/* Initialize Layer 1 */
	LTDC_LayerInit(LTDC_Layer1, &layerInit);

    /* Configure Layer2 */
    /* Start Address configuration : the LCD Frame buffer is defined on SDRAM w/ Offset */
	layerInit.LTDC_CFBStartAdress = ILI9341_FRAME_BUFFER + ILI9341_FRAME_OFFSET;

	/* Configure blending factors */
	layerInit.LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_PAxCA;
	layerInit.LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_PAxCA;
	/* Initialize Layer 2 */
	LTDC_LayerInit(LTDC_Layer2, &layerInit);



	LTDC_Cmd(ENABLE);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el modul.
///
void ILI9341LTDC_Driver::shutdown() {

	LTDC_Cmd(DISABLE);
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
/// \param color: Color de borrat.
///
void ILI9341LTDC_Driver::clear(
	Color color) {

}


void ILI9341LTDC_Driver::setPixel(
	int16_t x,
	int16_t y,
	Color color) {

}


/// ----------------------------------------------------------------------
/// \brief Inicia la comunicacio amb el controlador.
///
void ILI9341LTDC_Driver::ioBegin() {

	halGPIOSetPin(ILI9341LTDC_CS_PORT, ILI9341LTDC_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Finalitza la comunicacio amb el controlador.
///
void ILI9341LTDC_Driver::ioEnd() {

	halGPIOClearPin(ILI9341LTDC_CS_PORT, ILI9341LTDC_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda en el controlador
/// \param data: El byte de comanda.
///
void ILI9341LTDC_Driver::ioWriteCommand(
	uint8_t d) {

	halGPIOClearPin(ILI9341LTDC_RS_PORT, ILI9341LTDC_RS_PIN);
	halSPISend(ILI9341LTDC_SPI_MODULE, d);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades en el controlador
/// \param data: El byte de dades.
///
void ILI9341LTDC_Driver::ioWriteData(
	uint8_t d) {

	halGPIOSetPin(ILI9341LTDC_RS_PORT, ILI9341LTDC_RS_PIN);
	halSPISend(ILI9341LTDC_SPI_MODULE, d);
}

