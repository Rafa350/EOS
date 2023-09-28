#include "eos.h"
#include "Controllers/Display/eosMonoFrameBuffer.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    frameWidth: Amplada.
/// \param    frameHeight: Alçada.
/// \param    framePitch: El pitch
/// \param    orientation: Orientacio.
/// \param    buffer: El buffer de memoria.
///
MonoFrameBuffer::MonoFrameBuffer(
	int16_t frameWidth,
	int16_t frameHeight,
	int16_t framePitch,
	DisplayOrientation orientation,
	uint8_t *buffer):

	FrameBuffer(frameWidth, frameHeight, orientation),
	_buffer {reinterpret_cast<uint8_t*>(buffer)},
	_framePitch {framePitch} {
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

	uint8_t *page = &_buffer[(y >> 3) * getWidth()];
	if (color.getL() > 127)
		page[x] |= 1 << (y & 7);    // L>127 -> Color blanc
	else
		page[x] &= ~(1 << (y & 7)); // L<128 -> Color negre
}


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
