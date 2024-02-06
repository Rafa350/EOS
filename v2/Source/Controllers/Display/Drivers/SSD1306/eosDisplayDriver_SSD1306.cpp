#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlTick.h"
#include "Controllers/Display/eosMonoFrameBuffer.h"
#include "Controllers/Display/Drivers/SSD1306/eosDevice_SSD1306.h"
#include "Controllers/Display/Drivers/SSD1306/eosDisplayDriver_SSD1306.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
DisplayDriver_SSD1306::DisplayDriver_SSD1306(
    Device_SSD1306 *device,
	FrameBuffer *frameBuffer):

    _device {device},
	_frameBuffer {frameBuffer} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void DisplayDriver_SSD1306::initialize() {

    enable();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el driver.
///
void DisplayDriver_SSD1306::deinitialize() {

	disable();
}


/// ----------------------------------------------------------------------
/// \brief    Encen el display
///
void DisplayDriver_SSD1306::enable() {

    uint8_t command = 0xAF;
	_device->writeCommand(&command, sizeof(command));
}


/// ----------------------------------------------------------------------
/// \brief    Apaga el display
///
void DisplayDriver_SSD1306::disable() {

    uint8_t command = 0xAE;
    _device->writeCommand(&command, sizeof(command));
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona l'orientacio.
/// \param    orientation: L'orientacio.
///
void DisplayDriver_SSD1306::setOrientation(
    DisplayOrientation orientation) {

	_frameBuffer->setOrientation(orientation);
}


/// ----------------------------------------------------------------------
/// \brief    Borra la pantalla.
/// \param    color: Color de borrat.
///
void DisplayDriver_SSD1306::clear(
    Color color) {

	_frameBuffer->clear(color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada x.
/// \param    y: Coordinada x.
/// \param    color: Color del pixel.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_SSD1306::setPixel(
    int16_t x,
    int16_t y,
    Color color) {

	_frameBuffer->setPixel(x, y, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels horitzontals.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    length: Longitut de la linia.
/// \param    color: Color dels pixels.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_SSD1306::setHPixels(
    int16_t x,
    int16_t y,
    int16_t size,
    Color color) {

	_frameBuffer->setPixels(x, y, size, 1, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels en vertical.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    length: Longitut de la linia.
/// \param    color: Color dels pixels.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_SSD1306::setVPixels(
    int16_t x,
    int16_t y,
    int16_t size,
    Color color) {

	_frameBuffer->setPixels(x, y, 1, size, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular.
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    color: Color.
///
void DisplayDriver_SSD1306::setPixels(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height,
    Color color) {

	_frameBuffer->setPixels(x, y, width, height, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular.
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    color: Punter als colors.
/// \param    pitch: Pitch dels colors.
///
void DisplayDriver_SSD1306::setPixels(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height,
    const Color *color,
	int16_t pitch) {

	_frameBuffer->setPixels(x, y, width, height, color, pitch);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular.
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    pixels: Punter als colors.
/// \param    format: Format de color
/// \param    pitch: Pitch dels colors.
///
void DisplayDriver_SSD1306::setPixels(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height,
    const void *pixels,
    ColorFormat format,
    int16_t pitch) {

	_frameBuffer->setPixels(x, y, width, height, pixels, format, pitch);
}


/// ----------------------------------------------------------------------
/// \brief    Transfereix el buffer d'imatge al controlador
///
void DisplayDriver_SSD1306::refresh() {

    auto buffer = _frameBuffer->getBuffer();
    auto width = _frameBuffer->getWidth();
    auto height = _frameBuffer->getHeight();

    uint8_t command[3];
    command[0] = 0x0B;
    command[1] = 0x00;
    command[2] = 0x10;

    // Bucle per procesat totes les pagines
    //
    for (uint8_t i = 0, ii = height / 8; i < ii; i++) {

        // Transfereix una pagina
        //
        _device->writeCommand(command, sizeof(command));
        _device->writeData(buffer, width);

        // Pasa a la seguent pagina
        //
        command[0] += 1;
        buffer += width;
    }
}
