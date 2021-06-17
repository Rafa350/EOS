#include "eos.h"
#include "Controllers/Display/eosFrameBuffer_RGB565_DMA2D.h"
#include "HAL/STM32/halDMA2D.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorMath.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    frameWidth: Amplada fisica en pixels.
/// \param    frameHeight: Alçada fisica en pixels.
/// \param    orientation: Orientacio inicial.
/// \param    buffer: Buffer d'imatge.
/// \remarks  S'ajusta l'amplada per ser multiple de 64 bytes, aixo permet
///           optimitzar les transferencies de DMA2D
///
FrameBuffer_RGB565_DMA2D::FrameBuffer_RGB565_DMA2D(
	int frameWidth,
	int frameHeight,
	DisplayOrientation orientation,
	void* buffer):

	FrameBuffer(frameWidth, frameHeight, orientation),
	_buffer(buffer),
	_lineWidth((((frameWidth * sizeof(uint16_t)) + 63) & 0xFFFFFFC0) / sizeof(uint16_t)) {

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
	const Color& color) {

	uint8_t opacity = color.getOpacity();
	if (opacity != 0) {
		uint16_t c = color.toRGB565();
		uint16_t* p = (uint16_t*) getPixelAddr(x, y);
	    *p = opacity == 0xFF ? c : ColorMath::combineColor_RGB565(*p, c, opacity);
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
/// \param    colors: Llista de pixels.
/// \param    dx: Offset x dins del bitmap.
/// \param    dy: Offset y dins del bitmap.
/// \param    pitch: Offset a la seguent linia del bitmap. 0 si son consecutives.
///
void FrameBuffer_RGB565_DMA2D::copy(
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
