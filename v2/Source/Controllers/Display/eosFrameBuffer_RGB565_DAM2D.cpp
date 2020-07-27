#include "eos.h"
#include "Controllers/Display/eosFrameBuffer_RGB565_DMA2D.h"
#include "HAL/STM32/halDMA2D.h"


using namespace eos;


static uint16_t combinePixel(uint16_t b, uint16_t f, uint8_t o);


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

	FrameBuffer(screenWidth, screenHeight, orientation),
	buffer(buffer),
	lineWidth(lineBytes / sizeof(uint16_t)),
	lineBytes(lineBytes) {

    halDMA2DInitialize();
}


/// ----------------------------------------------------------------------
/// \brief Asigna un color a un pixel.
/// \param x: Coordinada X del pixel.
/// \param y: Coordinada Y del pixel.
/// \param color: Color en format de pixel fisic;
/// \remarks No es fa cap tipus de verificacio dels parametres.
///
void RGB565_DMA2D_FrameBuffer::put(
	int x,
	int y,
	const Color& color) {

	uint8_t opacity = color.getOpacity();
	if (opacity != 0) {
		uint16_t c = color.toRGB565();
		uint16_t* p = (uint16_t*)(buffer + ((y * lineWidth) + x) * sizeof(uint16_t));
	    *p = opacity == 0xFF ? c : combinePixel(*p, c, opacity);
	}
}


/// ----------------------------------------------------------------------
/// \brief Ompla amb un color, una regio de la pantalla.
/// \param x: Coordinada x.
/// \param y: Coordinada y.
/// \param width: Amplada del bloc.
/// \param height: Alçada del bloc.
/// \param color: Color.
/// \remarks No es fa cap tipus de verificacio dels parametres.
///
void RGB565_DMA2D_FrameBuffer::fill(
	int x,
	int y,
	int width,
	int height,
	const Color& color) {

	uint8_t opacity = color.getOpacity();
	if (opacity != 0) {

		int addr = (int)buffer + ((y * lineWidth) + x) * sizeof(uint16_t);

		halDMA2DStartFill(
			addr,
			width,
			height,
			lineWidth - width,
			HAL_DMA2D_DFMT_RGB565,
			color.toRGB565());

		halDMA2DWaitForFinish();
	}
	else
		// TODO
		// Crear un buffer d'una linia amb el color
		// Tranferir la linia amb DMA2D
		for (int yy = 0; yy < height; yy++)
			for (int xx = 0; xx < width; xx++)
				put(x + xx, y + yy, color);
}

/// ----------------------------------------------------------------------
/// \brief Copia un bitmap a una regio de la pantalla.
/// \param x: Coordinada X de la posicio.
/// \param y: Coordinada Y de la posicio.
/// \param width: Amplada.
/// \param height: Alçada.
/// \param pixels: Llista de pixels.
/// \param dx: Offset X dins del bitmap.
/// \param dy: offset Y dins del vitmap.
/// \param pitch: Offset a la seguent linia del bitmap. 0 si son consecutives.
///
void RGB565_DMA2D_FrameBuffer::copy(
	int x,
	int y,
	int width,
	int height,
	const uint8_t* pixels,
	int dx,
	int dy,
	int pitch) {

	int addr = (int)buffer + ((y * lineWidth) + x) * sizeof(uint16_t);

	halDMA2DStartCopy(
		addr,
		width,
		height,
		lineWidth - width,
		HAL_DMA2D_DFMT_RGB565,
		((uint32_t) pixels) + (((dy * height) + dx) * sizeof(uint16_t)),
	    pitch);

	halDMA2DWaitForFinish();
}


/// ----------------------------------------------------------------------
/// \brief Compbina dos pixels.
/// \param b: Pixel del fons.
/// \param f: Pixel del primer pla.
/// \param o: Opacitat.
/// \return El valor del pixel combinat.
///
static uint16_t combinePixel(
	uint16_t b,
	uint16_t f,
	uint8_t o) {

	uint8_t br = (b & COLOR_RGB565_MASK_R) >> COLOR_RGB565_SHIFT_R;
	uint8_t bg = (b & COLOR_RGB565_MASK_G) >> COLOR_RGB565_SHIFT_G;
	uint8_t bb = (b & COLOR_RGB565_MASK_B) >> COLOR_RGB565_SHIFT_B;

	uint8_t fr = (f & COLOR_RGB565_MASK_R) >> COLOR_RGB565_SHIFT_R;
	uint8_t fg = (f & COLOR_RGB565_MASK_G) >> COLOR_RGB565_SHIFT_G;
	uint8_t fb = (f & COLOR_RGB565_MASK_B) >> COLOR_RGB565_SHIFT_B;

	return (uint16_t)
		((((fr * o) + (br * (255u - o))) >> 8) << COLOR_RGB565_SHIFT_R) |
		((((fg * o) + (bg * (255u - o))) >> 8) << COLOR_RGB565_SHIFT_G) |
		((((fb * o) + (bb * (255u - o))) >> 8) << COLOR_RGB565_SHIFT_B);
}
