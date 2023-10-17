#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "System/eosMath.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    frameWidth: Amplada.
/// \param    frameHeight: Alçada.
/// \param    orientation: Orientacio inicial.
///
FrameBuffer::FrameBuffer(
	int16_t frameWidth,
	int16_t frameHeight,
	DisplayOrientation orientation) :

	_frameWidth {frameWidth},
	_frameHeight {frameHeight},
	_maxX {frameWidth - 1},
	_maxY {frameHeight - 1},
	_orientation {DisplayOrientation::normal} {
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'orientacio de la imatge.
/// \param    orientation: L'orientacio.
///
void FrameBuffer::setOrientation(
	DisplayOrientation orientation) {

	_orientation = orientation;
	switch (orientation) {
		case DisplayOrientation::rotate0:
		case DisplayOrientation::rotate180:
			_maxX = _frameWidth - 1;
			_maxY = _frameHeight - 1;
			break;

		case DisplayOrientation::rotate90:
		case DisplayOrientation::rotate270:
			_maxX = _frameHeight - 1;
			_maxY = _frameWidth - 1;
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Transforma les coordinades d'un punt, segons l'orientacio de
///           la pantaslla
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
///
void FrameBuffer::transform(
	int16_t &x,
	int16_t &y) const {

	int16_t xx = x;
	int16_t yy = y;

	// Realitza la rotacio. D'aquesta manera es mes rapida que
	// fer dues multiplicacione fent servir la formula.
	//
	switch (_orientation) {
		case DisplayOrientation::rotate0:
			break;

		case DisplayOrientation::rotate90:
			x = (_frameWidth - 1) - yy;
			y = xx;
			break;

		case DisplayOrientation::rotate180:
			x = (_frameWidth - 1) - xx;
			y = (_frameHeight - 1) - yy;
			break;

		case DisplayOrientation::rotate270:
			x = yy;
			y = (_frameHeight - 1) - xx;
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Transforma les coordinades d'un rectangle segons l'orientacio
///           de la pantalla
/// \param    x1: Coordinada x esquerra.
/// \param    y1: Coordinada y superior.
/// \param    x2: Coordinada x dreta.
/// \param    y2: Coordinada y inferior.
/// \remarks  Les coordinades son retornades en forma normalitzada.
///
void FrameBuffer::transform(
	int16_t &x1,
	int16_t &y1,
	int16_t &x2,
	int16_t &y2) const {

	int16_t xx1;
	int16_t yy1;
	int16_t xx2;
	int16_t yy2;

	// Realitza la rotacio. D'aquesta manera es mes rapida que
	// fer dues multiplicacione fent servir la formula.
	//
	switch (_orientation) {
		default:
		case DisplayOrientation::normal:
            xx1 = x1;
            yy1 = y1;
            xx2 = x2;
            yy2 = y2;
			break;

		case DisplayOrientation::rotate90:
			xx1 = (_frameWidth - 1) - y1;
			yy1 = x1;
			xx2 = (_frameWidth - 1) - y2;
			yy2 = x2;
			break;

		case DisplayOrientation::rotate180:
			xx1 = (_frameWidth - 1) - x1;
			yy1 = (_frameHeight - 1) - y1;
			xx2 = (_frameWidth - 1) - x2;
			yy2 = (_frameHeight - 1) - y2;
			break;

		case DisplayOrientation::rotate270:
			xx1 = y1;
			yy1 = (_frameHeight - 1) - x1;
			xx2 = y2;
			yy2 = (_frameHeight - 1) - x2;
			break;
	}

	// Normalitza el resultat
	//
	x1 = math::min(xx1, xx2);
	y1 = math::min(yy1, yy2);
	x2 = math::max(xx1, xx2);
	y2 = math::max(yy1, yy2);
}


/// ----------------------------------------------------------------------
/// \brief    Borra la imatge.
/// \param    color: Color de borrat.
///
void FrameBuffer::clear(
	Color color) {

	fill(0, 0, _frameWidth, _frameHeight, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada X del pxel.
/// \param    y: Coordinada Y del pìxel.
/// \param    color: Color.
///
void FrameBuffer::setPixel(
	int16_t x,
	int16_t y,
	Color color) {

	if ((x >= 0) && (x <= _maxX) && (y >= 0) && (y <= _maxY)) {
		transform(x, y);
		put(x, y, color);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular de pixels.
/// \param    x: Posicio X de la regio.
/// \param    y: Posicio Y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    color: Color.
///
void FrameBuffer::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	Color color) {

	int16_t x1 = x;
	int16_t y1 = y;
	int16_t x2 = x + width - 1;
	int16_t y2 = y + height - 1;

	// Retalla al tamany de pantalla
	//
	x1 = math::max(x1, (int16_t)0);
	y1 = math::max(y1, (int16_t)0);
	x2 = math::min(x2, _maxX);
	y2 = math::min(y2, _maxY);

	// Cas que nomes sigui un pixel
	//
	if ((x1 == x2) && (y1 == y2)) {
		transform(x1, y1);
		put(x1, y1, color);
	}

	// Cas que hagi una regio rectangular per dibuixar
	//
	else if ((x1 <= x2) && (y1 <= y2)) {
		transform(x1, y1, x2, y2);
		fill(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en una regio rectangular.
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    colors: Array de colors.
/// \param    pitch: El pitch del array de colors.
///
void FrameBuffer::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color *colors,
	int16_t colorPitch) {

	// TODO: Girs i retall

	copy(x, y, width, height, colors, colorPitch);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una llista de colors en una regio rectangular
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    colors: Llista de colors.
/// \param    colorFormat: Format de la llista de colors.
/// \param    colorPpitch: Pitch de la llista de colors.
///
void FrameBuffer::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const void *colors,
	ColorFormat colorFormat,
	int16_t colorPitch)  {

	int16_t x1 = x;
	int16_t y1 = y;
	int16_t x2 = x + width - 1;
	int16_t y2 = y + height - 1;

	// Retalla al tamany de pantalla
	//
	x1 = math::max(x1, (int16_t)0);
	y1 = math::max(y1, (int16_t)0);
	x2 = math::min(x2, _maxX);
	y2 = math::min(y2, _maxY);

	if ((x1 <= x2) && (y1 <= y2)) {
		transform(x1, y1, x2, y2);

		int16_t bytesPerPixel = 2;

		switch (_orientation) {
			case DisplayOrientation::rotate0:
				copy(x1, y1, width, height, colors, colorFormat, colorPitch);
				break;

			case DisplayOrientation::rotate90:
				for (int16_t yy = 0; yy < height; yy++) {
					copy(
						x1 + height - yy, y1,
						1, width,
						(const void*)((int)colors + (colorPitch * bytesPerPixel * yy)),
						colorFormat,
						colorPitch);
				}
				break;

			case DisplayOrientation::rotate180:
				for (int16_t yy = 0; yy < height; yy++)
					for (int16_t xx = 0; xx < width; xx++) {
						int p = (int)colors + ((yy * colorPitch) + xx) * bytesPerPixel;
				}
				break;

			case DisplayOrientation::rotate270:
				for (int16_t yy = 0; yy < height; yy++)
					for (int16_t xx = 0; xx < width; xx++) {
						int p = (int)colors + ((yy * colorPitch) + xx) * bytesPerPixel;
				}
				break;
		}
	}
}
