#include "eos.h"
#include "Controllers/Display/eosMonoFrameBuffer.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    frameWidth: Amplada en pixels
/// \param    frameHeight: Alçada en pixels
/// \param    orientation: Orientacio.
/// \param    buffer: El buffer de memoria.
/// \param    bufferPitch: Amplada en bytes de cada scanline.
///
MonoFrameBuffer::MonoFrameBuffer(
    int16_t frameWidth,
    int16_t frameHeight,
    DisplayOrientation orientation,
    uint8_t *buffer,
    unsigned bufferPitch):

    FrameBuffer(frameWidth, frameHeight, orientation),
    _buffer {buffer},
    _bufferPitch {bufferPitch} {
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un pixel en la posicio indicada.
/// \param    x: Coordinada x de la posicio
/// \param    y: Coordinada y de la posicio
/// \param    color: Color del pixel.
///
void MonoFrameBuffer::put(
	int16_t x,
	int16_t y,
	Color color) {

	uint8_t *byte = reinterpret_cast<uint8_t*>(uint32_t(_buffer) + ((y >> 3) * _bufferPitch) + x);
	if (color.getL() > 127)
		*byte |= 1 << (y & 7);    // L>127 -> Color blanc
	else
		*byte &= ~(1 << (y & 7)); // L<128 -> Color negre
}


/// ----------------------------------------------------------------------
/// \brief    Ompla una regio amb el color indicat.
/// \param    x: Coordinada X de la posisio de la regio.
/// \param    y: Coordinada y de la posicio de la regio
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    color: Color.
///
void MonoFrameBuffer::fill(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	Color color) {

	for (int16_t yy = y; yy < y + height; yy++)
		for (int16_t xx = x; xx < x + width; xx++)
			put(xx, yy, color);

}


void MonoFrameBuffer::copy(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color *colors,
	int16_t colorPitch) {

}

void MonoFrameBuffer::copy(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const void *color,
	ColorFormat colorFormat,
	int16_t colorPitch) {

}
