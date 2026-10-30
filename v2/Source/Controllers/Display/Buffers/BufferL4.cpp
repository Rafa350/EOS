export module Eos.Controllers.Display.Buffers.L4;

import Eos.Controllers.Display;
import Eos.System.Graphics.Color;
import Eos.Types;


export namespace eos {

    class DisplayBuffer_L4 final: public DisplayBuffer {
        private:
            UInt8 * const _buffer;
            Int16 const _bufferPitch;

		protected:
            void put(Int16 x, Int16 y, Color color) override;
            void fill(Int16 x, Int16 y, Int16 width, Int16 height, Color color) override;
            void copy(Int16 x, Int16 y, Int16 width, Int16 height, const Color *colors, Int16 colorPitch) override;
            void copy(Int16 x, Int16 y, Int16 width, Int16 height, const void *colors, ColorFormat colorFormat, Int16 colorPitch) override;

        public:
            DisplayBuffer_L4(Int16 frameWidth, Int16 frameHeight, Orientation orientation, UInt8 *buffer, Int16 bufferPitch);

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
DisplayBuffer_L4::DisplayBuffer_L4(
    Int16 frameWidth,
    Int16 frameHeight,
    Orientation orientation,
    UInt8 *buffer,
    Int16 bufferPitch):

    FrameBuffer(frameWidth, frameHeight, orientation),
    _buffer {buffer},
    _bufferPitch {bufferPitch} {
}


/// ---------------------------------------------------------------------------
/// @brief    Escriu un pixel en la posicio indicada.
/// @param    x: Coordinada x de la posicio
/// @param    y: Coordinada y de la posicio
/// @param    color: Color del pixel.
///
void DisplayBuffer_L4::put(
	Int16 x,
	Int16 y,
	Color color) {

	UInt8 *byte = _buffer + (y * _bufferPitch) + (x >> 1);

	if (x & 1)
		*byte = (*byte & 0xF0) | color.getL();
	else
		*byte = (*byte & 0x0F) | (color.getL() << 4);
}


/// ---------------------------------------------------------------------------
/// @brief    Ompla una regio amb el color indicat.
/// @param    x: Coordinada X de la posisio de la regio.
/// @param    y: Coordinada y de la posicio de la regio
/// @param    width: Amplada de la regio.
/// @param    height: Alçada de la regio.
/// @param    color: Color.
///
void DisplayBuffer_L4::fill(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	Color color) {

	for (UInt16 yy = y; yy < y + height; yy++)
		for (UInt16 xx = x; xx < x + width; xx++)
			put(xx, yy, color);

}


void DisplayBuffer_L4::copy(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	const Color *colors,
	Int16 colorPitch) {

}


void DisplayBuffer_L4::copy(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	const void *color,
	ColorFormat colorFormat,
	Int16 colorPitch) {

}
