#include "eos.h"
#include "Controllers/Display/eosFrameBuffer_RGB565_DMA2D.h"
#include "HAL/STM32/halDMA2D.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorMath.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    screenWidth: Amplada fisica de la pantalla.
/// \param    screenHeight: Alçada fisica de la pantalla.
/// \param    orientation: Orientacio inicial.
/// \param    buffer: Buffer d'imatge.
/// \param    lineBytes: Bytes per linia d'imatge.
///
RGB565_DMA2D_FrameBuffer::RGB565_DMA2D_FrameBuffer(
	int screenWidth,
	int screenHeight,
	DisplayOrientation orientation,
	uint8_t* buffer,
	int lineBytes):

	ColorFrameBuffer(screenWidth, screenHeight, orientation),
	_buffer(buffer),
	_lineWidth(lineBytes / _pixelBytes),      // Amplada de linia en pixels
	_lineBytes(lineBytes) {                   // Amplada de linia en bytes

    halDMA2DInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un color a un pixel.
/// \param    x: Coordinada X del pixel.
/// \param    y: Coordinada Y del pixel.
/// \param    color: Color en format de pixel fisic;
/// \remarks  No es fa cap tipus de verificacio dels parametres.
///
void RGB565_DMA2D_FrameBuffer::put(
	int x,
	int y,
	const Color& color) {

	uint8_t opacity = color.getOpacity();
	if (opacity != 0) {
		uint16_t c = color.toRGB565();
		uint16_t* p = (uint16_t*) getPixelAddr(x, y);
	    *p = opacity == 0xFF ? c : ColorMath::RGB565_combineColor(*p, c, opacity);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Ompla amb un color, una regio de la pantalla.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    width: Amplada del bloc.
/// \param    height: Alçada del bloc.
/// \param    color: Color.
/// \remarks  No es fa cap tipus de verificacio dels parametres.
///
void RGB565_DMA2D_FrameBuffer::fill(
	int x,
	int y,
	int width,
	int height,
	const Color& color) {

	uint8_t opacity = color.getOpacity();
	if (opacity == 0xFF) {

		uint32_t addr = getPixelAddr(x, y);

		halDMA2DStartFill(
			addr,
			width,
			height,
			_lineWidth - width,
			HAL_DMA2D_DFMT_RGB565,
			color.toRGB565());

		halDMA2DWaitForFinish();
	}
	else if (opacity > 0) {
		// TODO
		// Crear un buffer d'una linia amb el color
		// Tranferir la linia amb DMA2D
		for (int yy = 0; yy < height; yy++)
			for (int xx = 0; xx < width; xx++)
				put(x + xx, y + yy, color);
	}
}

/// ----------------------------------------------------------------------
/// \brief    Copia un bitmap a una regio de la pantalla.
/// \param    x: Coordinada X de la posicio.
/// \param    y: Coordinada Y de la posicio.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    colors: Llista de pixels.
/// \param    dx: Offset X dins del bitmap.
/// \param    dy: offset Y dins del vitmap.
/// \param    pitch: Offset a la seguent linia del bitmap. 0 si son consecutives.
///
void RGB565_DMA2D_FrameBuffer::copy(
	int x,
	int y,
	int width,
	int height,
	const Color* colors,
	int dx,
	int dy,
	int pitch) {

#if defined(EOS_COLOR_ARGB8888)
	uint32_t colorAddr = ((uint32_t) colors) + (((dy * height) + dx) * sizeof(uint32_t));
	DMA2DOptions options = HAL_DMA2D_DFMT_RGB565 | HAL_DMA2D_SFMT_ARGB8888;

#elif defined(EOS_COLOR_RGB565)
	uint32_t colorAddr = ((uint32_t) colors) + (((dy * height) + dx) * sizeof(uint16_t));
	DMA2DOptions options = HAL_DMA2D_DFMT_RGB565 | HAL_DMA2D_SFMT_RGB565;

#else
#error No se especifico el formato de color del sistema
#endif

	uint32_t addr = getPixelAddr(x, y);

	halDMA2DStartCopy(
		addr,
		width,
		height,
		_lineWidth - width,
		options,
		colorAddr,
	    pitch);

	halDMA2DWaitForFinish();
}
