export module Eos.Controllers.Display.Buffers.L1;

import Eos.Controllers.Display;
import Eos.System.Graphics.Color;
import Eos.Types;


export namespace eos {

    class DisplayBuffer_L1 final: public DisplayBuffer {
        private:
            UInt8 * const _buffer;
            Int16 const _bufferPitch;

		protected:
            void put(Int16 x, Int16 y, Color color) override;
            void fill(Int16 x, Int16 y, Int16 width, Int16 height, Color color) override;
            void copy(Int16 x, Int16 y, Int16 width, Int16 height, const Color *colors, Int16 colorPitch) override;
            void copy(Int16 x, Int16 y, Int16 width, Int16 height, const void *colors, ColorFormat colorFormat, Int16 colorPitch) override;

        public:
            DisplayBuffer_L1(Int16 frameWidth, Int16 frameHeight, Orientation orientation, UInt8 *buffer, Int16 bufferPitch);

            inline UInt8 *getBuffer() const override { return _buffer; }
            inline Int16 getBufferPitch() const { return _bufferPitch; }
    };

}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    frameWidth: Amplada en pixels
/// @param    frameHeight: Alçada en pixels
/// @param    orientation: Orientacio.
/// @param    buffer: El buffer de memoria.
/// @param    bufferPitch: Amplada en bytes de cada scanline.
///
DisplayBuffer_L1::DisplayBuffer_L1(
    Int16 frameWidth,
    Int16 frameHeight,
    Orientation orientation,
    UInt8 *buffer,
    Int16 bufferPitch):

    DisplayBuffer(frameWidth, frameHeight, orientation),
    _buffer {buffer},
    _bufferPitch {bufferPitch} {
}


/// ---------------------------------------------------------------------------
/// @brief    Escriu un pixel en la posicio indicada.
/// @param    x: Coordinada x de la posicio
/// @param    y: Coordinada y de la posicio
/// @param    color: Color del pixel.
///
void DisplayBuffer_L1::put(
	Int16 x,
	Int16 y,
	Color color) {

	UInt8 *byte = reinterpret_cast<UInt8*>(UInt32(_buffer) + ((y >> 3) * _bufferPitch) + x);
	if (color.getL())
		*byte |= 1 << (y & 7);
	else
		*byte &= ~(1 << (y & 7));
}


/// ---------------------------------------------------------------------------
/// @brief    Ompla una regio amb el color indicat.
/// @param    x: Coordinada X de la posisio de la regio.
/// @param    y: Coordinada y de la posicio de la regio
/// @param    width: Amplada de la regio.
/// @param    height: Alçada de la regio.
/// @param    color: Color.
///
void DisplayBuffer_L1::fill(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	Color color) {

	for (Int16 yy = y; yy < y + height; yy++)
		for (Int16 xx = x; xx < x + width; xx++)
			put(xx, yy, color);

}


void DisplayBuffer_L1::copy(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	const Color *colors,
	Int16 colorPitch) {

}


void DisplayBuffer_L1::copy(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	const void *color,
	ColorFormat colorFormat,
	Int16 colorPitch) {

}
