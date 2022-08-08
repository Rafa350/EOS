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
	int frameWidth,
	int frameHeight,
	DisplayOrientation orientation) :

	_frameWidth(frameWidth),
	_frameHeight(frameHeight),
	_maxX(frameWidth - 1),
	_maxY(frameHeight - 1),
	_orientation(DisplayOrientation::normal) {
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'orientacio de la imatge.
/// \param    orientation: L'orientacio.
///
void FrameBuffer::setOrientation(
	DisplayOrientation orientation) {

	_orientation = orientation;
	switch (orientation) {
		case DisplayOrientation::normal:
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
	int &x,
	int &y) const {

	int xx;
	int yy;

	// Realitza la rotacio. D'aquesta manera es mes rapida que
	// fer dues multiplicacione fent servir la formula.
	//
	switch (_orientation) {
		case DisplayOrientation::rotate0:
            xx = x;
            yy = y;
			break;

		case DisplayOrientation::rotate90:
			xx = (_frameWidth - 1) - y;
			yy = x;
			break;

		case DisplayOrientation::rotate180:
			xx = (_frameWidth - 1) - x;
			yy = (_frameHeight - 1) - y;
			break;

		case DisplayOrientation::rotate270:
			xx = y;
			yy = (_frameHeight - 1) - x;
			break;
	}

	x = xx;
	y = yy;
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
	int &x1,
	int &y1,
	int &x2,
	int &y2) const {

	int xx1;
	int yy1;
	int xx2;
	int yy2;

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
	x1 = Math::min(xx1, xx2);
	y1 = Math::min(yy1, yy2);
	x2 = Math::max(xx1, xx2);
	y2 = Math::max(yy1, yy2);
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
	int x,
	int y,
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
	int x,
	int y,
	int width,
	int height,
	Color color) {

	int x1 = x;
	int y1 = y;
	int x2 = x + width - 1;
	int y2 = y + height - 1;

	// Retalla al tamany de pantalla
	//
	x1 = Math::max(x1, 0);
	y1 = Math::max(y1, 0);
	x2 = Math::min(x2, _maxX);
	y2 = Math::min(y2, _maxY);

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
	int x,
	int y,
	int width,
	int height,
	const Color *colors,
	int colorPitch) {

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
	int x,
	int y,
	int width,
	int height,
	const void *colors,
	ColorFormat colorFormat,
	int colorPitch)  {

	int x1 = x;
	int y1 = y;
	int x2 = x + width - 1;
	int y2 = y + height - 1;

	// Retalla al tamany de pantalla
	//
	x1 = Math::max(x1, 0);
	y1 = Math::max(y1, 0);
	x2 = Math::min(x2, _maxX);
	y2 = Math::min(y2, _maxY);

	if ((x1 <= x2) && (y1 <= y2)) {
		transform(x1, y1, x2, y2);

		int bytesPerPixel = 2;

		switch (_orientation) {
			case DisplayOrientation::rotate0:
				copy(x1, y1, width, height, colors, colorFormat, colorPitch);
				break;

			case DisplayOrientation::rotate90:
				for (int yy = 0; yy < height; yy++) {
					copy(
						x1 + height - yy, y1,
						1, width,
						(const void*)((int)colors + (colorPitch * bytesPerPixel * yy)),
						colorFormat,
						colorPitch);
				}
				break;

			case DisplayOrientation::rotate180:
				for (int yy = 0; yy < height; yy++)
					for (int xx = 0; xx < width; xx++) {
						int p = (int)colors + ((yy * colorPitch) + xx) * bytesPerPixel;
				}
				break;

			case DisplayOrientation::rotate270:
				for (int yy = 0; yy < height; yy++)
					for (int xx = 0; xx < width; xx++) {
						int p = (int)colors + ((yy * colorPitch) + xx) * bytesPerPixel;
				}
				break;
		}
	}
}
