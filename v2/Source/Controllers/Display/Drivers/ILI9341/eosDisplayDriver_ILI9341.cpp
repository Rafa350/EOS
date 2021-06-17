#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/ILI9341/eosDisplayDriver_ILI9341.h"
#include "Controllers/Display/Drivers/ILI9341/eosILI9341Defs.h"
#include "HAL/halTMR.h"
#include "System/eosMath.h"


#if !defined(DISPLAY_ER_TFT028_4) && \
    !defined(STM32F429I_DISC1)
#error "No se especifico DISPLAY_xxx"
#endif


using namespace eos;


IDisplayDriver *DisplayDriver_ILI9341::_instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief    Obte una instancia unica del driver.
/// \return   La instancia del driver.
///
IDisplayDriver *DisplayDriver_ILI9341::getInstance() {

	if (_instance == nullptr)
		_instance = new DisplayDriver_ILI9341();
	return _instance;
}


/// ----------------------------------------------------------------------
/// \brief    Contructor.
///
DisplayDriver_ILI9341::DisplayDriver_ILI9341():

	_imageWidth(DISPLAY_IMAGE_WIDTH),
	_imageHeight(DISPLAY_IMAGE_HEIGHT) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la pantalla.
/// \remarks  La pantalla esta inicialment en OFF. Car cridar a la
///           funcio displayOn()
///
void DisplayDriver_ILI9341::initialize() {

	hwInitialize();
}


/// ----------------------------------------------------------------------
/// \brief Desactiva la pantalla
///
void DisplayDriver_ILI9341::shutdown() {

    displayOff();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona l'orientacio de la pantalla.
/// \param    orientation: L'orientacio.
///
void DisplayDriver_ILI9341::setOrientation(
    DisplayOrientation orientation) {

#if defined(DISPLAY_ER_TFT028_4)
	static const uint8_t data0 = 0x08 | MAC_MV_OFF | MAC_MX_OFF | MAC_MY_OFF;
	static const uint8_t data90 = 0x08 | MAC_MV_ON | MAC_MX_ON | MAC_MY_OFF;
	static const uint8_t data180 = 0x08 | MAC_MV_OFF | MAC_MX_ON | MAC_MY_ON;
	static const uint8_t data270 = 0x08 | MAC_MV_ON | MAC_MX_OFF | MAC_MY_ON;

#elif defined(STM32F429I_DISC1)
    static const uint8_t data0 = 0x08 | MAC_MV_OFF | MAC_MX_OFF | MAC_MY_ON;
	static const uint8_t data90 = 0x08 | MAC_MV_ON | MAC_MX_OFF | MAC_MY_OFF;
	static const uint8_t data180 = 0x08 | MAC_MV_OFF | MAC_MX_ON | MAC_MY_OFF;
	static const uint8_t data270 = 0x08 | MAC_MV_ON | MAC_MX_ON | MAC_MY_ON;
#endif

    uint8_t data = 0;
    switch (orientation) {
        case DisplayOrientation::normal:
            _imageWidth = DISPLAY_IMAGE_WIDTH;
            _imageHeight = DISPLAY_IMAGE_HEIGHT;
            data = data0;
            break;

        case DisplayOrientation::rotate90:
            _imageWidth = DISPLAY_IMAGE_HEIGHT;
            _imageHeight = DISPLAY_IMAGE_WIDTH;
            data = data90;
            break;

        case DisplayOrientation::rotate180:
            _imageWidth = DISPLAY_IMAGE_WIDTH;
            _imageHeight = DISPLAY_IMAGE_HEIGHT;
            data = data180;
            break;

        case DisplayOrientation::rotate270:
            _imageWidth = DISPLAY_IMAGE_HEIGHT;
            _imageHeight = DISPLAY_IMAGE_WIDTH;
            data = data270;
            break;
    }

    if (data) {
		hwOpen();
		hwWriteCommand(CMD_MEMORY_ACCESS_CONTROL);
		hwWriteData(data);
		hwClose();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Borra la pantalla
/// \param    color: Color per borrar
///
void DisplayDriver_ILI9341::clear(
    const Color &color) {

    selectRegion(0, 0, _imageWidth, _imageHeight);
    writeRegion(color, _imageWidth * _imageHeight);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    color: Color del pixel.
///
void DisplayDriver_ILI9341::setPixel(
    int x,
    int y,
    const Color &color) {

    selectRegion(x, y, 1, 1);
    writeRegion(color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels horitzontals.
/// \param    x: Coordinada X.
/// \param    y: Colordinada Y.
/// \param    length: Longitut de la linia.
/// \param    color: Color dels pixels.
///
void DisplayDriver_ILI9341::setHPixels(
    int x,
    int y,
    int length,
    const Color &color) {

    selectRegion(x, y, length, 1);
    writeRegion(color, length);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels en vertical.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    length: Longitut de la linia.
/// \param    color: Color dels pixels.
///
void DisplayDriver_ILI9341::setVPixels(
    int x,
    int y,
    int length,
    const Color &color) {

    selectRegion(x, y, 1, length);
    writeRegion(color, length);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular de pixels.
/// \param    x: Posicio X.
/// \param    y: Posicio Y.
/// \param    width: Amplada de la regio.
/// \param    height: Al�ada de la regio.
/// \param    color: Color dels pixels.
///
void DisplayDriver_ILI9341::setPixels(
    int x,
    int y,
    int width,
    int height,
    const Color &color) {

    selectRegion(x, y, width, height);
    writeRegion(color, width * height);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular de pixels.
/// \param    x: Posicio X.
/// \param    y: Posicio Y.
/// \param    width: Amplada de la regio.
/// \param    height: Al�ada de la regio.
/// \param    colors: Color dels pixels.
///
void DisplayDriver_ILI9341::writePixels(
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
/// \brief    Llegeix una regio rectangular de pixels. No hi ha cap tipus de
///           comprovacio de la validesa dels parametres.
/// \param    x: Posicio X.
/// \param    y: Posicio Y.
/// \param    width: Amplada de la regio.
/// \param    height: Al�ada de la regio.
/// \params   colors: Buffer on deixar els pixels.
///
void DisplayDriver_ILI9341::readPixels(
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
/// \brief    Realitza un scroll vertical de la pantalla.
/// \param    delta: Numero de lineas a despla�ar. El signe indica la direccio.
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Al�ada de la regio.
///
void DisplayDriver_ILI9341::vScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

    static Color buffer[DISPLAY_IMAGE_WIDTH];

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
/// \brief    Realitza un scroll horitzontal de la pantalla.
/// \param    delta: Numero de lineas a despla�ar. El signe indica la direccio.
/// \param    delta: Numero de lineas a despla�ar. El signe indica la direccio.
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Al�ada de la regio.
///
void DisplayDriver_ILI9341::hScroll(
    int delta,
    int x,
    int y,
    int width,
    int height) {

}


/// ----------------------------------------------------------------------
/// \brief    Refresca la imatge de la pantalla.
///
void DisplayDriver_ILI9341::refresh() {

}


/// ----------------------------------------------------------------------
/// \brief    Activa el display
///
void DisplayDriver_ILI9341::displayOn() {

	hwOpen();
	hwWriteCommand(CMD_SLEEP_OUT);
	halTMRDelay(120);
	hwWriteCommand(CMD_DISPLAY_ON);
	hwClose();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_ILI9341::displayOff() {

	hwOpen();
	hwWriteCommand(CMD_DISPLAY_OFF);
	hwWriteCommand(CMD_ENTER_SLEEP_MODE);
	halTMRDelay(120);
	hwClose();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la regio de treball per les transferencies de
///           pixels.
/// \param    x: Coordinada X origen.
/// \param    y: Coordinada Y oriden.
/// \param    width: Amplada de la regio.
/// \param    height: Al�ada de la regio.
///
void DisplayDriver_ILI9341::selectRegion(
    int x,
    int y,
    int width,
    int height) {

	uint8_t buffer[4];

    int x2 = x + width - 1;
    int y2 = y + height - 1;

    hwOpen();

    hwWriteCommand(CMD_COLUMN_ADDRESS_SET);

    buffer[0] = x >> 8;
    buffer[1] = x;
    buffer[2] = x2 >> 8;
    buffer[3] = x2;
	hwWriteData(buffer, sizeof(buffer));

	hwWriteCommand(CMD_PAGE_ADDRESS_SET);

	buffer[0] = y >> 8;
    buffer[1] = y;
    buffer[2] = y2 >> 8;
    buffer[3] = y2;
	hwWriteData(buffer, sizeof(buffer));

    hwClose();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un color en la regio seleccionada. Cas particular d'una
///		      regio de 1x1 pixel.
/// \param    data: El color.
///
void DisplayDriver_ILI9341::writeRegion(
	const Color &color) {

#if defined(DISPLAY_COLOR_RGB565)

    uint16_t c = color.toRGB565();
    uint8_t cc[sizeof(uint16_t)];
 	cc[0] = c >> 8;
   	cc[1] = c;

    hwOpen();
    hwWriteCommand(CMD_MEMORY_WRITE);
    hwWriteData(cc, sizeof(cc));
    hwClose();

#elif defined(DISPLAY_COLOR_RGB666)

    uint32_t c = color.toRGB888();
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
/// \brief    Escriu un color en el controlador.
/// \param    data: El color.
/// \param    count: Numero de copies a escriure.
///
void DisplayDriver_ILI9341::writeRegion(
    const Color &color,
    int count) {

#if defined(DISPLAY_COLOR_RGB565)

	static uint8_t cc_buffer[sizeof(uint16_t) * DISPLAY_IMAGE_WIDTH] __attribute__ ((aligned (__BIGGEST_ALIGNMENT__)));
	static uint16_t _c;
    static int16_t _ccCapacity = 0;

	uint8_t* cc = (uint8_t*) cc_buffer;  // Fer-ho aixi si no no va
    uint16_t c = color.toRGB565();
	int ccCapacity = Math::min(count, (int)(sizeof(cc_buffer) / sizeof(cc_buffer[0])));
	if (c != _c || _ccCapacity < ccCapacity) {
		for (int16_t i = 0; i < ccCapacity; i++) {
			cc[i + i + 0] = c >> 8;
			cc[i + i + 1] = c;
		}
		_c = c;
		_ccCapacity = ccCapacity;
	}

    hwOpen();
    hwWriteCommand(CMD_MEMORY_WRITE);
    while (count) {
    	int16_t  n = ccCapacity;
    	if (count < n)
    		n = count;
        hwWriteData(cc, (int16_t) sizeof(uint16_t) * n);
        count -= n;
    }
    hwClose();

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
/// \brief    Escriu una llista de colors en el controlador
/// \param    colors: Llista de colors.
/// \param    count: Numero d'elements en la llista.
///
void DisplayDriver_ILI9341::writeRegion(
    const Color *colors,
    int count) {

    while (count--)
        writeRegion(*colors++, 1);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix una sequencia de colors.
/// \param    colors: Llista de colors.
/// \param    count: Numero de colors a lleigir.
///
void DisplayDriver_ILI9341::readRegion(
    Color *colors,
    int count) {

    hwOpen();
    hwWriteCommand(CMD_MEMORY_READ);
    hwReadData();               // Dummy read
    hwReadData();               // Dummy read
    while (count--) {

#if defined(DISPLAY_COLOR_RGB565)
        uint8_t volatile c1 = hwReadData();
        uint8_t volatile c2 = hwReadData();
        uint8_t volatile c3 = hwReadData();
        Color color(c1, c2, c3);
        *colors++ = color;

#elif defined(DISPLAY_COLOR_RGB666)
#endif

    }
    hwClose();
}
