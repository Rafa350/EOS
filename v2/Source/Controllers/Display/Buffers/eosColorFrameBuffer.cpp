module;


#include "eos.h"


export module Eos.Controllers.Display.Buffers.Color;


export import Eos.Controllers.Display.Buffers;


import Eos.System.Graphics.Color;


export namespace eos {


	class ColorFrameBuffer: public FrameBuffer {
		private:
			Color::Pixel * const _buffer;
			int16_t const _framePitch;

		protected:
            void put(int16_t x, int16_t y, Color color) override;
            void fill(int16_t x, int16_t y, int16_t width, int16_t height, Color color) override;
            void copy(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t colorPitch) override;
            void copy(int16_t x, int16_t y, int16_t width, int16_t height, const void *colors, ColorFormat colorFormat, int16_t colorPitch) override;

		public:
			ColorFrameBuffer(int16_t frameWidth, int16_t frameHeight, int16_t framePitch, Orientation orientation, uint8_t *buffer);
	};
}


static uint16_t combinePixel(uint16_t b, uint16_t f, uint8_t o);


static inline eos::Color::Pixel *getPixelPtr(
	eos::Color::Pixel *buffer,
	int bufferPitch,
	int x,
	int y) {

	return &buffer[(y * bufferPitch) + x];
}


eos::ColorFrameBuffer::ColorFrameBuffer(
	int16_t frameWidth,
	int16_t frameHeight,
	int16_t framePitch,
	Orientation orientation,
	uint8_t *buffer):

	FrameBuffer(frameWidth, frameHeight, orientation),
	_buffer(reinterpret_cast<Color::Pixel*>(buffer)),
	_framePitch(framePitch) {
}


/// ----------------------------------------------------------------------
/// \brief Asigna un color a un pixel.
/// \param x: Coordinada X del pixel.
/// \param y: Coordinada Y del pixel.
/// \param color: Color en format de pixel fisic;
/// \remarks No es fa cap tipus de verificacio dels parametres.
///
void eos::ColorFrameBuffer::put(
	int16_t x,
	int16_t y,
	const Color color) {

	uint8_t opacity = color.getOpacity();
	if (opacity != 0) {

		Color::Pixel c = color;
		Color::Pixel *ptr = getPixelPtr(_buffer, _framePitch, x, y);

		*ptr = c; // opacity == 0xFF ? c : combinePixels(c, *ptr, opacity);
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
void eos::ColorFrameBuffer::fill(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	Color color) {

	Color::Pixel c = color;
	uint8_t opacity = color.getOpacity();

	if (opacity != 0) {

		if (opacity == 0xFF) {
			for (int yy = y; yy < height + y; yy++) {
				Color::Pixel *ptr = getPixelPtr(_buffer, _framePitch, x, yy);
				for (int xx = x; xx < width + x; xx++) {
					*ptr = c; // opacity == 0xFF ? c : combinePixels(c, *ptr, opacity);
					ptr++;
				}
			}
		}
		else {
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief Compbina dos pixels.
/// \param b: Pixel del fons.
/// \param f: Pixel del primer pla.
/// \param o: Opacitat.
/// \return El valor del pixel combinat.
///
/*
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
*/
