#include "eos.h"
#include "Controllers/Display/eosColorFrameBuffer.h"


using namespace eos;


static uint16_t combinePixel(uint16_t b, uint16_t f, uint8_t o);



ColorFrameBuffer::ColorFrameBuffer(
	int screenWidth,
	int screenHeight,
	DisplayOrientation orientation,
	void* buffer,
	int bufferPitch):

	FrameBuffer(screenWidth, screenHeight, orientation),
	_buffer(buffer),
	_bufferPitch(bufferPitsh) {

}


/// ----------------------------------------------------------------------
/// \brief Asigna un color a un pixel.
/// \param x: Coordinada X del pixel.
/// \param y: Coordinada Y del pixel.
/// \param color: Color en format de pixel fisic;
/// \remarks No es fa cap tipus de verificacio dels parametres.
///
void ColorFrameBuffer::put(
	int x,
	int y,
	const Color& color) {

	uint8_t opacity = color.getOpacity();
	if (opacity != 0) {
		uint16_t c = color.toRGB565();
		uint16_t* p = (uint16_t*)(_buffer + (y * lineBytes) + (x * sizeof(uint16_t)));
	    *p = opacity == 0xFF ? c : combinePixel(*p, c, opacity);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Assigna un color a una regio.
/// \param    x: Coordinada X.
/// \param    y: Coordinada y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    color: Color.-
///
void ColorFrameBuffer::fill(
	int x,
	int y,
	int width,
	int height,
	Color color) {

	for (int yy = 0; yy < height; yy++)
		for (int xx = 0; xx < width; xx++)
			put(x + xx, y + yy, color);
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
