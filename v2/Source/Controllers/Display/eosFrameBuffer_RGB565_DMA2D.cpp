#include "eos.h"
#include "Controllers/Display/eosFrameBuffer_RGB565_DMA2D.h"
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
/// \remarks  S'ajusta l'amplada per ser multiple de 64 bits, aixo permet
///           optimitzar les transferencies de DMA2D
///
FrameBuffer_RGB565_DMA2D::FrameBuffer_RGB565_DMA2D(
	int frameWidth,
	int frameHeight,
	DisplayOrientation orientation,
	void* buffer,
	int bufferPitch):

	FrameBuffer(frameWidth, frameHeight, orientation),
	_buffer((pixel_t*)buffer),
	_bufferPitch((((frameWidth * sizeof(pixel_t)) + 63) & 0xFFFFFFC0) / sizeof(pixel_t)) {

    halDMA2DInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un color a un pixel.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    color: Color.
/// \remarks  No es fa cap tipus de verificacio dels parametres.
///
void FrameBuffer_RGB565_DMA2D::put(
	int x,
	int y,
	Color color) {

	uint8_t opacity = color.getOpacity();
	if (opacity != 0) {

		pixel_t vPixel = toPixel(color);
		pixel_t* pPixel = getPixelPtr(x, y);

	    *pPixel = opacity == 0xFF ? vPixel : ColorMath::combineColor_RGB565(*pPixel, vPixel, opacity);
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
void FrameBuffer_RGB565_DMA2D::fill(
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
		// suministrar el color en format adecuat, ja que no es realitza
		// cap tipis de converssio de format.
		//
		halDMA2DStartFill(pPixel, width, height, _bufferPitch - width, options, vPixel);
		halDMA2DWaitForFinish();
	}

	else if (opacity > 0) {
		// TODO
		// Crear un buffer d'una linia amb el color. Pot ser l'ultima
		// linia del buffer
		// Tranferir la linia amb DMA2D
		for (int yy = 0; yy < height; yy++)
			for (int xx = 0; xx < width; xx++)
				put(x + xx, y + yy, color);
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
void FrameBuffer_RGB565_DMA2D::copy(
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
	// les opcions.
	//
	halDMA2DStartCopy(pPixel, width, height, _bufferPitch - width, options, (void*)colors, pitch - width);
	halDMA2DWaitForFinish();
}
