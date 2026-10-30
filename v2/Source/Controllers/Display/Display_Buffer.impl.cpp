module Eos.Controllers.Display;

import Eos.Math;


using namespace eos;


/// --------------------------------------------------------------------------------
/// @brief    Constructor del objecte.
/// @param    frameWidth: Amplada fisica del display
/// @param    frameHeight: Alçada fisica del display
/// @param    orientation: Orientacio de les coordinades respecte a l'orientacio
///           fisica del display.
///
DisplayBuffer::DisplayBuffer(
	Int16 frameWidth,
	Int16 frameHeight,
	Orientation orientation) :

	_frameWidth {frameWidth},
	_frameHeight {frameHeight},
	_maxX {(Int16)(frameWidth - 1)},
	_maxY {(Int16)(frameHeight - 1)},
	_orientation {orientation} {
}


/// ---------------------------------------------------------------------------
/// @brief    Canvia l'orientacio de la imatge.
/// @param    orientation: L'orientacio.
///
void DisplayBuffer::setOrientation(
	Orientation orientation) {

	_orientation = orientation;
	switch (orientation) {
		case Orientation::rotate0:
		case Orientation::rotate180:
			_maxX = _frameWidth - 1;
			_maxY = _frameHeight - 1;
			break;

		case Orientation::rotate90:
		case Orientation::rotate270:
			_maxX = _frameHeight - 1;
			_maxY = _frameWidth - 1;
			break;
	}
}


/// ---------------------------------------------------------------------------
/// @brief    Transforma les coordinades d'un punt, segons l'orientacio de
///           la pantalla
/// @param    x: Coordinada x.
/// @param    y: Coordinada y.
///
void DisplayBuffer::transform(
	Int16 &x,
	Int16 &y) const {

	Int16 xx = x;
	Int16 yy = y;

	// Realitza la rotacio. D'aquesta manera es mes rapida que
	// fer dues multiplicacione fent servir la formula.
	//
	switch (_orientation) {
		case Orientation::rotate0:
			break;

		case Orientation::rotate90:
			x = (_frameWidth - 1) - yy;
			y = xx;
			break;

		case Orientation::rotate180:
			x = (_frameWidth - 1) - xx;
			y = (_frameHeight - 1) - yy;
			break;

		case Orientation::rotate270:
			x = yy;
			y = (_frameHeight - 1) - xx;
			break;
	}
}


/// ---------------------------------------------------------------------------
/// @brief    Transforma les coordinades d'un rectangle segons l'orientacio
///           de la pantalla
/// @param    x1: Coordinada x esquerra.
/// @param    y1: Coordinada y superior.
/// @param    x2: Coordinada x dreta.
/// @param    y2: Coordinada y inferior.
/// @remarks  Les coordinades son retornades en forma normalitzada.
///
void DisplayBuffer::transform(
	Int16 &x1,
	Int16 &y1,
	Int16 &x2,
	Int16 &y2) const {

	Int16 xx1;
	Int16 yy1;
	Int16 xx2;
	Int16 yy2;

	// Realitza la rotacio. D'aquesta manera es mes rapida que
	// fer dues multiplicacione fent servir la formula.
	//
	switch (_orientation) {
		default:
		case Orientation::normal:
            xx1 = x1;
            yy1 = y1;
            xx2 = x2;
            yy2 = y2;
			break;

		case Orientation::rotate90:
			xx1 = (_frameWidth - 1) - y1;
			yy1 = x1;
			xx2 = (_frameWidth - 1) - y2;
			yy2 = x2;
			break;

		case Orientation::rotate180:
			xx1 = (_frameWidth - 1) - x1;
			yy1 = (_frameHeight - 1) - y1;
			xx2 = (_frameWidth - 1) - x2;
			yy2 = (_frameHeight - 1) - y2;
			break;

		case Orientation::rotate270:
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


/// ---------------------------------------------------------------------------
/// @brief    Borra la imatge.
/// @param    color: Color de borrat.
///
void DisplayBuffer::clear(
	Color color) {

	fill(0, 0, _frameWidth, _frameHeight, color);
}


/// ---------------------------------------------------------------------------
/// @brief    Dibuixa un pixel.
/// @param    x: Coordinada X del pxel.
/// @param    y: Coordinada Y del pìxel.
/// @param    color: Color.
///
void DisplayBuffer::setPixel(
	Int16 x,
	Int16 y,
	Color color) {

	if ((x >= 0) && (x <= _maxX) && (y >= 0) && (y <= _maxY)) {
		transform(x, y);
		put(x, y, color);
	}
}


/// ---------------------------------------------------------------------------
/// @brief    Dibuixa una regio rectangular de pixels.
/// @param    x: Posicio X de la regio.
/// @param    y: Posicio Y de la regio.
/// @param    width: Amplada de la regio.
/// @param    height: Alçada de la regio.
/// @param    color: Color.
///
void DisplayBuffer::setPixels(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	Color color) {

	Int16 x1 = x;
	Int16 y1 = y;
	Int16 x2 = x + width - 1;
	Int16 y2 = y + height - 1;

	// Retalla al tamany de pantalla
	//
	x1 = Math::max(x1, (Int16)0);
	y1 = Math::max(y1, (Int16)0);
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


/// ---------------------------------------------------------------------------
/// @brief    Escriu en una regio rectangular.
/// @param    x: Posicio x de la regio.
/// @param    y: Posicio y de la regio.
/// @param    width: Amplada de la regio.
/// @param    height: Alçada de la regio.
/// @param    colors: Array de colors.
/// @param    pitch: El pitch del array de colors.
///
void DisplayBuffer::setPixels(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	const Color *colors,
	Int16 colorPitch) {

	// TODO: Girs i retall

	copy(x, y, width, height, colors, colorPitch);
}


/// ---------------------------------------------------------------------------
/// @brief    Escriu una llista de colors en una regio rectangular
/// @param    x: Posicio x de la regio.
/// @param    y: Posicio y de la regio.
/// @param    width: Amplada de la regio.
/// @param    height: Alçada de la regio.
/// @param    colors: Llista de colors.
/// @param    colorFormat: Format de la llista de colors.
/// @param    colorPitch: Pitch de la llista de colors.
///
void DisplayBuffer::setPixels(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	const void *colors,
	ColorFormat colorFormat,
	Int16 colorPitch)  {

	Int16 x1 = x;
	Int16 y1 = y;
	Int16 x2 = x + width - 1;
	Int16 y2 = y + height - 1;

	// Retalla al tamany de pantalla
	//
	x1 = Math::max(x1, (Int16)0);
	y1 = Math::max(y1, (Int16)0);
	x2 = Math::min(x2, _maxX);
	y2 = Math::min(y2, _maxY);

	if ((x1 <= x2) && (y1 <= y2)) {
		transform(x1, y1, x2, y2);

		Int16 bytesPerPixel = 2;

		switch (_orientation) {
			case Orientation::rotate0:
				copy(x1, y1, width, height, colors, colorFormat, colorPitch);
				break;

			case Orientation::rotate90:
				for (Int16 yy = 0; yy < height; yy++) {
					copy(
						x1 + height - yy, y1,
						1, width,
						(const void*)((int)colors + (colorPitch * bytesPerPixel * yy)),
						colorFormat,
						colorPitch);
				}
				break;

			case Orientation::rotate180:
				for (Int16 yy = 0; yy < height; yy++)
					for (Int16 xx = 0; xx < width; xx++) {
						int p = (int)colors + ((yy * colorPitch) + xx) * bytesPerPixel;
				}
				break;

			case Orientation::rotate270:
				for (Int16 yy = 0; yy < height; yy++)
					for (Int16 xx = 0; xx < width; xx++) {
						int p = (int)colors + ((yy * colorPitch) + xx) * bytesPerPixel;
				}
				break;
		}
	}
}
