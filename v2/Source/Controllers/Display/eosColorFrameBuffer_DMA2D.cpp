#include "eos.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HAL/STM32/halDMA2DTpl.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorMath.h"


using namespace eos;


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

    halDMA2DInitialize();
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
	if constexpr (Color::CI::hasAlpha) {

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
	if (opacity == 0xFF) {

		pixel_t vPixel = toPixel(color);
		pixel_t* pPixel = getPixelPtr(x, y);

		DMA2DOptions options = DMA2DOptionsFor<CI::format>::DFMT;

		// Rellena la regio amb el valor de color del pixel. Hi ha que
		// suministrar el color en format adecuat, ja que no es fa cap
		// tipus de converssio. La funcio 'toPixel()' realitza la
		// converssio al format adequat.
		//
		halDMA2DStartFill(pPixel, width, height, _bufferPitch - width, options, vPixel);
		halDMA2DWaitForFinish();
	}

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
/// \param    pitch: Offset a la seguent linia del bitmap.
///
void ColorFrameBuffer_DMA2D::copy(
	int x,
	int y,
	int width,
	int height,
	const Color* colors,
	int pitch) {

	// TODO: Revisar que esta malament dy * height --> dy * (width + pitch)

	pixel_t* pPixel = getPixelPtr(x, y);

	DMA2DOptions options =
		DMA2DOptionsFor<CI::format>::DFMT |
		DMA2DOptionsFor<Color::CI::format>::SFMT;

	// Rellena la regio amb el valor de color dels pixels. Aquesta funcio
	// Converteix el format de pixels gracies als parametres DFMT i SFMT de
	// les opcions. No cal cridar a 'toPixel()'
	//
	halDMA2DStartCopy(pPixel, width, height, _bufferPitch - width, options, (void*)colors, pitch - width);
	halDMA2DWaitForFinish();
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

