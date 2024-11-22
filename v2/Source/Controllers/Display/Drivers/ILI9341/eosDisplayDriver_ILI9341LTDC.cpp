#include "eos.h"
#include "Controllers/Display/Drivers/ILI9341/eosDisplayDriver_ILI9341LTDC.h"
#include "Controllers/Display/Drivers/ILI9341/eosDevice_ILI9341.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HAL/halINT.h"
#include "HTL/STM32/htlLTDC.h"
#include "HTL/STM32/htlGPIO.h"
#include "System/Core/eosTask.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
DisplayDriver_ILI9341LTDC::DisplayDriver_ILI9341LTDC(
	Device_ILI9341 *devILI9341,
	htl::ltdc::LTDCDevice *devLTDC,
	htl::ltdc::LTDCLayerDevice *devLTDCLayer,
	FrameBuffer *frameBuffer):

    _devILI9341 {devILI9341},
	_devLTDC {devLTDC},
	_devLTDCLayer {devLTDCLayer},
	_frameBuffer {frameBuffer} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void DisplayDriver_ILI9341LTDC::initialize() {

}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el modul.
///
void DisplayDriver_ILI9341LTDC::deinitialize() {

	disable();
}


/// ----------------------------------------------------------------------
/// \brief    Activa el display
///
void DisplayDriver_ILI9341LTDC::enable() {

	_devLTDC->enable();
	_devILI9341->writeCommand(CMD_SLEEP_OUT);
	Task::delay(120);
	_devILI9341->writeCommand(CMD_DISPLAY_ON);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_ILI9341LTDC::disable() {

	_devILI9341->writeCommand(CMD_DISPLAY_OFF);
	_devILI9341->writeCommand(CMD_ENTER_SLEEP_MODE);
	Task::delay(120);
	_devLTDC->disable();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la orientacio.
/// \param    orientation: L'orientacio a seleccionar.
///
void DisplayDriver_ILI9341LTDC::setOrientation(
	DisplayOrientation orientation) {

	_frameBuffer->setOrientation(orientation);
}


/// ----------------------------------------------------------------------
/// \brief    Borra la pantalla.
/// \param    color: Color de borrat.
///
void DisplayDriver_ILI9341LTDC::clear(
	Color color) {

	_frameBuffer->clear(color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada x.
/// \param    y: Coordinada x.
/// \param    color: Color.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_ILI9341LTDC::setPixel(
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
/// \param    color: Color.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_ILI9341LTDC::setHPixels(
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
/// \param    color: Color.
/// \remarks  Si esta fora de limits no dibuixa res.
///
void DisplayDriver_ILI9341LTDC::setVPixels(
	int16_t x,
	int16_t y,
	int16_t size,
	Color color) {

	_frameBuffer->setPixels(x, y, 1, size, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular d'un color
/// \param    x: Posicio x.
/// \param    y: Posicio y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    color: Color.
///
void DisplayDriver_ILI9341LTDC::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	Color color) {

	_frameBuffer->setPixels(x, y, width, height, color);
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
void DisplayDriver_ILI9341LTDC::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color *colors,
	int16_t pitch) {

	_frameBuffer->setPixels(x, y, width, height, colors, pitch);
}


/// ----------------------------------------------------------------------
/// \brief    Copia una regio rectangular de pixels.
/// \param    x: Posicio x.
/// \param    y: Posicio y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    pixels: Array de pixels.
/// \param    format: El format de color dels pixels.
/// \param    pitch: Pitch dels colors.
///
void DisplayDriver_ILI9341LTDC::setPixels(
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
/// \brief    Refresca la pantalla
/// \remarks  La funcio no fa res, ja que el controlador LTDC, fa la
///           transferencia de dades a la pantalla de forma continua
///           i automatica.
///
void DisplayDriver_ILI9341LTDC::refresh() {

}
