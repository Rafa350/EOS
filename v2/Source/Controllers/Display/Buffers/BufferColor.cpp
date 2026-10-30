export module Eos.Controllers.Display.Buffers.Color;

import Eos.Controllers.Display;
import Eos.System.Graphics.Color;
import Eos.Types;


export namespace eos {

	class DisplayBuffer_Color: public DisplayBuffer {
		private:
			Color::Pixel * const _buffer;
			Int16 const _framePitch;

		protected:
            void put(Int16 x, Int16 y, Color color) override;
            void fill(Int16 x, Int16 y, Int16 width, Int16 height, Color color) override;
            void copy(Int16 x, Int16 y, Int16 width, Int16 height, const Color *colors, Int16 colorPitch) override;
            void copy(Int16 x, Int16 y, Int16 width, Int16 height, const void *colors, ColorFormat colorFormat, Int16 colorPitch) override;

		public:
			DisplayBuffer_Color(Int16 frameWidth, Int16 frameHeight, Int16 framePitch, Orientation orientation, UInt8 *buffer);
	};
}


using namespace eos;


static UInt16 combinePixel(UInt16 b, UInt16 f, UInt8 o);


static inline Color::Pixel *getPixelPtr(
	Color::Pixel *buffer,
	Int16 bufferPitch,
	Int16 x,
	Int16 y) {

	return &buffer[(y * bufferPitch) + x];
}


DisplayBuffer_Color::DisplayBuffer_Color(
	Int16 frameWidth,
	Int16 frameHeight,
	Int16 framePitch,
	Orientation orientation,
	UInt8 *buffer):

	DisplayBuffer(frameWidth, frameHeight, orientation),
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
void DisplayBuffer_Color::put(
	Int16 x,
	Int16 y,
	const Color color) {

	UInt8 opacity = color.getOpacity();
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
void DisplayBuffer_Color::fill(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	Color color) {

	Color::Pixel c = color;
	UInt8 opacity = color.getOpacity();

	if (opacity != 0) {

		if (opacity == 0xFF) {
			for (Int16 yy = y; yy < height + y; yy++) {
				Color::Pixel *ptr = getPixelPtr(_buffer, _framePitch, x, yy);
				for (Int16 xx = x; xx < width + x; xx++) {
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
static UInt16 combinePixel(
	UInt16 b,
	UInt16 f,
	UInt8 o) {

	UInt8 br = (b & COLOR_RGB565_MASK_R) >> COLOR_RGB565_SHIFT_R;
	UInt8 bg = (b & COLOR_RGB565_MASK_G) >> COLOR_RGB565_SHIFT_G;
	UInt8 bb = (b & COLOR_RGB565_MASK_B) >> COLOR_RGB565_SHIFT_B;

	UInt8 fr = (f & COLOR_RGB565_MASK_R) >> COLOR_RGB565_SHIFT_R;
	UInt8 fg = (f & COLOR_RGB565_MASK_G) >> COLOR_RGB565_SHIFT_G;
	UInt8 fb = (f & COLOR_RGB565_MASK_B) >> COLOR_RGB565_SHIFT_B;

	return (UInt16)
		((((fr * o) + (br * (255u - o))) >> 8) << COLOR_RGB565_SHIFT_R) |
		((((fg * o) + (bg * (255u - o))) >> 8) << COLOR_RGB565_SHIFT_G) |
		((((fb * o) + (bb * (255u - o))) >> 8) << COLOR_RGB565_SHIFT_B);
}
*/
