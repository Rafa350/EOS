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


void MonoFrameBuffer::put(
	int x,
	int y,
	Color color) {

	uint8_t* p = (uint8_t*)((int)_buffer + ((y >> 3) * getImageWidth()) + x);
	if (color)
		*p = *p | (1 << (y & 3));
	else
		*p = *p & ~(1 << (y & 3));
}

void MonoFrameBuffer::fill(
	int x,
	int y,
	int width,
	int height,
	Color color) {

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
