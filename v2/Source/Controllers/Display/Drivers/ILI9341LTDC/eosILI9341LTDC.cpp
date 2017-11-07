#include "eos.h"
#include "Controllers/Display/Drivers/eosILI9341LTDC.h"
#include "Controllers/Display/Drivers/eosILI9341Defs.h"
#include "HAL/halINT.h"
#include "hAL/halTMR.h"
#include "hAL/halGPIO.h"
#include "hAL/halSPI.h"

#include <string.h>

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_ltdc.h"


#if !defined(ILI9341LTDC_COLORMODE_565) && !defined(ILI9341LTDC_COLORMODE_666)
#error "No se especifico ILI9342_COLORMODE_xxx"
#endif


// Parametres de la pantalla
//
#define MAX_COLUMNS          240
#define MAX_ROWS             320
#define MAX_LAYERS           2
#define FRAME_BUFFER		 ILI9341LTDC_VRAM
#define FRAME_OFFSET		 (MAX_COLUMNS * MAX_ROWS * sizeof(uint16_t))

#define  ILI9341_HSYNC            ((uint32_t)9)   // Horizontal synchronization
#define  ILI9341_HBP              ((uint32_t)29)  // Horizontal back porch
#define  ILI9341_HFP              ((uint32_t)2)   // Horizontal front porch
#define  ILI9341_VSYNC            ((uint32_t)1)   // Vertical synchronization
#define  ILI9341_VBP              ((uint32_t)3)   // Vertical back porch
#define  ILI9341_VFP              ((uint32_t)2)   // Vertical front porch


// Codis d'operacio
//
#define OP_END        0
#define OP_DELAY      255


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
ILI9341LTDC_Driver::ILI9341LTDC_Driver() {

    screenWidth = MAX_COLUMNS;
    screenHeight = MAX_ROWS;
    buffer = (int8_t *) FRAME_BUFFER;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void ILI9341LTDC_Driver::initialize() {

#if defined(STM32F429I_DISC1)
    static uint8_t const lcdInit[] = {
        __SOFTWARE_RESET,
        OP_DELAY, 250,
        OP_DELAY, 250,
    	__POWER_CONTROL_B(0x00, 0xC1, 0x30),
		__POWER_ON_SEQUENCE_CONTROL(0x64, 0x03, 0x12, 0x81),
    	__DRIVER_TIMING_CONTROL_A(0x85, 0x00, 0x78),
		__POWER_CONTROL_A(0x39, 0x2C, 0x00, 0x34, 0x02),
		__PUMP_RATIO_CONTROL(0x20),
    	__DRIVER_TIMING_CONTROL_B(0x00, 0x00),
    	__FRAME_RATE_CONTROL_1(0x00, 0x18),
    	__POWER_CONTROL_1(0x23),
    	__POWER_CONTROL_2(0x10),
		__VCOM_CONTROL_1(0x3E, 0x28),
		__VCOM_CONTROL_2(0x86),
		__MEMORY_ACCESS_CONTROL(0x08 | MAC_MX_ON | MAC_MY_ON),
		__ENABLE_3G(0x00),
		__RGB_INTERFACE_SIGNAL_CONTROL(0xC2),

#if defined(ILI9341_COLORMODE_565)
    	//__PIXEL_FORMAT_SET(0x55),
#elif defined(ILI9341_COLORMODE_666)
        __PIXEL_FORMAT_SET(0x66),
#endif
		__DISPLAY_FUNCTION_CONTROL(0x0A, 0xA7, 0x27, 0x04),
		__COLUMN_ADDRESS_SET(0x00, 0x00, 0x00, 0xEF),
		__PAGE_ADDRESS_SET(0x00, 0x00, 0x01, 0x3F),
		__INTERFACE_CONTROL(0x01, 0x00, 0x06),
		__MEMORY_WRITE,
		OP_DELAY, 200,
		__GAMMA_SET(0x01),
		__POSITIVE_GAMMA_CORRECTION(0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
            0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00),
    	__NEGATIVE_GAMMA_CORRECTION(0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
            0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F),
        __SLEEP_OUT,
        OP_DELAY, 200,
        __DISPLAY_ON,
		__MEMORY_WRITE,
        OP_END
    };
#elif
#error "Display no soportado"
#endif

    // Inicialitzacio del controlador
    //
    displayInit();
	writeCommands(lcdInit);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el modul.
///
void ILI9341LTDC_Driver::shutdown() {

	displayOff();
}


/// ----------------------------------------------------------------------
/// \brief Selecciona la orientacio.
/// \param orientation: L'orientacio a seleccionar.
///
void ILI9341LTDC_Driver::setOrientation(
	DisplayOrientation orientation) {

}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
/// \param color: Color de borrat.
///
void ILI9341LTDC_Driver::clear(
	const Color &color) {

	uint16_t c = color.to565();
	uint16_t *p = (uint16_t*) buffer;
	for (int i = 0; i < screenWidth * screenHeight; i++)
		*p++ = c;
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param color: Color del pixel.
///
void ILI9341LTDC_Driver::setPixel(
	int16_t x,
	int16_t y,
	const Color &color) {

	*((uint16_t*)(buffer + (y * screenWidth + x) * sizeof(uint16_t))) = color.to565();
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels horitzontals.
/// \param x: Coordinada X.
/// \param y: Colordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void ILI9341LTDC_Driver::setHPixels(
	int16_t x,
	int16_t y,
	int16_t size,
	const Color &color) {

	while (size--)
		setPixel(x++, y, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels en vertical.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void ILI9341LTDC_Driver::setVPixels(
	int16_t x,
	int16_t y,
	int16_t size,
	const Color &color) {

	while (size--)
		setPixel(x, y++, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
/// \param color: Color dels pixels.
///
void ILI9341LTDC_Driver::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color &color) {

}


void ILI9341LTDC_Driver::writePixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color *colors) {

}


void ILI9341LTDC_Driver::readPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	Color *colors) {

}


void ILI9341LTDC_Driver::vScroll(
	int16_t delta,
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height) {

}


void ILI9341LTDC_Driver::hScroll(
	int16_t delta,
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height) {

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el display.
///
void ILI9341LTDC_Driver::displayInit() {

    ltdcInitialize();
	lcdInitialize();
	lcdReset();
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el display.
///
void ILI9341LTDC_Driver::displayOff() {

	lcdWriteCommand(CMD_DISPLAY_OFF);
}


/// ----------------------------------------------------------------------
/// \brief Escriu una sequencia de comandes en el controlador.
/// \param data: La sequencia de comandes.
///
void ILI9341LTDC_Driver::writeCommands(
	const uint8_t *data) {

    lcdOpen();

    uint8_t c;
    const uint8_t *p = data;
    while ((c = *p++) != OP_END) {
        switch (c) {
            case OP_DELAY:
                halTMRDelay(*p++);
                break;

            default:
                lcdWriteCommand(*p++);
                while (--c != 0)
                    lcdWriteData(*p++);
                break;
        }
    }
    lcdClose();
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza les comunicacions amb el driver.
///
void ILI9341LTDC_Driver::lcdInitialize() {

	static const GPIOInitializePinInfo gpioInit[] = {
#ifdef ILI9341LTDC_RST_PIN
		{ ILI9341LTDC_RST_PORT,    ILI9341LTDC_RST_PIN,
			HAL_GPIO_MODE_OUTPUT | HAL_GPIO_INIT_CLR, 0                  },
#endif
		{ ILI9341LTDC_CS_PORT,     ILI9341LTDC_CS_PIN,
			HAL_GPIO_MODE_OUTPUT | HAL_GPIO_INIT_SET, 0                  },
		{ ILI9341LTDC_RS_PORT,     ILI9341LTDC_RS_PIN,
			HAL_GPIO_MODE_OUTPUT | HAL_GPIO_INIT_CLR, 0                  },
		{ ILI9341LTDC_CLK_PORT,    ILI9341LTDC_CLK_PIN,
			HAL_GPIO_MODE_FUNCTION,                   ILI9341LTDC_CLK_AF },
		{ ILI9341LTDC_MISO_PORT,   ILI9341LTDC_MISO_PIN,
			HAL_GPIO_MODE_FUNCTION,                   ILI9341LTDC_MISO_AF},
		{ ILI9341LTDC_MOSI_PORT,   ILI9341LTDC_MOSI_PIN,
			HAL_GPIO_MODE_FUNCTION,                   ILI9341LTDC_MOSI_AF}
	};

	static const SPIInitializeInfo spiInit = {
		ILI9341_SPI_ID,
			HAL_SPI_MODE_0 | HAL_SPI_MS_MASTER | HAL_SPI_FIRSTBIT_MSB, HAL_SPI_CLOCKDIV_16, 0, 0
	};

	// Inicialitza modul GPIO
	//
	halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));

	// Inicialitza el modul SPI
	//
	halSPIInitialize(&spiInit);
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ILI9341LTDC_Driver::lcdReset() {

#ifdef ILI9341LTDC_RST_PORT
    halTMRDelay(10);
	halGPIOSetPin(ILI9341LTDC_RST_PORT, ILI9341LTDC_RST_PIN);
    halTMRDelay(120);
#endif

}

/// ----------------------------------------------------------------------
/// \brief Inicia la comunicacio amb el controlador.
///
void ILI9341LTDC_Driver::lcdOpen() {

	halGPIOClearPin(ILI9341LTDC_CS_PORT, ILI9341LTDC_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Finalitza la comunicacio amb el controlador.
///
void ILI9341LTDC_Driver::lcdClose() {

    halGPIOSetPin(ILI9341LTDC_CS_PORT, ILI9341LTDC_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda en el controlador
/// \param data: El byte de comanda.
///
void ILI9341LTDC_Driver::lcdWriteCommand(
	uint8_t d) {

	halGPIOClearPin(ILI9341LTDC_RS_PORT, ILI9341LTDC_RS_PIN);
	halSPISendBuffer(ILI9341LTDC_SPI_ID, &d, sizeof(d));
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades en el controlador
/// \param data: El byte de dades.
///
void ILI9341LTDC_Driver::lcdWriteData(
	uint8_t d) {

	halGPIOSetPin(ILI9341LTDC_RS_PORT, ILI9341LTDC_RS_PIN);
	halSPISendBuffer(ILI9341LTDC_SPI_ID, &d, sizeof(d));
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el control de la memoria d'imatge
///
LTDC_HandleTypeDef ltdcHandle;

void ILI9341LTDC_Driver::ltdcInitialize() {

	static const GPIOInitializePinInfo gpioInit[] = {
    	{ ILI9341LTDC_DE_PORT,     ILI9341LTDC_DE_PIN,
    		HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_DE_AF    },
		{ ILI9341LTDC_HSYNC_PORT,  ILI9341LTDC_HSYNC_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_HSYNC_AF },
		{ ILI9341LTDC_VSYNC_PORT,  ILI9341LTDC_VSYNC_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_VSYNC_AF },
		{ ILI9341LTDC_DOTCLK_PORT, ILI9341LTDC_DOTCLK_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_DOTCLK_AF},
		{ ILI9341LTDC_R2_PORT,     ILI9341LTDC_R2_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R2_AF    },
		{ ILI9341LTDC_R3_PORT,     ILI9341LTDC_R3_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R3_AF    },
		{ ILI9341LTDC_R4_PORT,     ILI9341LTDC_R4_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R4_AF    },
		{ ILI9341LTDC_R5_PORT,     ILI9341LTDC_R5_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R5_AF    },
		{ ILI9341LTDC_R6_PORT,     ILI9341LTDC_R6_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R6_AF    },
		{ ILI9341LTDC_R7_PORT,     ILI9341LTDC_R7_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R7_AF    },
		{ ILI9341LTDC_G2_PORT,     ILI9341LTDC_G2_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G2_AF    },
		{ ILI9341LTDC_G3_PORT,     ILI9341LTDC_G3_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G3_AF    },
		{ ILI9341LTDC_G4_PORT,     ILI9341LTDC_G4_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G4_AF    },
		{ ILI9341LTDC_G5_PORT,     ILI9341LTDC_G5_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G5_AF    },
		{ ILI9341LTDC_G6_PORT,     ILI9341LTDC_G6_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G6_AF    },
		{ ILI9341LTDC_G7_PORT,     ILI9341LTDC_G7_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G7_AF    },
		{ ILI9341LTDC_B2_PORT,     ILI9341LTDC_B2_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B2_AF    },
		{ ILI9341LTDC_B3_PORT,     ILI9341LTDC_B3_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B3_AF    },
		{ ILI9341LTDC_B4_PORT,     ILI9341LTDC_B4_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B4_AF    },
		{ ILI9341LTDC_B5_PORT,     ILI9341LTDC_B5_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B5_AF    },
		{ ILI9341LTDC_B6_PORT,     ILI9341LTDC_B6_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B6_AF    },
		{ ILI9341LTDC_B7_PORT,     ILI9341LTDC_B7_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B7_AF    },
	};

	// Inicialitza el modul GPIO
	//
	halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));

	// Inicialitza el modul LTDC
	//
	// Configure PLLSAI prescalers for LCD
	// Enable Pixel Clock
	// PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
	// PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAI_N = 192 Mhz
	// PLLLCDCLK = PLLSAI_VCO Output/PLLSAI_R = 192/4 = 96 Mhz
	// LTDC clock frequency = PLLLCDCLK / RCC_PLLSAIDivR = 96/4 = 24 Mhz

	RCC_PeriphCLKInitTypeDef clkInit;
    clkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    clkInit.PLLSAI.PLLSAIN = 192;
    clkInit.PLLSAI.PLLSAIR = 4;
    clkInit.PLLSAIDivR = RCC_PLLSAIDIVR_8;
    HAL_RCCEx_PeriphCLKConfig(&clkInit);

	ltdcHandle.Instance = LTDC;
	ltdcHandle.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	ltdcHandle.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	ltdcHandle.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	ltdcHandle.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	ltdcHandle.Init.Backcolor.Red = 0;
	ltdcHandle.Init.Backcolor.Green = 0;
	ltdcHandle.Init.Backcolor.Blue = 0;
    ltdcHandle.Init.HorizontalSync = ILI9341_HSYNC;
    ltdcHandle.Init.VerticalSync = ILI9341_VSYNC;
    ltdcHandle.Init.AccumulatedHBP = ILI9341_HBP;
    ltdcHandle.Init.AccumulatedVBP = ILI9341_VBP;
    ltdcHandle.Init.AccumulatedActiveW = 269;
    ltdcHandle.Init.AccumulatedActiveH = 323;
    ltdcHandle.Init.TotalWidth = 279;
    ltdcHandle.Init.TotalHeigh = 327;

    __LTDC_CLK_ENABLE();
	//__DMA2D_CLK_ENABLE();

	HAL_LTDC_Init(&ltdcHandle);

	// Inicialitza les capes
	//
	LTDC_LayerCfgTypeDef cfgLayer;
	cfgLayer.WindowX0 = 0;
	cfgLayer.WindowX1 = MAX_COLUMNS;
	cfgLayer.WindowY0 = 0;
	cfgLayer.WindowY1 = MAX_ROWS;
	cfgLayer.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
	cfgLayer.Alpha = 255;
	cfgLayer.Alpha0 = 0;
	cfgLayer.Backcolor.Blue = 0;
	cfgLayer.Backcolor.Green = 0;
	cfgLayer.Backcolor.Red = 0;
	cfgLayer.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
	cfgLayer.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
	cfgLayer.ImageWidth = MAX_COLUMNS;
	cfgLayer.ImageHeight = MAX_ROWS;

	for (int i = 0; i < MAX_LAYERS; i++) {
		cfgLayer.FBStartAdress = FRAME_BUFFER + (FRAME_OFFSET * i);
		HAL_LTDC_ConfigLayer(&ltdcHandle, &cfgLayer, i);
	}

	HAL_LTDC_EnableDither(&ltdcHandle);

	__HAL_LTDC_LAYER_ENABLE(&ltdcHandle, 0);
	__HAL_LTDC_RELOAD_CONFIG(&ltdcHandle);

	  HAL_NVIC_SetPriority(LTDC_IRQn, 0xE, 0);
	  HAL_NVIC_EnableIRQ(LTDC_IRQn);
}


void LTDC_IRQHandler(void) {

	HAL_LTDC_IRQHandler(&ltdcHandle);
}
