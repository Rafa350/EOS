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

	_screenWidth(screenWidth),
	_screenHeight(screenHeight),
	_maxX(screenWidth - 1),
	_maxY(screenHeight - 1),
	_orientation(DisplayOrientation::normal) {
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'orientacio de la imatge.
/// \param    orientation: L'orientacio.
///
void FrameBuffer::setOrientation(
	DisplayOrientation orientation) {

	_orientation = orientation;
	switch (_orientation) {
		case DisplayOrientation::normal:
		case DisplayOrientation::rotate180:
			_maxX = _screenWidth - 1;
			_maxY = _screenHeight - 1;
			break;

		case DisplayOrientation::rotate90:
		case DisplayOrientation::rotate270:
			_maxX = _screenHeight - 1;
			_maxY = _screenWidth - 1;
			break;
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
	switch (_orientation) {
		default:
		case DisplayOrientation::normal:
            xx = x;
            yy = y;
			break;

		case DisplayOrientation::rotate90:
			xx = (_screenWidth - 1) - y;
			yy = x;
			break;

		case DisplayOrientation::rotate180:
			xx = (_screenWidth - 1) - x;
			yy = (_screenHeight - 1) - y;
			break;

		case DisplayOrientation::rotate270:
			xx = y;
			yy = (_screenHeight - 1) - x;
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
	switch (_orientation) {
		default:
		case DisplayOrientation::normal:
            xx1 = x1;
            yy1 = y1;
            xx2 = x2;
            yy2 = y2;
			break;

		case DisplayOrientation::rotate90:
			xx1 = (_screenWidth - 1) - y1;
			yy1 = x1;
			xx2 = (_screenWidth - 1) - y2;
			yy2 = x2;
			break;

		case DisplayOrientation::rotate180:
			xx1 = (_screenWidth - 1) - x1;
			yy1 = (_screenHeight - 1) - y1;
			xx2 = (_screenWidth - 1) - x2;
			yy2 = (_screenHeight - 1) - y2;
			break;

		case DisplayOrientation::rotate270:
			xx1 = y1;
			yy1 = (_screenHeight - 1) - x1;
			xx2 = y2;
			yy2 = (_screenHeight - 1) - x2;
			break;
	}

	// Normalitza el resultat
	//
	x1 = Math::min(xx1, xx2);
	y1 = Math::min(yy1, yy2);
	x2 = Math::max(xx1, xx2);
	y2 = Math::max(yy1, yy2);
}
