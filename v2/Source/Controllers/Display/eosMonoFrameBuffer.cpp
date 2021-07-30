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
	_buffer(buffer),
	_bufferPitch(bufferPitch) {
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un pixel en lña posicio indicada.
/// \param    x: Coordinada x de la posicio
/// \param    y: Coordinada y de la posicio
/// \param    color: Colord el pixel.
///
void MonoFrameBuffer::put(
	int x,
	int y,
	Color color) {

	ColorBase<ColorFormat::l1> c = color.convertTo<ColorFormat::l1>();

	uint8_t* page = (uint8_t*)((int)_buffer + ((y >> 3) * getImageWidth()));
	if (c)
		page[x] = page[x] | (1 << (y & 7));
	else
		page[x] = page[x] & ~(1 << (y & 7));
}


void MonoFrameBuffer::fill(
	int x,
	int y,
	int width,
	int height,
	Color color) {

	//memset(_buffer, 0x00, 128 * 8);

	// Pendent d'optimitzar
	for (int yy = y; yy < y + height; yy++)
		for (int xx = x; xx < x + width; xx++)
			put(xx, yy, color);

}


void MonoFrameBuffer::copy(
	int x,
	int y,
	int width,
	int height,
	const Color* colors,
	int offset) {

}

void MonoFrameBuffer::write(
	int x,
	int y,
	int width,
	int height,
	const void* pixels,
	ColorFormat format,
	int offset) {

}
