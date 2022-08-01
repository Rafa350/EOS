#include "eos.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HTL/STM32/htlDMA2D.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorMath.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    frameWidth: Amplada fisica en pixels.
/// \param    frameHeight: Alçada fisica en pixels.
/// \param    orientation: Orientacio inicial.
/// \param    buffer: Buffer d'imatge.
/// \param    bufferPitch: Pitch del buffer d'imatge.
///
ColorFrameBuffer_DMA2D::ColorFrameBuffer_DMA2D(
	int frameWidth,
	int frameHeight,
	DisplayOrientation orientation,
	void* buffer,
	int bufferPitch):

	FrameBuffer(frameWidth, frameHeight, orientation),
	_buffer((pixel_t*)buffer),
	_bufferPitch(bufferPitch) {

    DMA2D_1::init();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un color a un pixel.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    color: Color.
/// \remarks  No es fa cap tipus de verificacio dels parametres.
///
void ColorFrameBuffer_DMA2D::put(
	int x,
	int y,
	Color color) {

	// Color amb opacitat (Canal alpha)
	//
	if constexpr (Color::hasAlpha) {

		// Nomes el pinta si no es transparent
		//
		uint8_t opacity = color.getOpacity();
		if (opacity != 0) {

			pixel_t vPixel = toPixel(color);
			pixel_t* pPixel = getPixelPtr(x, y);

			*pPixel = opacity == 0xFF ? vPixel : combinePixels(*pPixel, vPixel, opacity);
		}
	}

	// Color sense opacitat
	//
	else {

		pixel_t vPixel = toPixel(color);
		pixel_t* pPixel = getPixelPtr(x, y);

		*pPixel = vPixel;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Ompla amb un color, una regio de la pantalla.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    color: Color.
/// \remarks  No es fa cap tipus de verificacio dels parametres.
///
void ColorFrameBuffer_DMA2D::fill(
	int x,
	int y,
	int width,
	int height,
	Color color) {

	uint8_t opacity = color.getOpacity();

	// Cas que sigui un color solid
	//
	if (opacity == 0xFF) {

		pixel_t vPixel = toPixel(color);
		pixel_t* pPixel = getPixelPtr(x, y);

		DMA2DColorMode colorMode;
		if constexpr (CI::format == ColorFormat::rgb565)
			colorMode = DMA2DColorMode::rgb565;
		else if constexpr (CI::format == ColorFormat::argb8888)
			colorMode = DMA2DColorMode::argb8888;
		else
			colorMode = DMA2DColorMode::rgb888;

		// Rellena la regio amb el valor de color del pixel. Hi ha que
		// suministrar el color en format adecuat, ja que no es fa cap
		// tipus de converssio. La funcio 'toPixel()' realitza la
		// converssio al format adequat.
		//
		DMA2D_1::startFill(pPixel, width, height, _bufferPitch - width, colorMode, vPixel);
		DMA2D_1::waitForFinish();
	}

	// Cas que no sigui transparent
	//
	else if (opacity != 0) {

		pixel_t vPixel = toPixel(color);

		for (int yy = y; yy < height + y; yy++)
			for (int xx = x; xx < width + x; xx++) {

				pixel_t* pPixel = getPixelPtr(xx, yy);

				*pPixel = combinePixels(*pPixel, vPixel, opacity);
			}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Copia un bitmap a una regio de la pantalla.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    colors: Llista de pixels del bitmap
/// \param    offset: Offset entre linies del bitmap.
///
void ColorFrameBuffer_DMA2D::copy(
	int x,
	int y,
	int width,
	int height,
	const Color *colors,
	int offset) {

	pixel_t *pPixel = getPixelPtr(x, y);

	DMA2DColorMode colorMode;
	if constexpr (CI::format == ColorFormat::rgb565)
		colorMode = DMA2DColorMode::rgb565;
	else if constexpr (CI::format == ColorFormat::argb8888)
		colorMode = DMA2DColorMode::argb8888;
	else
		colorMode = DMA2DColorMode::rgb888;

	DMA2DColorMode srcColorMode;
	if constexpr (Color::format == ColorFormat::rgb565)
		srcColorMode = DMA2DColorMode::rgb565;
	else if constexpr (Color::format == ColorFormat::argb8888)
		srcColorMode = DMA2DColorMode::argb8888;
	else
		srcColorMode = DMA2DColorMode::rgb888;

	// Rellena la regio amb el valor de color dels pixels. Aquesta funcio
	// Converteix el format de pixels gracies als parametres DFMT i SFMT de
	// les opcions.
	//
	DMA2D_1::startCopy(pPixel, width, height, _bufferPitch - width, colorMode, colors, offset, srcColorMode);
	DMA2D_1::waitForFinish();
}


/// ----------------------------------------------------------------------
/// \brief    Copia un bitmap a una regio de la pantalla.
/// \param    x: Coordinada x de la regio.
/// \param    y: Coordinada y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    pixels: Llista de pixels del bitmap
/// \param    format: Format de color
/// \param    offset: Offset entre linies del bitmap.
///
void ColorFrameBuffer_DMA2D::write(
	int x,
	int y,
	int width,
	int height,
	const void *pixels,
	ColorFormat format,
	int offset) {

	pixel_t* pPixel = getPixelPtr(x, y);

	DMA2DColorMode colorMode;
	if constexpr (CI::format == ColorFormat::rgb565)
		colorMode = DMA2DColorMode::rgb565;
	else if constexpr (CI::format == ColorFormat::argb8888)
		colorMode = DMA2DColorMode::argb8888;
	else
		colorMode = DMA2DColorMode::rgb888;

	DMA2DColorMode srcColorMode;
	if constexpr (Color::format == ColorFormat::rgb565)
		srcColorMode = DMA2DColorMode::rgb565;
	else if constexpr (Color::format == ColorFormat::argb8888)
		srcColorMode = DMA2DColorMode::argb8888;
	else
		srcColorMode = DMA2DColorMode::rgb888;

	// Rellena la regio amb el valor de color dels pixels. Aquesta funcio
	// Converteix el format de pixels gracies als parametres DFMT i SFMT de
	// les opcions. No cal cridar a 'toPixel()'
	//
	DMA2D_1::startCopy(pPixel, width, height, _bufferPitch - width, colorMode, pixels, offset, colorMode);
	DMA2D_1::waitForFinish();
}


/// ----------------------------------------------------------------------
/// \brief    Combina dos pixels amb opacitat
/// \param    b: Pixel de fons
/// \param    f: Pixel a combinar.
/// \param    opascity: Opacitat.
/// \return   El pixel combinat.
///
ColorFrameBuffer_DMA2D::pixel_t ColorFrameBuffer_DMA2D::combinePixels(
	pixel_t b,
	pixel_t f,
	uint8_t opacity) {

	uint8_t br = (b & CI::maskR) >> CI::shiftR;
	uint8_t bg = (b & CI::maskG) >> CI::shiftG;
	uint8_t bb = (b & CI::maskB) >> CI::shiftB;

	uint8_t fr = (f & CI::maskR) >> CI::shiftR;
	uint8_t fg = (f & CI::maskG) >> CI::shiftG;
	uint8_t fb = (f & CI::maskB) >> CI::shiftB;

	return
		((((fr * opacity) + (br * (255u - opacity))) >> 8) << CI::shiftR) |
		((((fg * opacity) + (bg * (255u - opacity))) >> 8) << CI::shiftG) |
		((((fb * opacity) + (bb * (255u - opacity))) >> 8) << CI::shiftB);
}

