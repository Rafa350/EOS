#include "eos.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HTL/STM32/htlDMA2D.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorMath.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Combina dos pixels amb opacitat
/// \param    fg: El pixel a combinar.
/// \param    bg: El pixel de fons.
/// \param    opascity: Opacitat del pixel fg.
/// \return   El pixel combinat.
///
static Color::Pixel combinePixels(
	Color::Pixel fg,
	Color::Pixel bg,
	uint8_t opacity) {

	using CT = ColorTrait<Color::format>;

	uint32_t fgR = (fg & CT::maskR) >> CT::shiftR;
	uint32_t fgG = (fg & CT::maskG) >> CT::shiftG;
	uint32_t fgB = (fg & CT::maskB) >> CT::shiftB;

	uint32_t bgR = (bg & CT::maskR) >> CT::shiftR;
	uint32_t bgG = (bg & CT::maskG) >> CT::shiftG;
	uint32_t bgB = (bg & CT::maskB) >> CT::shiftB;

	Color::Pixel c =
		((((fgR * opacity) + (bgR * (255 - opacity))) >> 8) << CT::shiftR) |
		((((fgG * opacity) + (bgG * (255 - opacity))) >> 8) << CT::shiftG) |
		((((fgB * opacity) + (bgB * (255 - opacity))) >> 8) << CT::shiftB);

	if constexpr (CT::hasAlpha)
		c |= 0xFF << CT::shiftA;

	return c;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el format de color es suportat pel DMA2D
/// \param    format: El format de color.
/// \return   True si esta suportat.
///
static constexpr bool isDstColorSuported(
	ColorFormat format) {

	return
		(format == ColorFormat::argb8888) ||
		(format == ColorFormat::argb4444) ||
		(format == ColorFormat::argb1555) ||
		(format == ColorFormat::rgb888) ||
		(format == ColorFormat::rgb565);
}


/// ----------------------------------------------------------------------
/// \brief    Obte l modus de color de sortida pel DMA2D.
/// \param    format: El format de color.
/// \return   El modus de color.
///
static constexpr DMA2DDstColorMode getDstColorMode(
	ColorFormat format) {

	switch (format) {
		case ColorFormat::argb8888:
			return DMA2DDstColorMode::argb8888;

		case ColorFormat::argb4444:
			return DMA2DDstColorMode::argb4444;

		case ColorFormat::argb1555:
			return DMA2DDstColorMode::argb1555;

		case ColorFormat::rgb888:
			return DMA2DDstColorMode::rgb888;

		case ColorFormat::rgb565:
			return DMA2DDstColorMode::rgb565;
	}
}


static constexpr DMA2DSrcColorMode getSrcColorMode(
	ColorFormat format) {

}


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
	_buffer((Color::Pixel*)buffer),
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

			Color::Pixel c = color;
			Color::Pixel *ptr = getPixelPtr(x, y);

			*ptr = opacity == 0xFF ? c : combinePixels(c, *ptr, opacity);
		}
	}

	// Color sense opacitat
	//
	else {

		Color::Pixel c = color;
		Color::Pixel *ptr = getPixelPtr(x, y);

		*ptr = c;
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

	// Cas que sigui un color solid per utilitzar DAM2D R2M
	//
	if ((opacity == 0xFF) &&
		isDstColorSuported(Color::format)) {

		Color::Pixel *ptr = getPixelPtr(x, y);
		DMA2DDstColorMode dstColorMode = getDstColorMode(Color::format);
		Color::Pixel c = color;
		DMA2D_1::startFill(ptr, width, height, _bufferPitch - width, dstColorMode, c);
		DMA2D_1::waitForFinish();
	}

	// Cas que no sigui transparent, relitza una transferencia per soft
	//
	else if (opacity != 0) {

		Color::Pixel c = color;

		for (int yy = y; yy < height + y; yy++) {
			Color::Pixel *ptr = getPixelPtr(x, yy);
			for (int xx = x; xx < width + x; xx++) {
				*ptr = combinePixels(c, *ptr, opacity);
				ptr++;
			}
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

	Color::Pixel *ptr = getPixelPtr(x, y);

	// Rellena la regio amb el valor de color dels pixels. Aquesta funcio
	// Converteix el format de pixels gracies als parametres DFMT i SFMT de
	// les opcions.
	//
	DMA2DDstColorMode dstColorMode = getDstColorMode(Color::format);
	DMA2DSrcColorMode srcColorMode = getSrcColorMode(Color::format);
	DMA2D_1::startCopy(ptr, width, height, _bufferPitch - width, dstColorMode, colors, offset, srcColorMode);
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

	Color::Pixel *ptr = getPixelPtr(x, y);

	// Rellena la regio amb el valor de color dels pixels. Aquesta funcio
	// Converteix el format de pixels gracies als parametres DFMT i SFMT de
	// les opcions. No cal cridar a 'toPixel()'
	//
	DMA2DDstColorMode dstColorMode = getDstColorMode(Color::format);
	DMA2DSrcColorMode srcColorMode = getSrcColorMode(format);
	DMA2D_1::startCopy(ptr, width, height, _bufferPitch - width, dstColorMode, pixels, offset, srcColorMode);
	DMA2D_1::waitForFinish();
}
