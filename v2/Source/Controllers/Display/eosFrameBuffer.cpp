#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "System/eosMath.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    screenWidth: Amplada fisica de la pantalla.
/// \param    screenHeight: Alçada fisica de la pantalla.
/// \param    orientation: Orientacio inicial.
/// \param    imageBuffer: Buffer d'imatge.
/// \param    colorFormat: Format de color del buffer.
///
FrameBuffer::FrameBuffer(
	int screenWidth,
	int screenHeight,
	DisplayOrientation orientation):

	screenWidth(screenWidth),
	screenHeight(screenHeight) {

	setOrientation(orientation);
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'orientacio de la imatge.
/// \param    orientation: L'orientacio.
///
void FrameBuffer::setOrientation(
	DisplayOrientation orientation) {

	this->orientation = orientation;
	switch (orientation) {
		case DisplayOrientation::normal:
		case DisplayOrientation::rotate180:
			maxX = screenWidth - 1;
			maxY = screenHeight - 1;
			break;

		case DisplayOrientation::rotate90:
		case DisplayOrientation::rotate270:
			maxX = screenHeight - 1;
			maxY = screenWidth - 1;
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Borra la imatge.
/// \param color: Color de borrat.
///
void FrameBuffer::clear(
	const Color &color) {

	fill(0, 0, maxX + 1, maxY + 1, color);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param color: Color del pixel.
///
void FrameBuffer::setPixel(
	int x,
	int y,
	const Color& color) {

	if ((x >= 0) && (x <= maxX) && (y >= 0) && (y <= maxY)) {
		rotate(x, y);
		put(x, y, color);
	}
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
/// \param color: Color dels pixels.
///
void FrameBuffer::setPixels(
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
	x2 = Math::min(x2, maxX);
	y2 = Math::min(y2, maxY);

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
/// \brief Rota les coordinades d'un punt.
/// \param x: Coordinada X del punt.
/// \param y: Coordinada Y del punt.
///
void FrameBuffer::rotate(
	int &x,
	int &y) {

	int xx;
	int yy;

	// Realitza la rotacio. D'aquesta manera es mes rapida que
	// fer dues multiplicacione fent servir la formula.
	//
	switch (orientation) {
		default:
		case DisplayOrientation::normal:
            xx = x;
            yy = y;
			break;

		case DisplayOrientation::rotate90:
			xx = (screenWidth - 1) - y;
			yy = x;
			break;

		case DisplayOrientation::rotate180:
			xx = (screenWidth - 1) - x;
			yy = (screenHeight - 1) - y;
			break;

		case DisplayOrientation::rotate270:
			xx = y;
			yy = (screenHeight - 1) - x;
			break;
	}

	x = xx;
	y = yy;
}


/// ----------------------------------------------------------------------
/// \brief Rota les coordinades d'un rectangle.
/// \param x1: Coordinada X esquerra.
/// \param y1: Coordinada Y superior.
/// \param x2: Coordinada X dreta.
/// \param y2: Coordinada Y inferior.
/// \remarks Les coordinades son retornades en forma normalitzada.
///
void FrameBuffer::rotate(
	int &x1,
	int &y1,
	int &x2,
	int &y2) {

	int xx1;
	int yy1;
	int xx2;
	int yy2;

	// Realitza la rotacio. D'aquesta manera es mes rapida que
	// fer dues multiplicacione fent servir la formula.
	//
	switch (orientation) {
		default:
		case DisplayOrientation::normal:
            xx1 = x1;
            yy1 = y1;
            xx2 = x2;
            yy2 = y2;
			break;

		case DisplayOrientation::rotate90:
			xx1 = (screenWidth - 1) - y1;
			yy1 = x1;
			xx2 = (screenWidth - 1) - y2;
			yy2 = x2;
			break;

		case DisplayOrientation::rotate180:
			xx1 = (screenWidth - 1) - x1;
			yy1 = (screenHeight - 1) - y1;
			xx2 = (screenWidth - 1) - x2;
			yy2 = (screenHeight - 1) - y2;
			break;

		case DisplayOrientation::rotate270:
			xx1 = y1;
			yy1 = (screenHeight - 1) - x1;
			xx2 = y2;
			yy2 = (screenHeight - 1) - x2;
			break;
	}

	// Normalitza el resultat
	//
	x1 = Math::min(xx1, xx2);
	y1 = Math::min(yy1, yy2);
	x2 = Math::max(xx1, xx2);
	y2 = Math::max(yy1, yy2);
}

