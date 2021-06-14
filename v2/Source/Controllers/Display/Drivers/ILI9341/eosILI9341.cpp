#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/eosILI9341.h"
#include "Controllers/Display/Drivers/eosILI9341Defs.h"
#include "HAL/halTMR.h"


#if !defined(DISPLAY_ER_TFT028_4) && \
    !defined(STM32F429I_DISC1)
#error "No se especifico DISPLAY_xxx"
#endif


// Codis d'operacio
//
#define OP_END        0
#define OP_DELAY      255


using namespace eos;


IDisplayDriver *ILI9341Driver::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief Obte una instancia unica del driver.
/// \return La instancia del driver.
///
IDisplayDriver *ILI9341Driver::getInstance() {

	if (instance == nullptr)
		instance = new ILI9341Driver();
	return instance;
}


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
ILI9341Driver::ILI9341Driver():

	screenWidth(DISPLAY_SCREEN_WIDTH),
	screenHeight(DISPLAY_SCREEN_HEIGHT) {
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la pantalla.
///
void ILI9341Driver::initialize() {

#if defined(DISPLAY_ER_TFT028_4)
    static const uint8_t initData[] = {
        __SOFTWARE_RESET,
        OP_DELAY, 250,
        OP_DELAY, 250,
        6, CMD_POWER_CONTROL_A, 0x39, 0x2C, 0x00, 0x34, 0x02,
        4, CMD_POWER_CONTROL_B, 0x00, 0xC3, 0x30,
     	5, CMD_POWER_ON_SEQUENCE_CONTROL, 0x64, 0x03, 0X12, 0x81,
        6, CMD_POWER_CONTROL_A, 0x39, 0x2C, 0x00, 0x34, 0x02,
        2, CMD_PUMP_RATIO_CONTROL, 0x20,
        3, CMD_DRIVER_TIMING_CONTROL_B, 0x00, 0x00,
       	2, CMD_POWER_CONTROL_1, 0x22,
        2, CMD_POWER_CONTROL_2, 0x11,
        3, CMD_VCOM_CONTROL_1, 0x3D, 0x20,
        2, CMD_VCOM_CONTROL_2, 0xAA,
        2, CMD_MEMORY_ACCESS_CONTROL, 0x08 | MAC_MV_OFF | MAC_MX_OFF | MAC_MY_OFF,
#if defined(DISPLAY_COLOR_RGB565)
        2, CMD_PIXEL_FORMAT_SET, 0x55,
#elif defined(DISPLAY_COLOR_RGB666)
        2, CMD_PIXEL_FORMAT_SET, 0x66,
#endif
        3, CMD_FRAME_RATE_CONTROL_1, 0x00, 0x13,
        3, CMD_DISPLAY_FUNCTION_CONTROL, 0x0A, 0xA2,
        3, CMD_INTERFACE_CONTROL, 0x01, 0x30,
        2, CMD_ENABLE_3G, 0x00,
        2, CMD_GAMMA_SET, 0x01,
        16, CMD_POSITIVE_GAMMA_CORRECTION, 0x0F, 0x3F, 0x2F, 0x0C, 0x10, 0x0A,
            0x53, 0xD5, 0x40, 0x0A, 0x13, 0x03, 0x08, 0x03, 0x00,
        16, CMD_NEGATIVE_GAMMA_CORRECTION, 0x00, 0x00, 0x10, 0x03, 0x0F, 0x05,
            0x2C, 0xA2, 0x3F, 0x05, 0x0E, 0x0C, 0x37, 0x3C, 0x0F,
        OP_END
    };

#elif defined(STM32F429I_DISC1)
    static const uint8_t initData[] = {
        __SOFTWARE_RESET,
        OP_DELAY, 250,
        OP_DELAY, 250,
		__POWER_CONTROL_A(0x39, 0x2C, 0x00, 0x34, 0x62),
    	__POWER_CONTROL_B(0x00, 0xC1, 0x30),
    	__DRIVER_TIMING_CONTROL_A(0x85, 0x00, 0x78),
    	__DRIVER_TIMING_CONTROL_B(0x00, 0x00),
		__POWER_ON_SEQUENCE_CONTROL(0x64, 0x03, 0x12, 0x81),
		__PUMP_RATIO_CONTROL(0x20),
    	__POWER_CONTROL_1(0x23),
    	__POWER_CONTROL_2(0x10),
		__VCOM_CONTROL_1(0x3E, 0x28),
		__VCOM_CONTROL_2(0x86),
    	__MEMORY_ACCESS_CONTROL(0x08 | MAC_MV_OFF | MAC_MX_ON | MAC_MY_OFF),
#if defined(DISPLAY_COLOR_RGB565)
		__PIXEL_FORMAT_SET(0x55),
#elif defined(DISPLAY_COLOR_RGB666)
        __PIXEL_FORMAT_SET(0x66),
#endif
		__FRAME_RATE_CONTROL_1(0x00, 0x18),
		__DISPLAY_FUNCTION_CONTROL(0x08, 0x82, 0x27, 0x00),
		__ENABLE_3G(0x00),
		__GAMMA_SET(0x01),
    	__POSITIVE_GAMMA_CORRECTION( 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
    			0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00),
    	__NEGATIVE_GAMMA_CORRECTION(0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
    			0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F),
        OP_END
    };
#endif

    // Inicialitzacio del controlador
    //
    displayInit();
    writeCommands(initData);
    displayOn();
}


/// ----------------------------------------------------------------------
/// \brief Desativa la pantalla
///
void ILI9341Driver::shutdown() {

    displayOff();
}


/// ----------------------------------------------------------------------
/// \brief Selecciona l'orientacio de la pantalla.
/// \param orientation: Orientacio (0=0, 1=90, 2=180, 3=270)
///
void ILI9341Driver::setOrientation(
    DisplayOrientation orientation) {

#if defined(DISPLAY_ER_TFT028_4)
    static const uint8_t orientationData[4][4] = {
   		{__MEMORY_ACCESS_CONTROL(0x08 | MAC_MV_OFF | MAC_MX_OFF | MAC_MY_OFF), OP_END},
		{__MEMORY_ACCESS_CONTROL(0x08 | MAC_MV_ON | MAC_MX_ON | MAC_MY_OFF), OP_END},
		{__MEMORY_ACCESS_CONTROL(0x08 | MAC_MV_OFF | MAC_MX_ON | MAC_MY_ON), OP_END},
		{__MEMORY_ACCESS_CONTROL(0x08 | MAC_MV_ON | MAC_MX_OFF | MAC_MY_ON), OP_END}
    };

#elif defined(STM32F429I_DISC1)
    static const uint8_t orientationData[4][4] = {
   		{__MEMORY_ACCESS_CONTROL(0x08 | MAC_MV_OFF | MAC_MX_OFF | MAC_MY_ON), OP_END},
		{__MEMORY_ACCESS_CONTROL(0x08 | MAC_MV_ON | MAC_MX_OFF | MAC_MY_OFF), OP_END},
		{__MEMORY_ACCESS_CONTROL(0x08 | MAC_MV_OFF | MAC_MX_ON | MAC_MY_OFF), OP_END},
		{__MEMORY_ACCESS_CONTROL(0x08 | MAC_MV_ON | MAC_MX_ON | MAC_MY_ON), OP_END}
    };
#endif

    switch (orientation) {
        case DisplayOrientation::normal:
            screenWidth = DISPLAY_SCREEN_WIDTH;
            screenHeight = DISPLAY_SCREEN_HEIGHT;
            writeCommands(orientationData[0]);
            break;

        case DisplayOrientation::rotate90:
            screenWidth = DISPLAY_SCREEN_HEIGHT;
            screenHeight = DISPLAY_SCREEN_WIDTH;
            writeCommands(orientationData[1]);
            break;

        case DisplayOrientation::rotate180:
            screenWidth = DISPLAY_SCREEN_WIDTH;
            screenHeight = DISPLAY_SCREEN_HEIGHT;
            writeCommands(orientationData[2]);
            break;

        case DisplayOrientation::rotate270:
            screenWidth = DISPLAY_SCREEN_HEIGHT;
            screenHeight = DISPLAY_SCREEN_WIDTH;
            writeCommands(orientationData[3]);
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla
/// \param color: Color per borrar
///
void ILI9341Driver::clear(
    const Color &color) {

    selectRegion(0, 0, screenWidth, screenHeight);
    writeRegion(color, screenWidth * screenHeight);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param color: Color del pixel.
///
void ILI9341Driver::setPixel(
    int x,
    int y,
    const Color &color) {

    selectRegion(x, y, 1, 1);
    writeRegion(color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels horitzontals.
/// \param x: Coordinada X.
/// \param y: Colordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void ILI9341Driver::setHPixels(
    int x,
    int y,
    int length,
    const Color &color) {

    selectRegion(x, y, length, 1);
    writeRegion(color, length);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels en vertical.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void ILI9341Driver::setVPixels(
    int x,
    int y,
    int length,
    const Color &color) {

    selectRegion(x, y, 1, length);
    writeRegion(color, length);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Al�ada de la regio.
/// \param color: Color dels pixels.
///
void ILI9341Driver::setPixels(
    int x,
    int y,
    int width,
    int height,
    const Color &color) {

    selectRegion(x, y, width, height);
    writeRegion(color, width * height);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Al�ada de la regio.
/// \param colors: Color dels pixels.
///
void ILI9341Driver::writePixels(
    int x,
    int y,
    int width,
    int height,
    const uint8_t *pixels,
	ColorFormat format,
	int dx,
	int xy,
	int pitch) {

    //selectRegion(x, y, width, width);
    //writeRegion(colors, width * height);
}


/// ----------------------------------------------------------------------
/// \brief Llegeix una regio rectangular de pixels. No hi ha cap tipus de
///        comprovacio de la validesa dels parametres.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Al�ada de la regio.
/// \params colors: Buffer on deixar els pixels.
///
void ILI9341Driver::readPixels(
    int x,
    int y,
    int width,
    int height,
    uint8_t *pixels,
	ColorFormat format,
	int dx,
	int dy,
	int pitch) {

    //selectRegion(x, y, width, height);
    //readRegion(colors, width * height);
}


/// ----------------------------------------------------------------------
/// \brief Realitza un scroll vertical de la pantalla.
/// \param delta: Numero de lineas a despla�ar. El signe indica la direccio.
/// \param x: Posicio x de la regio.
/// \param y: Posicio y de la regio.
/// \param width: Amplada de la regio.
/// \param height: Al�ada de la regio.
///
void ILI9341Driver::vScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

    static Color buffer[DISPLAY_SCREEN_WIDTH];

    if (delta > 0) {

        for (int i = y; i < height - y - delta; i++) {

            selectRegion(x, i + delta, width, 1);
            readRegion(buffer, width);

            selectRegion(x, i, width, 1);
            writeRegion(buffer, width);
        }
    }

    else if (delta < 0) {

    }
}


/// ----------------------------------------------------------------------
/// \brief Realitza un scroll horitzontal de la pantalla.
/// \param delta: Numero de lineas a despla�ar. El signe indica la direccio.
/// \param delta: Numero de lineas a despla�ar. El signe indica la direccio.
/// \param x: Posicio x de la regio.
/// \param y: Posicio y de la regio.
/// \param width: Amplada de la regio.
/// \param height: Al�ada de la regio.
///
void ILI9341Driver::hScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

}


/// ----------------------------------------------------------------------
/// \brief Refresca la imatge de la pantalla.
///
void ILI9341Driver::refresh() {

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el controlador del display.
///
void ILI9341Driver::displayInit() {

    lcdInitialize();
    lcdReset();
}


/// ----------------------------------------------------------------------
/// \brief Activa el display
///
void ILI9341Driver::displayOn() {

	lcdOpen();
	lcdWriteCommand(CMD_SLEEP_OUT);
	halTMRDelay(120);
	lcdWriteCommand(CMD_DISPLAY_ON);
	lcdClose();
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el display.
///
void ILI9341Driver::displayOff() {

	lcdOpen();
	lcdWriteCommand(CMD_DISPLAY_OFF);
	lcdWriteCommand(CMD_ENTER_SLEEP_MODE);
	halTMRDelay(120);
	lcdClose();
}


/// ----------------------------------------------------------------------
// \brief Envia una sequencia programada.
// \param data: Programa a enviar
//
void ILI9341Driver::writeCommands(
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
/// \brief Selecciona la regio de treball per les transferencies de
///        pixels.
/// \param x: Coordinada X origen.
/// \param y: Coordinada Y oriden.
/// \param width: Amplada de la regio.
/// \param height: Al�ada de la regio.
///
void ILI9341Driver::selectRegion(
    int x,
    int y,
    int width,
    int height) {

	uint8_t buffer[4];

    int x2 = x + width - 1;
    int y2 = y + height - 1;

    lcdOpen();

    lcdWriteCommand(CMD_COLUMN_ADDRESS_SET);

    buffer[0] = x >> 8;
    buffer[1] = x;
    buffer[2] = x2 >> 8;
    buffer[3] = x2;
	lcdWriteData(buffer, sizeof(buffer));

	lcdWriteCommand(CMD_PAGE_ADDRESS_SET);

	buffer[0] = y >> 8;
    buffer[1] = y;
    buffer[2] = y2 >> 8;
    buffer[3] = y2;
	lcdWriteData(buffer, sizeof(buffer));

    lcdClose();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un color en la regio seleccionada. Cas particular d'una
///		   regio de 1x1 pixel.
/// \param data: El color.
///
void ILI9341Driver::writeRegion(
	const Color &color) {

#if defined(DISPLAY_COLOR_RGB565)

    uint16_t c = color.toRGB565();
    uint8_t cc[sizeof(uint16_t)];
 	cc[0] = c >> 8;
   	cc[1] = c;

    lcdOpen();
    lcdWriteCommand(CMD_MEMORY_WRITE);
    lcdWriteData(cc, sizeof(cc));
    lcdClose();

#elif defined(DISPLAY_COLOR_RGB666)

    uint32_t c = color.c;
    uint8_t cc[3];
    cc[0] = (uint32_t)(c & 0x00FC0000) >> 16;
    cc[1] = (uint32_t)(c & 0x0000FC00) >> 8;
    cc[2] = (uint32_t)(c & 0x000000FC);

    lcdOpen();
    lcdWriteCommand(CMD_MEMORY_WRITE);
    lcdWriteData(cc, sizeof(cc));
    lcdClose();

#endif
}


/// ----------------------------------------------------------------------
/// \brief Escriu un color en el controlador.
/// \param data: El color.
/// \param count: Numero de copies a escriure.
///
void ILI9341Driver::writeRegion(
    const Color &color,
    int count) {

#if defined(DISPLAY_COLOR_RGB565)

	static uint8_t cc_buffer[sizeof(uint16_t) * DISPLAY_SCREEN_WIDTH] __attribute__ ((aligned (__BIGGEST_ALIGNMENT__)));
	static uint16_t _c;
    static int16_t _ccCapacity = 0;

	uint8_t* cc = (uint8_t*) cc_buffer;  // Fer-ho aixi si no no va
    uint16_t c = color.toRGB565();
	int16_t ccCapacity = count < (int32_t)(sizeof(cc) / sizeof(cc[0])) ? count : (int32_t)(sizeof(cc) / sizeof(cc[0]));
	if (c != _c || _ccCapacity < ccCapacity) {
		for (int16_t i = 0; i < ccCapacity; i++) {
			cc[i + i + 0] = c >> 8;
			cc[i + i + 1] = c;
		}
		_c = c;
		_ccCapacity = ccCapacity;
	}

    lcdOpen();
    lcdWriteCommand(CMD_MEMORY_WRITE);
    while (count) {
    	int16_t  n = ccCapacity;
    	if (count < n)
    		n = count;
        lcdWriteData(cc, (int16_t) sizeof(uint16_t) * n);
        count -= n;
    }
    lcdClose();

#elif defined(DISPLAY_COLOR_RGB666)

    uint32_t c = color.c;
    uint8_t cc[3];
    cc[0] = (uint32_t)(c & 0x00FC0000) >> 16;
    cc[1] = (uint32_t)(c & 0x0000FC00) >> 8;
    cc[2] = (uint32_t)(c & 0x000000FC);

    lcdOpen();
    lcdWriteCommand(CMD_MEMORY_WRITE);
    while (count--)
        lcdWriteData(cc, sizeof(cc));
    lcdClose();

#endif
}


/// ----------------------------------------------------------------------
/// \brief Escriu una llista de colors en el controlador
/// \param colors: Llista de colors.
/// \param count: Numero d'elements en la llista.
///
void ILI9341Driver::writeRegion(
    const Color *colors,
    int count) {

    while (count--)
        writeRegion(*colors++, 1);
}


/// ----------------------------------------------------------------------
/// \brief Llegeix una sequencia de colors.
/// \param colors: Llista de colors.
/// \param count: Numero de colors a lleigir.
///
void ILI9341Driver::readRegion(
    Color *colors,
    int count) {

    lcdOpen();
    lcdWriteCommand(CMD_MEMORY_READ);
    lcdReadData();               // Dummy read
    lcdReadData();               // Dummy read
    while (count--) {

#if defined(DISPLAY_COLOR_RGB565)
        uint8_t volatile c1 = lcdReadData();
        uint8_t volatile c2 = lcdReadData();
        uint8_t volatile c3 = lcdReadData();
        Color color(c1, c2, c3);
        *colors++ = color;

#elif defined(DISPLAY_COLOR_RGB666)
#endif

    }
    lcdClose();
}
