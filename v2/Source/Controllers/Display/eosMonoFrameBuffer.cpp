#include "eos.h"
#include "Controllers/Display/eosFrameBuffer_L1_PAGECOL.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    frameWidth: Amplada de la imatge.
/// \param    frameHeight: Alçada de la imatge.
/// \param    orientation: Orientacio.
/// \param    buffer: El buffer de memoria.
///
FrameBuffer_L1_PAGECOL::FrameBuffer_L1_PAGECOL(
	int frameWidth,
	int frameHeight,
	DisplayOrientation orientation,
	void* buffer):

	FrameBuffer(frameWidth, frameHeight, orientation),
	_buffer(buffer) {
}


void FrameBuffer_L1_PAGECOL::put(
	int x,
	int y,
	const Color& color) {

	uint8_t* p = (uint8_t*)((int)_buffer + ((y >> 3) * getWidth()) + x);
	if (color)
		*p = *p | (1 << (y & 3));
	else
		*p = *p & ~(1 << (y & 3));
}

void FrameBuffer_L1_PAGECOL::fill(
	int x,
	int y,
	int width,
	int height,
	const Color& color) {

}


void FrameBuffer_L1_PAGECOL::copy(
	int x,
	int y,
	int width,
	int height,
	const Color* colors,
	int dx,
	int dy,
	int pitch) {

}
