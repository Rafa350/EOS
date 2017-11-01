#include "eos.h"
#include "Controllers/Display/Drivers/eosILI9341LTDC.h"
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
#define FRAME_OFFSET		 (MAX_COLUMNS * MAX_ROWS * 2)

// Comandes del controlador
//
#define CMD_NOP                                            0x00
#define CMD_SOFTWARE_RESET                                 0x01
#define CMD_READ_DISPLAY_INFORMATION                       0x04
#define CMD_READ_DISPLAY_STATUS                            0x09
#define CMD_READ_DISPLAY_POWER_MODE                        0x0A
#define CMD_READ_DISPLAY_MADCTL                            0x0B
#define CMD_READ_DISPLAY_PIXEL_FORMAT                      0x0C
#define CMD_READ_DISPLAY_IMAGE_FORMAT                      0x0D
#define CMD_READ_DISPLAY_SINGLE_MODE                       0x0E
#define CMD_READ_DISPLAY_SELF_DIAGNOSTIC_RESULT            0x0F
#define CMD_ENTER_SLEEP_MODE                               0x10
#define CMD_SLEEP_OUT                                      0x11
#define CMD_PARTIAL_MODE_ON                                0x12
#define CMD_NORMAL_DISPLAY_MODE_ON                         0x13
#define CMD_DISPLAY_INVERSION_OFF                          0x20
#define CMD_DISPLAY_INVERSION_ON                           0x21
#define CMD_GAMMA_SET                                      0x26
#define CMD_DISPLAY_OFF                                    0x28
#define CMD_DISPLAY_ON                                     0x29
#define CMD_COLUMN_ADDRESS_SET                             0x2A
#define CMD_PAGE_ADDRESS_SET                               0x2B
#define CMD_MEMORY_WRITE                                   0x2C
#define CMD_COLOR_SET                                      0x2D
#define CMD_MEMORY_READ                                    0x2E
#define CMD_PARTIAL_AREA                                   0x30
#define CMD_VERTICAL_SCROLLING_DEFINITION                  0x33
#define CMD_TEARING_EFFECT_LINE_OFF                        0x34
#define CMD_TEARING_EFFECT_LINE_ON                         0x35
#define CMD_MEMORY_ACCESS_CONTROL                          0x36
#define CMD_VERTICAL_SCROLLING_START_ADDRESS               0x37
#define CMD_IDLE_MODE_OFF                                  0x38
#define CMD_IDLE_MODE_ON                                   0x39
#define CMD_PIXEL_FORMAT_SET                               0x3A
#define CMD_WRITE_MEMORY_CONTINUE                          0x3C
#define CMD_READ_MEMORY_CONTINUE                           0x3D
#define CMD_SET_TEAR_SCANLINE                              0x44
#define CMD_GET_SCANLINE                                   0x45
#define CMD_WRITE_DISPLAY_BRIGNESS                         0x51
#define CMD_READ_DISPLAY_BRIGNESS                          0x52
#define CMD_WRITE_CTRL_DISPLAY                             0x53
#define CMD_READ_CTRL_DISPLAY                              0x54
#define CMD_WRITE_CONTENT_ADAPTIVE_BRIGNESS_CONTROL        0x55
#define CMD_READ_CONTENT_ADAPTIVE_BRIGNESS_CONTROL         0x56
#define CMD_WRITE_CABC_MINIMUM_BRIGNESS                    0x5E
#define CMD_READ_CABC_MINIMUM_BRIGNESS                     0x5F
#define CMD_READ_ID1                                       0xDA
#define CMD_READ_ID2                                       0xDB
#define CMD_READ_ID3                                       0xDC
#define CMD_RGB_INTERFACE_SIGNAL_CONTROL                   0xB0
#define CMD_FRAME_RATE_CONTROL_1                           0xB1
#define CMD_FRAME_RATE_CONTROL_2                           0xB2
#define CMD_FRAME_RATE_CONTROL_3                           0xB3
#define CMD_DISPLAY_INVERSION_CONTROL                      0xB4
#define CMD_BLANKING_PORCH_CONTROL                         0xB5
#define CMD_DISPLAY_FUNCTION_CONTROL                       0xB6
#define CMD_ENTRY_MODE_SET                                 0xB7
#define CMD_BACKLIGHT_CONTROL_1                            0xB8
#define CMD_BACKLIGHT_CONTROL_2                            0xB9
#define CMD_BACKLIGHT_CONTROL_3                            0xBA
#define CMD_BACKLIGHT_CONTROL_4                            0xBB
#define CMD_BACKLIGHT_CONTROL_5                            0xBC
#define CMD_BACKLIGHT_CONTROL_7                            0xBE
#define CMD_BACKLIGHT_CONTROL_8                            0xBF
#define CMD_POWER_CONTROL_1                                0xC0
#define CMD_POWER_CONTROL_2                                0xC1
#define CMD_VCOM_CONTROL_1                                 0xC5
#define CMD_VCOM_CONTROL_2                                 0xC7
#define CMD_POWER_CONTROL_A                                0xCB
#define CMD_POWER_CONTROL_B                                0xCF
#define CMD_NV_MEMORY_WRITE                                0xD0
#define CMD_NV_MEMORY_PROTECTION_KEY                       0xD1
#define CMD_NV_MEMORY_STATUS_READ                          0xD2
#define CMD_READ_ID4                                       0xD3
#define CMD_POSITIVE_GAMMA_CORRECTION                      0xE0
#define CMD_NEGATIVE_GAMMA_CORRECTION                      0xE1
#define CMD_DIGITAL_GAMMA_CONTROL_1                        0xE2
#define CMD_DIGITAL_GAMMA_CONTROL_2                        0xE3
#define CMD_DRIVER_TIMING_CONTROL_A                        0xE8
#define CMD_DRIVER_TIMING_CONTROL_B                        0xEA
#define CMD_POWER_ON_SEQUENCE_CONTROL                      0xED
#define CMD_ENABLE_3G                                      0xF2
#define CMD_INTERFACE_CONTROL                              0xF6
#define CMD_PUMP_RATIO_CONTROL                             0xF7

// Parametres de la comanda MEMORY_ACCESS_CONTROL
//
#define MAC_MX_OFF    0b00000000
#define MAC_MX_ON     0b10000000
#define MAC_MY_OFF    0b00000000
#define MAC_MY_ON     0b01000000
#define MAC_MV_OFF    0b00000000
#define MAC_MV_ON     0b00100000

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
    static const uint8_t lcdInit[] = {
        1, CMD_SOFTWARE_RESET,
        OP_DELAY, 250,
        OP_DELAY, 250,
    	6, CMD_POWER_CONTROL_A, 0x39, 0x2C, 0x00, 0x34, 0x02,
    	4, CMD_POWER_CONTROL_B, 0x00, 0xC1, 0x30,
    	4, CMD_DRIVER_TIMING_CONTROL_A, 0x85, 0x00, 0x78,
    	3, CMD_DRIVER_TIMING_CONTROL_B, 0x00, 0x00, //
		5, CMD_POWER_ON_SEQUENCE_CONTROL, 0x64, 0x03, 0x12, 0x81,
		2, CMD_PUMP_RATIO_CONTROL, 0x20, //
    	2, CMD_POWER_CONTROL_1, 0x23,
    	2, CMD_POWER_CONTROL_2, 0x10,
		3, CMD_VCOM_CONTROL_1, 0x3E, 0x28,
		2, CMD_VCOM_CONTROL_2, 0x86,
    	2, CMD_MEMORY_ACCESS_CONTROL, 0x08 | MAC_MV_OFF | MAC_MX_ON | MAC_MY_OFF,
		// Interface VSYNC/HSYNC/DOTCLK/DE/RGB666
		2, CMD_RGB_INTERFACE_SIGNAL_CONTROL, 0xC2,
		4, CMD_INTERFACE_CONTROL, 0x01, 0x00, 0x06,
		// Format de video
#if defined(ILI9341_COLORMODE_565)
    	2, CMD_PIXEL_FORMAT_SET, 0x55,
#elif defined(ILI9341_COLORMODE_666)
        2, CMD_PIXEL_FORMAT_SET, 0x66,
#endif
    	3, CMD_FRAME_RATE_CONTROL_1, 0x00, 0x18,
		4, CMD_DISPLAY_FUNCTION_CONTROL, 0x08, 0x82, 0x27,
    	2, CMD_ENABLE_3G, 0x00,
    	2, CMD_GAMMA_SET, 0x01,
    	16, CMD_POSITIVE_GAMMA_CORRECTION, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
            0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
    	16, CMD_NEGATIVE_GAMMA_CORRECTION, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
            0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
        1, CMD_SLEEP_OUT,
        OP_DELAY, 150,
        1, CMD_DISPLAY_ON,
        OP_DELAY, 50,
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

    memset((void*) buffer, 0x55, FRAME_OFFSET);
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

	*((uint32_t*)(buffer + (y * screenWidth + x) * 4)) = color.to565();
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
		{ ILI9341LTDC_RST_PORT,    ILI9341LTDC_TSR_PIN,    HAL_GPIO_MODE_OUTPUT,   0                  },
#endif
		{ ILI9341LTDC_CS_PORT,     ILI9341LTDC_CS_PIN,     HAL_GPIO_MODE_OUTPUT,   0                  },
		{ ILI9341LTDC_RS_PORT,     ILI9341LTDC_RS_PIN,     HAL_GPIO_MODE_OUTPUT,   0                  },
		{ ILI9341LTDC_CLK_PORT,    ILI9341LTDC_CLK_PIN,    HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_CLK_AF },
		{ ILI9341LTDC_MISO_PORT,   ILI9341LTDC_MISO_PIN,   HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_MISO_AF},
		{ ILI9341LTDC_MOSI_PORT,   ILI9341LTDC_MOSI_PIN,   HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_MOSI_AF}
	};

	// Inicialitza modul GPIO
	//
	halGPIOSetPin(ILI9341LTDC_CS_PORT, ILI9341LTDC_CS_PIN);
#ifdef ILI9341LTDC_RST_PIN
	halGPIOClearPin(ILI9341LTDC_RST_PORT, ILI9341LTDC_RST_PIN);
#endif
	halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));

	// Inicialitza el modul SPI
	//
	SPIInitializeInfo info;
	info.module = ILI9341_SPI_MODULE;
	info.options = HAL_SPI_MODE_0 | HAL_SPI_MS_MASTER | HAL_SPI_FIRSTBIT_MSB;
	halSPIInitialize(&info);
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
	halSPITransmit(ILI9341LTDC_SPI_MODULE, d);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades en el controlador
/// \param data: El byte de dades.
///
void ILI9341LTDC_Driver::lcdWriteData(
	uint8_t d) {

	halGPIOSetPin(ILI9341LTDC_RS_PORT, ILI9341LTDC_RS_PIN);
	halSPITransmit(ILI9341LTDC_SPI_MODULE, d);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el control de la memoria d'imatge
///
void ILI9341LTDC_Driver::ltdcInitialize() {

	static const GPIOInitializePinInfo gpioInit[] = {
    	{ ILI9341LTDC_DE_PORT,     ILI9341LTDC_DE_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_DE_AF    },
		{ ILI9341LTDC_HSYNC_PORT,  ILI9341LTDC_HSYNC_PIN,  HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_HSYNC_AF },
		{ ILI9341LTDC_VSYNC_PORT,  ILI9341LTDC_VSYNC_PIN,  HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_VSYNC_AF },
		{ ILI9341LTDC_DOTCLK_PORT, ILI9341LTDC_DOTCLK_PIN, HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_DOTCLK_AF},
		{ ILI9341LTDC_R2_PORT,     ILI9341LTDC_R2_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R2_AF    },
		{ ILI9341LTDC_R3_PORT,     ILI9341LTDC_R3_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R3_AF    },
		{ ILI9341LTDC_R4_PORT,     ILI9341LTDC_R4_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R4_AF    },
		{ ILI9341LTDC_R5_PORT,     ILI9341LTDC_R5_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R5_AF    },
		{ ILI9341LTDC_R6_PORT,     ILI9341LTDC_R6_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R6_AF    },
		{ ILI9341LTDC_R7_PORT,     ILI9341LTDC_R7_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_R7_AF    },
		{ ILI9341LTDC_G2_PORT,     ILI9341LTDC_G2_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G2_AF    },
		{ ILI9341LTDC_G3_PORT,     ILI9341LTDC_G3_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G3_AF    },
		{ ILI9341LTDC_G4_PORT,     ILI9341LTDC_G4_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G4_AF    },
		{ ILI9341LTDC_G5_PORT,     ILI9341LTDC_G5_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G5_AF    },
		{ ILI9341LTDC_G6_PORT,     ILI9341LTDC_G6_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G6_AF    },
		{ ILI9341LTDC_G7_PORT,     ILI9341LTDC_G7_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_G7_AF    },
		{ ILI9341LTDC_B2_PORT,     ILI9341LTDC_B2_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B2_AF    },
		{ ILI9341LTDC_B3_PORT,     ILI9341LTDC_B3_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B3_AF    },
		{ ILI9341LTDC_B4_PORT,     ILI9341LTDC_B4_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B4_AF    },
		{ ILI9341LTDC_B5_PORT,     ILI9341LTDC_B5_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B5_AF    },
		{ ILI9341LTDC_B6_PORT,     ILI9341LTDC_B6_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B6_AF    },
		{ ILI9341LTDC_B7_PORT,     ILI9341LTDC_B7_PIN,     HAL_GPIO_MODE_FUNCTION, ILI9341LTDC_B7_AF    },
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

	LTDC_HandleTypeDef ltdcHandle;
	ltdcHandle.Instance = LTDC;
	ltdcHandle.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	ltdcHandle.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	ltdcHandle.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	ltdcHandle.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	ltdcHandle.Init.Backcolor.Red = 0;
	ltdcHandle.Init.Backcolor.Green = 0;
	ltdcHandle.Init.Backcolor.Blue = 0;
    ltdcHandle.Init.HorizontalSync = 9;
    ltdcHandle.Init.VerticalSync = 1;
    ltdcHandle.Init.AccumulatedHBP = 29;
    ltdcHandle.Init.AccumulatedVBP = 3;
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
	cfgLayer.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
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
}

