#include "eos.h"
#include "Controllers/Display/eosL4FrameBuffer.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    frameWidth: Amplada en pixels
/// \param    frameHeight: Alçada en pixels
/// \param    orientation: Orientacio.
/// \param    buffer: El buffer de memoria.
/// \param    bufferPitch: Amplada en bytes de cada scanline.
///
eos::L4FrameBuffer::L4FrameBuffer(
    int16_t frameWidth,
    int16_t frameHeight,
    DisplayOrientation orientation,
    uint8_t *buffer,
    int16_t bufferPitch):

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
void eos::L4FrameBuffer::put(
	int16_t x,
	int16_t y,
	Color color) {

	uint8_t *byte = _buffer + (y * _bufferPitch) + (x >> 1);

	if (x & 1)
		*byte = (*byte & 0xF0) | color.getL();
	else
		*byte = (*byte & 0x0F) | (color.getL() << 4);
}


/// ----------------------------------------------------------------------
/// \brief    Ompla una regio amb el color indicat.
/// \param    x: Coordinada X de la posisio de la regio.
/// \param    y: Coordinada y de la posicio de la regio
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    color: Color.
///
void eos::L4FrameBuffer::fill(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	Color color) {

	for (int16_t yy = y; yy < y + height; yy++)
		for (int16_t xx = x; xx < x + width; xx++)
			put(xx, yy, color);

}


void eos::L4FrameBuffer::copy(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color *colors,
	int16_t colorPitch) {

}


void eos::L4FrameBuffer::copy(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const void *color,
	ColorFormat colorFormat,
	int16_t colorPitch) {

}
