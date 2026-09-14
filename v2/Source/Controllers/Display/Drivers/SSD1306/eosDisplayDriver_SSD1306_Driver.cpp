module;


#include "eos.h"


module Eos.Controllers.Display.Drivers.SSD1306;


/// ---------------------------------------------------------------------------
/// @brief    Constructor
///
eos::DisplayDriver_SSD1306::DisplayDriver_SSD1306(
    DisplayDevice_SSD1306 *device,
	L1FrameBuffer *frameBuffer):

    _device {device},
	_frameBuffer {frameBuffer} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void eos::DisplayDriver_SSD1306::initialize() {

    enable();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el driver.
///
void eos::DisplayDriver_SSD1306::deinitialize() {

	disable();
}


/// ----------------------------------------------------------------------
/// \brief    Encen el display
///
void eos::DisplayDriver_SSD1306::enable() {

    uint8_t command = DisplayDevice_SSD1306::Command::DISPLAY_ON;
	_device->writeCommand(&command, sizeof(command));
}


/// ----------------------------------------------------------------------
/// \brief    Apaga el display
///
void eos::DisplayDriver_SSD1306::disable() {

    uint8_t command = DisplayDevice_SSD1306::Command::DISPLAY_OFF;
    _device->writeCommand(&command, sizeof(command));
}


/// ----------------------------------------------------------------------
/// \brief    Borra la pantalla.
/// \param    color: Color de borrat.
///
void eos::DisplayDriver_SSD1306::clear(
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
void eos::DisplayDriver_SSD1306::setPixel(
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
void eos::DisplayDriver_SSD1306::setHPixels(
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
void eos::DisplayDriver_SSD1306::setVPixels(
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
void eos::DisplayDriver_SSD1306::setPixels(
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
void eos::DisplayDriver_SSD1306::setPixels(
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
void eos::DisplayDriver_SSD1306::setPixels(
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
void eos::DisplayDriver_SSD1306::refresh() {

    auto buffer = _frameBuffer->getBuffer();
    auto width = _frameBuffer->getWidth();
    auto height = _frameBuffer->getHeight();

    uint8_t cmd[6];
    cmd[0] = DisplayDevice_SSD1306::Command::SET_COLUMN;
    cmd[1] = 0;
    cmd[2] = width - 1;
    cmd[3] = DisplayDevice_SSD1306::Command::SET_PAGE;
    cmd[4] = 0;
    cmd[5] = (height / 8) - 1;

    _device->writeCommand(cmd, sizeof(cmd));
    _device->writeData(buffer, width * height / 8);
}
