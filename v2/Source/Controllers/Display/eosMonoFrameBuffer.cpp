#include "eos.h"
#include "Controllers/Display/eosMonoFrameBuffer.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    frameWidth: Amplada de la imatge.
/// \param    frameHeight: Alçada de la imatge.
/// \param    orientation: Orientacio.
/// \param    buffer: El buffer de memoria.
///
MonoFrameBuffer::MonoFrameBuffer(
	int frameWidth,
	int frameHeight,
	DisplayOrientation orientation,
	void* buffer,
	int bufferPitch):

	FrameBuffer(frameWidth, frameHeight, orientation),
	_buffer(reinterpret_cast<uint8_t*>(buffer)),
	_bufferPitch(bufferPitch) {
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un pixel en la posicio indicada.
/// \param    x: Coordinada x de la posicio
/// \param    y: Coordinada y de la posicio
/// \param    color: Color del pixel.
///
void MonoFrameBuffer::put(
	int x,
	int y,
	Color color) {

	uint8_t *page = &_buffer[(y >> 3) * getImageWidth()];
	if (color.getL() > 127)
		page[x] |= 1 << (y & 7);
	else
		page[x] &= ~(1 << (y & 7));
}


void MonoFrameBuffer::fill(
	int x,
	int y,
	int width,
	int height,
	Color color) {

	for (int yy = y; yy < y + height; yy++)
		for (int xx = x; xx < x + width; xx++)
			put(xx, yy, color);

}


void MonoFrameBuffer::copy(
	int x,
	int y,
	int width,
	int height,
	const Color *colors,
	int colorPitch) {

}

void MonoFrameBuffer::copy(
	int x,
	int y,
	int width,
	int height,
	const void *color,
	ColorFormat colorFormat,
	int colorPitch) {

}
