#include "eos.h"
#include "Controllers/Display/eosColorFrameBuffer.h"
#include "System/eosMath.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    screenWidth: Amplada fisica de la pantalla.
/// \param    screenHeight: Alçada fisica de la pantalla.
/// \param    orientation: Orientacio inicial.
///
ColorFrameBuffer::ColorFrameBuffer(
	int screenWidth,
	int screenHeight,
	DisplayOrientation orientation):

	FrameBuffer(screenWidth, screenHeight, orientation) {
}


/// ----------------------------------------------------------------------
/// \brief    Borra la imatge.
/// \param    color: Color de borrat.
///
void ColorFrameBuffer::clear(
	const Color &color) {

	fill(0, 0, getWidth(), getHeight(), color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    color: Color del pixel.
///
void ColorFrameBuffer::setPixel(
	int x,
	int y,
	const Color& color) {

	if ((x >= 0) && (x < getWidth()) && (y >= 0) && (y < getHeight())) {
		rotate(x, y);
		put(x, y, color);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular de pixels.
/// \param    x: Posicio X.
/// \param    y: Posicio Y.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    color: Color dels pixels.
///
void ColorFrameBuffer::setPixels(
	int x,
	int y,
	int width,
	int height,
	const Color &color) {

	int x1 = x;
	int y1 = y;
	int x2 = x + width - 1;
	int y2 = y + height - 1;

	// Retalla al tamany de pantalla
	//
	x1 = Math::max(x1, 0);
	y1 = Math::max(y1, 0);
	x2 = Math::min(x2, getWidth() - 1);
	y2 = Math::min(y2, getHeight() - 1);

	// Cas que nomes sigui un pixel
	//
	if ((x1 == x2) && (y1 == y2)) {
		rotate(x1, y1);
		put(x1, y1, color);
	}

	// Cas que hagi una regio rectangular per dibuixar
	//
	else if ((x1 <= x2) && (y1 <= y2)) {
		rotate(x1, y1, x2, y2);
		fill(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en una regio rectangular.
/// \param    x: Posicio X.
/// \param    y: Posicio Y.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    colors: Els colors d'origen a copiar.
/// \param    dx: Offset X del origen.
/// \param    dy: Offset Y del origen.
/// \param    pitch: Pitch del origen.
///
void ColorFrameBuffer::writePixels(
	int x,
	int y,
	int width,
	int height,
	const Color* colors,
	int dx,
	int dy,
	int pitch) {

	//TODO Girs i retall

	copy(x, y, width, height, colors, dx, dy, pitch);
}
