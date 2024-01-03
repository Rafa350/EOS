#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/ILI9341/eosDisplayDriver_ILI9341.h"
#include "Controllers/Display/Drivers/ILI9341/eosDevice_ILI9341.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
///
DisplayDriver_ILI9341::DisplayDriver_ILI9341(
    Device_ILI9341 *device,
    int16_t displayWidth,
    int16_t displayHeight):

    _device {device},
    _displayWidth {displayWidth},
    _displayHeight {displayHeight},
	_maxX {displayWidth - 1},
	_maxY {displayHeight - 1} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la pantalla.
/// \remarks  La pantalla esta inicialment en OFF. Car cridar a la
///           funcio displayOn()
///
void DisplayDriver_ILI9341::initialize() {

    // Inicialitza el controlador del display
    //
#if defined(DISPLAY_ER_TFT028_4)
    static const uint8_t initCommands[] = {
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

#elif defined(HARDWARE_STM32F429I_DISC1)
    static const uint8_t initCommands[] = {
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
        __FRAME_RATE_CONTROL_1(0x00, 0x18),
        __DISPLAY_FUNCTION_CONTROL(0x08, 0x82, 0x27, 0x00),
        __TEARING_EFFECT_LINE_ON(0),
        __ENABLE_3G(0x00),
        __GAMMA_SET(0x01),
        __POSITIVE_GAMMA_CORRECTION( 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
                0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00),
        __NEGATIVE_GAMMA_CORRECTION(0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
                0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F),
        OP_END
    };
#endif

    uint8_t c;
    const uint8_t *p = initCommands;

    while ((c = *p++) != OP_END) {
        switch (c) {
            case OP_DELAY:
                HAL_Delay(*p++);
                break;

            default:
                _device->writeCommand(*p++);
                while (--c != 0)
                    _device->writeData(*p++);
                break;
        }
    }

    if constexpr (Color::format == ColorFormat::rgb565) {
        _device->writeCommand(CMD_PIXEL_FORMAT_SET);
        _device->writeData(0x55);
    }
    /*else if constexpr (CI::format == ColorFormat::rgb666) {
        _device->writeCommand(CMD_PIXEL_FORMAT_SET);
        _device->writeData(0x66);
    }*/
}


/// ----------------------------------------------------------------------
/// \brief Desactiva la pantalla
///
void DisplayDriver_ILI9341::deinitialize() {

    disable();
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

#elif defined(HARDWARE_STM32F429I_DISC1)
    static const uint8_t data0 = 0x08 | MAC_MV_OFF | MAC_MX_OFF | MAC_MY_ON;
	static const uint8_t data90 = 0x08 | MAC_MV_ON | MAC_MX_OFF | MAC_MY_OFF;
	static const uint8_t data180 = 0x08 | MAC_MV_OFF | MAC_MX_ON | MAC_MY_OFF;
	static const uint8_t data270 = 0x08 | MAC_MV_ON | MAC_MX_ON | MAC_MY_ON;
#endif

    uint8_t data = 0;
    switch (orientation) {
    	default:
        case DisplayOrientation::normal:
            _maxX = _displayWidth - 1;
            _maxY = _displayHeight - 1;
            data = data0;
            break;

        case DisplayOrientation::rotate90:
            _maxX = _displayHeight - 1;
            _maxY = _displayWidth - 1;
            data = data90;
            break;

        case DisplayOrientation::rotate180:
            _maxX = _displayWidth - 1;
            _maxY = _displayHeight - 1;
            data = data180;
            break;

        case DisplayOrientation::rotate270:
            _maxX = _displayHeight - 1;
            _maxY = _displayWidth - 1;
            data = data270;
            break;
    }

    if (data) {
		_device->writeCommand(CMD_MEMORY_ACCESS_CONTROL);
		_device->writeData(data);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Borra la pantalla
/// \param    color: Color per borrar
///
void DisplayDriver_ILI9341::clear(
    Color color) {

    selectRegion(0, 0, _maxX, _maxY);
    writeRegion(color, _displayWidth * _displayHeight);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    color: Color del pixel.
///
void DisplayDriver_ILI9341::setPixel(
    int16_t x,
    int16_t y,
    Color color) {

    selectRegion(x, y, x, y);
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
    int16_t x,
    int16_t y,
    int16_t length,
    Color color) {

    selectRegion(x, y, x + length - 1, y);
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
    int16_t x,
    int16_t y,
    int16_t length,
    Color color) {

    selectRegion(x, y, x, y + length - 1);
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
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height,
    Color color) {

    selectRegion(x, y, x + width - 1, y + height - 1);
    writeRegion(color, width * height);
}


/// ----------------------------------------------------------------------
/// \brief    Copia una regio rectangular de pixels.
/// \param    x: Posicio x.
/// \param    y: Posicio y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    colors: Colors a copiar.
/// \param    pitch: Pitch dels colors.
///
void DisplayDriver_ILI9341::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color *colors,
	int16_t pitch) {
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular de pixels.
/// \param    x: Posicio X.
/// \param    y: Posicio Y.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    colors: Color dels pixels.
///
void DisplayDriver_ILI9341::setPixels(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height,
    const void *pixels,
	ColorFormat format,
	int16_t pitch) {

    //selectRegion(x, y, x + width - 1, y + height - 1);
    //writeRegion(colors, width * height);
}


/// ----------------------------------------------------------------------
/// \brief    Refresca la imatge de la pantalla.
///
void DisplayDriver_ILI9341::refresh() {

}


/// ----------------------------------------------------------------------
/// \brief    Activa el display
///
void DisplayDriver_ILI9341::enable() {

    _device->writeCommand(CMD_SLEEP_OUT);
	//htl::tick::delay(120);
	HAL_Delay(120);
	_device->writeCommand(CMD_DISPLAY_ON);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_ILI9341::disable() {

    _device->writeCommand(CMD_DISPLAY_OFF);
    _device->writeCommand(CMD_ENTER_SLEEP_MODE);
	//htl::tick::delay(120);
    HAL_Delay(120);
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la regio de treball per les transferencies de
///           pixels.
/// \param    x1: Coordinada X origen.
/// \param    y1: Coordinada Y oriden.
/// \param    x2: Coordinada X final.
/// \param    y2: Coordinada Y final.
///
void DisplayDriver_ILI9341::selectRegion(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2) {

	uint8_t buffer[4];

    buffer[0] = x1 >> 8;
    buffer[1] = x1;
    buffer[2] = x2 >> 8;
    buffer[3] = x2;
    _device->writeCommand(CMD_COLUMN_ADDRESS_SET);
    _device->writeData(buffer, sizeof(buffer));

	buffer[0] = y1 >> 8;
    buffer[1] = y1;
    buffer[2] = y2 >> 8;
    buffer[3] = y2;
    _device->writeCommand(CMD_PAGE_ADDRESS_SET);
    _device->writeData(buffer, sizeof(buffer));
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un color en la regio seleccionada. Cas particular d'una
///		      regio de 1x1 pixel.
/// \param    data: El color.
///
void DisplayDriver_ILI9341::writeRegion(
	Color color) {

	Color::Pixel c = color;

	_device->writeCommand(CMD_MEMORY_WRITE);

	if constexpr (Color::format == ColorFormat::rgb565) {

		uint8_t data[2];
		data[0] = c >> 8;
		data[1] = c;

		_device->writeData(data, sizeof(data));
	}

	/*else if constexpr (CI::format == ColorFormat::rgb666) {

		uint8_t data[3];
		data[0] = (uint32_t)(c & 0x00FC0000) >> 16;
		data[1] = (uint32_t)(c & 0x0000FC00) >> 8;
		data[2] = (uint32_t)(c & 0x000000FC);

		_device->writeData(data, sizeof(data));
	}*/
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un color en el controlador.
/// \param    data: El color.
/// \param    count: Numero de copies a escriure.
///
void DisplayDriver_ILI9341::writeRegion(
    Color color,
    int32_t count) {

	Color::Pixel c = color;

	if constexpr (Color::format == ColorFormat::rgb565) {

		uint8_t data[2];
		data[0] = c >> 8;
		data[1] = c;

		_device->writeCommand(CMD_MEMORY_WRITE);
		while (count--)
			_device->writeData(data, sizeof(data));
	}

/*	else if constexpr (Color::format == ColorFormat::rgb888) {

        // TODO: Revisar la conversio que esta malament
		uint8_t data[3];
		data[0] = (c >> 16) & 0xFC;
		data[1] = (c >> 8) & 0xFC;
		data[2] = c & 0xFC;

		_device->writeCommand(CMD_MEMORY_WRITE);
		while (count--)
			_device->writeData(data, sizeof(data));
	}*/
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una llista de colors en el controlador
/// \param    colors: Llista de colors.
/// \param    count: Numero d'elements en la llista.
///
void DisplayDriver_ILI9341::writeRegion(
    const Color *colors,
    int32_t count) {

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
    int32_t count) {
#if 0
    _device->writeCommand(CMD_MEMORY_READ);
    _device->ReadData();               // Dummy read
    _device->ReadData();               // Dummy read
    while (count--) {

		if constexpr (CI::format == ColorFormat::rgb565) {
			uint8_t c1 = _device->readData();
			uint8_t c2 = _device->readData();
			uint8_t c3 = _device->readData();
			*colors++ = Color(c1, c2, c3);
		}

		/*else if constexpr (CI::format == ColorFormat::rgb666) {
		}*/
    }
#endif
}
