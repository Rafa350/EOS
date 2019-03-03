#include "eos.h"
#ifdef USE_DISPLAY_ILI9341_LTDC

#include "Controllers/Display/Drivers/eosILI9341LTDC.h"
#include "Controllers/Display/Drivers/eosILI9341Defs.h"
#include "HAL/halINT.h"
#include "hAL/halTMR.h"
#include "hAL/halGPIO.h"
#include "hAL/halSPI.h"

#include "string.h"

#include "stm32f4xx_hal.h"


// Format de pixel
//
#if defined(DISPLAY_COLOR_RGB565)
#define PIXEL_VALUE(c)       c.toRGB565()
#else
#error No se especifico DISPLAY_COLOR_xxxx
#endif


// Codis d'operacio
//
#define OP_END        0
#define OP_DELAY      255


/// ----------------------------------------------------------------------
/// \brief Obte el valor minim
/// \param a: Primer valor
/// \param b: Segin valor
/// \return El minim dels valors a i b.
///
static inline int min(
	int a,
	int b) {

	return a <= b ? a : b;
}


/// ----------------------------------------------------------------------
/// \brief Obte el valor absolut.
/// \param a: El valor
/// \return El seu valor absolut.
///
static inline int abs(
	int a) {

	return a < 0 ? -a : a;
}


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


IDisplayDriver *ILI9341LTDCDriver::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief Obte una instancia unica del driver.
/// \return La instancia del driver.
///
IDisplayDriver *ILI9341LTDCDriver::getInstance() {

	if (instance == nullptr)
		instance = new ILI9341LTDCDriver();
	return instance;
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
ILI9341LTDCDriver::ILI9341LTDCDriver():

	screenWidth(DISPLAY_SCREEN_WIDTH),
	screenHeight(DISPLAY_SCREEN_HEIGHT),
	sin(0),
	cos(1),
	dx(0),
	dy(0) {

    frameAddr = DISPLAY_VRAM;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void ILI9341LTDCDriver::initialize() {

    displayInit();
    displayOn();
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el modul.
///
void ILI9341LTDCDriver::shutdown() {

	displayOff();
}


/// ----------------------------------------------------------------------
/// \brief Selecciona la orientacio.
/// \param orientation: L'orientacio a seleccionar.
///
void ILI9341LTDCDriver::setOrientation(
	DisplayOrientation orientation) {

	switch (orientation) {
		case DisplayOrientation::normal:
			screenWidth = DISPLAY_SCREEN_WIDTH;
			screenHeight = DISPLAY_SCREEN_HEIGHT;
			sin = 0;
			cos = 1;
			dx = 0;
			dy = 0;
			break;

		case DisplayOrientation::rotate90:
			screenWidth = DISPLAY_SCREEN_HEIGHT;
			screenHeight = DISPLAY_SCREEN_WIDTH;
			sin = 1;
			cos = 0;
			dx = DISPLAY_SCREEN_WIDTH - 1;
			dy = 0;
			break;

		case DisplayOrientation::rotate180:
			screenWidth = DISPLAY_SCREEN_WIDTH;
			screenHeight = DISPLAY_SCREEN_HEIGHT;
			sin = 0;
			cos = -1;
			dx = DISPLAY_SCREEN_WIDTH - 1;
			dy = DISPLAY_SCREEN_HEIGHT - 1;
			break;

		case DisplayOrientation::rotate270:
			screenWidth = DISPLAY_SCREEN_HEIGHT;
			screenHeight = DISPLAY_SCREEN_WIDTH;
			sin = -1;
			cos = 0;
			dx = 0;
			dy = DISPLAY_SCREEN_HEIGHT - 1;
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
/// \param color: Color de borrat.
///
void ILI9341LTDCDriver::clear(
	const Color &color) {

	dma2dFill(0, 0, DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param color: Color del pixel.
/// \remarks Si esta fora de limits no dibuixa res.
///
void ILI9341LTDCDriver::setPixel(
	int x,
	int y,
	const Color &color) {

	// Comprova que estigui d'ins de l'area de visualitzacio
	//
	if ((x >= 0) && (x < screenWidth) && (y >= 0) && (y < screenHeight)) {

		// Rotacio
		//
		int xx = dx + (x * cos) - (y * sin);
		int yy = dy + (x * sin) + (y * cos);

		// Dibuixa el pixel
		//
		*((PIXEL_TYPE*) addressAt(frameAddr, xx, yy)) = PIXEL_VALUE(color);
	}
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels horitzontals.
/// \param x: Coordinada X.
/// \param y: Colordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
/// \remarks Si esta fora de limits no dibuixa res.
///
void ILI9341LTDCDriver::setHPixels(
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
/// \remarks Si esta fora de limits no dibuixa res.
///
void ILI9341LTDCDriver::setVPixels(
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
void ILI9341LTDCDriver::setPixels(
	int x,
	int y,
	int width,
	int height,
	const Color &color) {

	// El tamany ha de ser mes gran que zero per dibuixar un rectangle
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

			int xx = min(xx1, xx2);
			int yy = min(yy1, yy2);
			int ww = abs(xx2 - xx1) + 1;
			int hh = abs(yy2 - yy1) + 1;

			dma2dFill(xx, yy, ww, hh, color);
		}
	}
}


void ILI9341LTDCDriver::writePixels(
	int x,
	int y,
	int width,
	int height,
	const uint8_t *pixels,
	PixelFormat format,
	int dx,
	int dy,
	int pitch) {

}


void ILI9341LTDCDriver::readPixels(
	int x,
	int y,
	int width,
	int height,
	uint8_t *pixels,
	PixelFormat format,
	int dx,
	int dy,
	int pitch) {

}


void ILI9341LTDCDriver::vScroll(
	int delta,
	int x,
	int y,
	int width,
	int height) {

}


void ILI9341LTDCDriver::hScroll(
	int delta,
	int x,
	int y,
	int width,
	int height) {

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el display.
///
void ILI9341LTDCDriver::displayInit() {

#if defined(STM32F429I_DISC1)
    static const uint8_t lcdInit[] = {
        __SOFTWARE_RESET,
        OP_DELAY, 250,
        OP_DELAY, 250,
		__PUMP_RATIO_CONTROL(0x20),
		__POWER_CONTROL_A(0x39, 0x2C, 0x00, 0x34, 0x02),
    	__POWER_CONTROL_B(0x00, 0xC1, 0x30),
		__POWER_ON_SEQUENCE_CONTROL(0x64, 0x03, 0x12, 0x81),
    	__POWER_CONTROL_1(0x23),
    	__POWER_CONTROL_2(0x10),
    	__FRAME_RATE_CONTROL_1(0x00, 0x18),
    	__DRIVER_TIMING_CONTROL_A(0x85, 0x00, 0x78),
    	__DRIVER_TIMING_CONTROL_B(0x00, 0x00),
		__VCOM_CONTROL_1(0x3E, 0x28),
		__VCOM_CONTROL_2(0x86),
		__ENABLE_3G(0x00),
		__MEMORY_ACCESS_CONTROL(0x08 | MAC_MX_ON | MAC_MY_ON),
		__RGB_INTERFACE_SIGNAL_CONTROL(0xC2),
		__DISPLAY_FUNCTION_CONTROL(0x0A, 0xA7, 0x27, 0x04),
		__INTERFACE_CONTROL(0x01, 0x00, 0x06),
		OP_DELAY, 200,
		__GAMMA_SET(0x01),
		__POSITIVE_GAMMA_CORRECTION(0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
            0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00),
    	__NEGATIVE_GAMMA_CORRECTION(0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
            0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F),
        OP_END
    };

#elif
#error "Display no soportado"
#endif

    // Inicialitza la pantalla
    //
	lcdInitialize();
	lcdReset();
	writeCommands(lcdInit);

	// Inicialitza el controlador de video, dma, etc
	//
	ltdcInitialize();
	dma2dInitialize();
}


/// ----------------------------------------------------------------------
/// \brief Activa el display
///
void ILI9341LTDCDriver::displayOn() {

	lcdOpen();
	lcdWriteCommand(CMD_SLEEP_OUT);
	halTMRDelay(120);
	lcdWriteCommand(CMD_DISPLAY_ON);
	lcdClose();
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el display.
///
void ILI9341LTDCDriver::displayOff() {

	lcdOpen();
	lcdWriteCommand(CMD_DISPLAY_OFF);
	lcdWriteCommand(CMD_ENTER_SLEEP_MODE);
	halTMRDelay(120);
	lcdClose();
}


/// ----------------------------------------------------------------------
/// \brief Escriu una sequencia de comandes en el controlador.
/// \param data: La sequencia de comandes.
///
void ILI9341LTDCDriver::writeCommands(
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
void ILI9341LTDCDriver::lcdInitialize() {

	static const GPIOInitializePinInfo gpioInit[] = {
#ifdef DISPLAY_RST_PIN
		{ DISPLAY_RST_PORT,    DISPLAY_RST_PIN,
			HAL_GPIO_MODE_OUTPUT | HAL_GPIO_INIT_CLR, 0            },
#endif
		{ DISPLAY_CS_PORT,     DISPLAY_CS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_SET, 0         },
		{ DISPLAY_RS_PORT,     DISPLAY_RS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, 0         },
		{ DISPLAY_CLK_PORT,    DISPLAY_CLK_PIN,
			HAL_GPIO_MODE_ALT_PP,                   DISPLAY_CLK_AF },
#ifdef DISPLAY_MISO_PORT
		{ DISPLAY_MISO_PORT,   DISPLAY_MISO_PIN,
			HAL_GPIO_MODE_ALT_PP,                   DISPLAY_MISO_AF},
#endif
		{ DISPLAY_MOSI_PORT,   DISPLAY_MOSI_PIN,
			HAL_GPIO_MODE_ALT_PP,                   DISPLAY_MOSI_AF}
	};

	static const SPIInitializeInfo spiInit = {
		DISPLAY_SPI_ID,
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
void ILI9341LTDCDriver::lcdReset() {

#ifdef DISPLAY_RST_PORT
    halTMRDelay(10);
	halGPIOSetPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN);
    halTMRDelay(120);
#endif

}

/// ----------------------------------------------------------------------
/// \brief Inicia la comunicacio amb el controlador.
///
void ILI9341LTDCDriver::lcdOpen() {

	halGPIOClearPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Finalitza la comunicacio amb el controlador.
///
void ILI9341LTDCDriver::lcdClose() {

    halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda en el controlador
/// \param data: El byte de comanda.
///
void ILI9341LTDCDriver::lcdWriteCommand(
	uint8_t d) {

	halGPIOClearPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
	halSPISendBuffer(DISPLAY_SPI_ID, &d, sizeof(d));
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades en el controlador
/// \param data: El byte de dades.
///
void ILI9341LTDCDriver::lcdWriteData(
	uint8_t d) {

	halGPIOSetPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
	halSPISendBuffer(DISPLAY_SPI_ID, &d, sizeof(d));
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el controlador de video
///
void ILI9341LTDCDriver::ltdcInitialize() {

    uint32_t tmp;

    static const GPIOInitializePinInfo gpioInit[] = {
    	{ DISPLAY_DE_PORT,     DISPLAY_DE_PIN,
    		HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_DE_AF    },
		{ DISPLAY_HSYNC_PORT,  DISPLAY_HSYNC_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_HSYNC_AF },
		{ DISPLAY_VSYNC_PORT,  DISPLAY_VSYNC_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_VSYNC_AF },
		{ DISPLAY_DOTCLK_PORT, DISPLAY_DOTCLK_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_DOTCLK_AF},
		{ DISPLAY_R2_PORT,     DISPLAY_R2_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R2_AF    },
		{ DISPLAY_R3_PORT,     DISPLAY_R3_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R3_AF    },
		{ DISPLAY_R4_PORT,     DISPLAY_R4_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R4_AF    },
		{ DISPLAY_R5_PORT,     DISPLAY_R5_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R5_AF    },
		{ DISPLAY_R6_PORT,     DISPLAY_R6_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R6_AF    },
		{ DISPLAY_R7_PORT,     DISPLAY_R7_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_R7_AF    },
		{ DISPLAY_G2_PORT,     DISPLAY_G2_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G2_AF    },
		{ DISPLAY_G3_PORT,     DISPLAY_G3_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G3_AF    },
		{ DISPLAY_G4_PORT,     DISPLAY_G4_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G4_AF    },
		{ DISPLAY_G5_PORT,     DISPLAY_G5_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G5_AF    },
		{ DISPLAY_G6_PORT,     DISPLAY_G6_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G6_AF    },
		{ DISPLAY_G7_PORT,     DISPLAY_G7_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_G7_AF    },
		{ DISPLAY_B2_PORT,     DISPLAY_B2_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B2_AF    },
		{ DISPLAY_B3_PORT,     DISPLAY_B3_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B3_AF    },
		{ DISPLAY_B4_PORT,     DISPLAY_B4_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B4_AF    },
		{ DISPLAY_B5_PORT,     DISPLAY_B5_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B5_AF    },
		{ DISPLAY_B6_PORT,     DISPLAY_B6_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B6_AF    },
		{ DISPLAY_B7_PORT,     DISPLAY_B7_PIN,
			HAL_GPIO_SPEED_FAST | HAL_GPIO_MODE_ALT_PP, DISPLAY_B7_AF    },
	};

	// Inicialitza el modul GPIO
	//
	halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));

	// Inicialitza rellotge del modul LTDC
	// -Configure PLLSAI prescalers for LCD
	// -Enable Pixel Clock
	// -PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
	// -PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAI_N = 192 Mhz
	// -PLLLCDCLK = PLLSAI_VCO Output/PLLSAI_R = 192/4 = 96 Mhz
	// -LTDC clock frequency = PLLLCDCLK / RCC_PLLSAIDivR = 96/4 = 24 Mhz
	//
	RCC_PeriphCLKInitTypeDef clkInit;
    clkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    clkInit.PLLSAI.PLLSAIN = 192;
    clkInit.PLLSAI.PLLSAIR = 4;
    clkInit.PLLSAIDivR = RCC_PLLSAIDIVR_8;
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
    tmp |= (DISPLAY_HSYNC + DISPLAY_HBP + DISPLAY_SCREEN_WIDTH - 1) << LTDC_AWCR_AAW_Pos;
    tmp |= (DISPLAY_VSYNC + DISPLAY_VBP + DISPLAY_SCREEN_HEIGHT - 1) << LTDC_AWCR_AAH_Pos;
    LTDC->AWCR = tmp;

    // Configura el registre TWCR (Total Width Configuration Register)
    // -TOTALW = HSYNC + HBP + WIDTH + HFP - 1
    // -TOTALH = VSYNC + VBP + HEIGHT + VFP - 1
    //
    tmp = LTDC->TWCR;
    tmp &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
    tmp |= (DISPLAY_HSYNC + DISPLAY_HBP + DISPLAY_SCREEN_WIDTH + DISPLAY_HFP - 1) << LTDC_TWCR_TOTALW_Pos;
    tmp |= (DISPLAY_VSYNC + DISPLAY_VBP + DISPLAY_SCREEN_HEIGHT + DISPLAY_VFP - 1) << LTDC_TWCR_TOTALH_Pos;
    LTDC->TWCR = tmp;

    // Configura el registre BCCR (Back Color Configuration Register)
    //
    tmp = LTDC->BCCR;
    tmp &= ~(LTDC_BCCR_BCRED | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCBLUE);
    tmp |= 0 << LTDC_BCCR_BCRED_Pos;
    tmp |= 0 << LTDC_BCCR_BCGREEN_Pos;
    tmp |= 255 << LTDC_BCCR_BCBLUE_Pos;
    LTDC->BCCR = tmp;

    // Configura la Layer-1 WHPCR (Window Horizontal Position Configuration Register)
    // -Tamany horitzontal de la finestra
    //
    tmp = LTDC_Layer1->WHPCR;
    tmp &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
    tmp |= ((DISPLAY_HSYNC + DISPLAY_HBP - 1) + 1) << LTDC_LxWHPCR_WHSTPOS_Pos;
    tmp |= ((DISPLAY_HSYNC + DISPLAY_HBP - 1) + DISPLAY_SCREEN_WIDTH) << LTDC_LxWHPCR_WHSPPOS_Pos;
    LTDC_Layer1->WHPCR = tmp;

    // Configura L1_WHPCR (Window Vertical Position Configuration Register)
    // -Tamany vertical de la finestra
    //
    tmp = LTDC_Layer1->WVPCR;
    tmp &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
    tmp |= ((DISPLAY_VSYNC + DISPLAY_VBP - 1) + 1) << LTDC_LxWVPCR_WVSTPOS_Pos;
    tmp |= ((DISPLAY_VSYNC + DISPLAY_VBP - 1) + DISPLAY_SCREEN_HEIGHT) << LTDC_LxWVPCR_WVSPPOS_Pos;
    LTDC_Layer1->WVPCR = tmp;

    // Configura L1_DCCR (Default Color Configuration Register)
    // -Color per defecte ARGB(255, 0, 0, 0)
    //
    LTDC_Layer1->DCCR = 0xFF0000FF;

    // Configura L1_PFCR (Pixel Format Configuration Register)
    //
    tmp = LTDC_Layer1->PFCR;
    tmp &= ~(LTDC_LxPFCR_PF);
#if defined(DISPLAY_COLOR_RGB565)
    tmp |= 0b010 << LTDC_LxPFCR_PF_Pos;
#elif defined(DISPLAY_COLOR_RGB888)
    tmp |= 0b001 << LTDC_LxPFCR_PF_Pos;
#else
#error No se especifico DISPLAY_COLOR_xxxx
#endif
    LTDC_Layer1->PFCR = tmp;

    // Configura L1_CACR (Constant Alpha Configuration Register)
    //
    tmp = LTDC_Layer1->CACR;
    tmp &= ~(LTDC_LxCACR_CONSTA);
    tmp |= 255u;
    LTDC_Layer1->CACR;

    // Configura L1_BFCR
    // -Specifies the blending factors
    //
    tmp = LTDC_Layer1->BFCR;
    tmp &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
    tmp |= 6 << LTDC_LxBFCR_BF1_Pos;
    tmp |= 7 << LTDC_LxBFCR_BF2_Pos;
    LTDC_Layer1->BFCR = tmp;

    // Configura L1_CFBAR (Color Frame Buffer Address Register)
    // -Adressa del buffer de video
    //
    LTDC_Layer1->CFBAR = frameAddr;

    // Configura L1_CFBLR (Color Frame Buffer Length Register)
    // -Longitut de la linia en bytes.
    //
    tmp = LTDC_Layer1->CFBLR;
    tmp &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
    tmp |= LINE_SIZE << LTDC_LxCFBLR_CFBP_Pos;
    tmp |= ((DISPLAY_SCREEN_WIDTH * PIXEL_SIZE) + 3) << LTDC_LxCFBLR_CFBLL_Pos;
    LTDC_Layer1->CFBLR = tmp;

    // Configura L1_CFBLNR (Color Frame Buffer Line Number Register)
    //
    tmp = LTDC_Layer1->CFBLNR;
    tmp  &= ~(LTDC_LxCFBLNR_CFBLNBR);
    tmp |= DISPLAY_SCREEN_HEIGHT;
    LTDC_Layer1->CFBLNR = tmp;

    // Activa la capa
    //
    LTDC_Layer1->CR |= (uint32_t) LTDC_LxCR_LEN;
    LTDC->SRCR |= LTDC_SRCR_IMR;

    // Activa el controlador
    //
    LTDC->GCR |= LTDC_GCR_LTDCEN;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el controlador DMA
///
void ILI9341LTDCDriver::dma2dInitialize() {

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
void ILI9341LTDCDriver::dma2dFill(
	int x,
	int y,
	int width,
	int height,
	const Color &color) {

	// Calcula l'adresa inicial
	//
	int addr = addressAt(frameAddr, x, y);

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
/// \brief Espera que acabi la transaccio.
///
void ILI9341LTDCDriver::dma2dWaitFinish() {

	// Espera que acabi la transferencia
	//
	while ((DMA2D->ISR & DMA2D_ISR_TCIF_Msk) == 0) {

		// Si troba errors, finalitza
		//
		volatile uint32_t isr = DMA2D->ISR;
		if (((isr & DMA2D_ISR_CEIF_Msk) != 0) || ((isr & DMA2D_ISR_TEIF_Msk) != 0)) {
			DMA2D->IFCR |=
					1 << DMA2D_IFCR_CCEIF_Pos |
					1 << DMA2D_IFCR_CTEIF_Pos;
			return;
		}
	}
	DMA2D->IFCR |= 1 << DMA2D_IFCR_CTCIF_Pos;
}


#endif // USE_DISPLAY_ILI9341_LTDC
