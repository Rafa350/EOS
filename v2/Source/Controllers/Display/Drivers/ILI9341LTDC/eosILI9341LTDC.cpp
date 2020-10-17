#include "eos.h"

#ifdef DISPLAY_DRV_ILI9341LTDC

#include "Controllers/Display/Drivers/eosILI9341LTDC.h"
#include "Controllers/Display/Drivers/eosILI9341Defs.h"
#include "Controllers/Display/eosFrameBuffer_RGB565_DMA2D.h"
#include "HAL/halINT.h"
#include "hAL/halTMR.h"
#include "hAL/halGPIO.h"
#include "HAL/halSPI.h"
#include "HAL/STM32/halDMA2D.h"
#include "System/eosMath.h"


// Codis d'operacio
//
#define OP_END        0
#define OP_DELAY      255


using namespace eos;


static SPIData spiData;
static SPIHandler hSpi;


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
ILI9341LTDCDriver::ILI9341LTDCDriver() {

	frameBuffer = new RGB565_DMA2D_FrameBuffer(
		DISPLAY_SCREEN_WIDTH,
		DISPLAY_SCREEN_HEIGHT,
		DisplayOrientation::normal,
		(uint8_t*) DISPLAY_VRAM_ADDR,
		LINE_SIZE);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void ILI9341LTDCDriver::initialize() {

    displayInit();

    // Inicialitza el dispositiu LTDC
    //
    initializeLTDC();
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

	frameBuffer->setOrientation(orientation);
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
/// \param color: Color de borrat.
///
void ILI9341LTDCDriver::clear(
	const Color &color) {

	frameBuffer->clear(color);
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

	frameBuffer->setPixel(x, y, color);
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

	frameBuffer->setPixels(x, y, size, 1, color);
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

	frameBuffer->setPixels(x, y, 1, size, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Al�ada de la regio.
/// \param color: Color dels pixels.
///
void ILI9341LTDCDriver::setPixels(
	int x,
	int y,
	int width,
	int height,
	const Color &color) {

	frameBuffer->setPixels(x, y, width, height, color);
}


void ILI9341LTDCDriver::writePixels(
	int x,
	int y,
	int width,
	int height,
	const uint8_t *pixels,
	ColorFormat format,
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
	ColorFormat format,
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


void ILI9341LTDCDriver::refresh() {

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
			HAL_GPIO_MODE_OUTPUT | HAL_GPIO_INIT_CLR, 0 },
#endif
		{ DISPLAY_CS_PORT,     DISPLAY_CS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_SPEED_FAST | HAL_GPIO_INIT_SET, 0 },
		{ DISPLAY_RS_PORT,     DISPLAY_RS_PIN,
			HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_SPEED_FAST | HAL_GPIO_INIT_CLR, 0 },
		{ DISPLAY_CLK_PORT,    DISPLAY_CLK_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_CLK_AF },
#ifdef DISPLAY_MISO_PORT
		{ DISPLAY_MISO_PORT,   DISPLAY_MISO_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_MISO_AF},
#endif
		{ DISPLAY_MOSI_PORT,   DISPLAY_MOSI_PIN,
			HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_FAST, DISPLAY_MOSI_AF}
	};

	static const SPIInitializeInfo spiInit = {
		DISPLAY_SPI_ID,
			HAL_SPI_MODE_0 | HAL_SPI_MS_MASTER | HAL_SPI_FIRSTBIT_MSB | HAL_SPI_CLOCKDIV_16, 0, 0
	};

	// Inicialitza modul GPIO
	//
	halGPIOInitializePins(gpioInit, sizeof(gpioInit) / sizeof(gpioInit[0]));

	// Inicialitza el modul SPI
	//
	hSpi = halSPIInitialize(&spiData, &spiInit);
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
/// \param cmd: El byte de comanda.
///
void ILI9341LTDCDriver::lcdWriteCommand(
	uint8_t cmd) {

	halGPIOClearPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
	halSPISendBuffer(hSpi, &cmd, sizeof(cmd));
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades en el controlador
/// \param data: El byte de dades.
///
void ILI9341LTDCDriver::lcdWriteData(
	uint8_t data) {

	halGPIOSetPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
	halSPISendBuffer(hSpi, &data, sizeof(data));
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el controlador de video
///
void ILI9341LTDCDriver::initializeLTDC() {

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
    LTDC_Layer1->CFBAR = DISPLAY_VRAM_ADDR;

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


#endif // USE_DISPLAY_ILI9341_LTDC
