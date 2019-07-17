#include "eos.h"
#include "HAL/STM32/halDMA2D.h"
#include "System/Graphics/eosMemoryDrawSurface.h"


using namespace eos;



/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    buffer: Buffer de memoria.
/// \param    width: Amplada en pixels.
/// \param    height: Alçada en pixels.
/// \param    format: Format de pixels.
///
void MemoryDrawSurcace::MemoryDrawSurface(
    uint8_t *buffer,
    int width,
    int height,
    PixelFormat format):

    buffer(buffer),  
    bufferWidth(width),
    bufferHeight(height),
    pixFormat(format) {
    
	switch (format) {
		case PixelFormat::rgb565:
			pixSize = sizeof(uint16_t);
			break;

		default:
		case PixelFormat::rgb888:
		case PixelFormat::argb8888:
			pixSize = sizeof(uint32_t);
			break;
	}
}



/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    color: Color del pixel.
///
void MemoryDrawSurcace::setPixel(
	int x,
	int y,
	const Color &color) {

	if ((x >= 0) && (x < bufferWidth) && (y >= 0) && (y < bufferHeight)) {
        
        int offset = ((bufferWidth * y) + x) * pixSize);
        switch (format) {
            case PixelFormat::rgb565:
                (uint16_t*)(buffer + offset) = c.torgb565();
                break;
                
            default:
                break;
        }
	}
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels horitzontals.
/// \param    x: Coordinada X.
/// \param    y: Colordinada Y.
/// \param    length: Longitut de la linia.
/// \param    color: Color dels pixels.
///
void MemoryDrawSurface::setHPixels(
	int x,
	int y,
	int size,
	const Color &color) {

	setPixels(x, y, size, 1, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia de pixels en vertical.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    length: Longitut de la linia.
/// \param    color: Color dels pixels.
///
void MermoryDrawSurface::setVPixels(
	int x,
	int y,
	int size,
	const Color &color) {

	setPixels(x, y, 1, size, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una regio rectangular de pixels.
/// \param    x: Posicio X.
/// \param    y: Posicio Y.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    color: Color dels pixels.
///
void MemoryDrawSurface::setPixels(
	int x,
	int y,
	int width,
	int height,
	const Color &color) {

	int x1 = x;
	int y1 = y;
	int x2 = x + width - 1;
	int y2 = y + height - 1;

	// Retalla al tamany de pantalla
	//
	x1 = Math::max(x1, 0);
	y1 = Math::max(y1, 0);
	x2 = Math::min(x2, screenWidth - 1);
	y2 = Math::min(y2, screenHeight - 1);

	// Cas que nomes sigui un pixel
	//
	if ((x1 == x2) && (y1 == y2)) {
		put(x1, y1, toPixel(color));
	}

	// Cas que hagi una regio rectangular per dibuixar
	//
	else if ((x1 <= x2) && (y1 <= y2)) {
		fill(x1, y1, x2 - x1 + 1, y2 - y1 + 1, toPixel(color));
	}
}


/// ----------------------------------------------------------------------
/// \brief Escriu una regio rectangular de pixels.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    pixels: Els pixels a copiar.
/// \param    format: Format dels pixels.
/// \param    dx: Offset X dins del bitmap.
/// \param    dy: offset Y dins del vitmap.
/// \param    pitch: Aplada de linia del bitmap.
///
void MemoryDrawSurface::writePixels(
	int x,
	int y,
	int width,
	int height,
	const uint8_t *pixels,
	PixelFormat format,
	int dx,
	int dy,
	int pitch) {

	// Comprova si es dins dels limits
	//
	if ((x >= 0) && (x + width <= screenWidth) &&
		(y >= 0) && (y + height <= screenHeight) &&
		(width > 0) && (height > 0)) {

		copy(x, y, width, height, pixels, format, dx, dy, pitch);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix una regio rectangular de pixels.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    pixels: Buffer de pixels.
/// \param    format: Format de pixels.
///
void MemoryDrawSurface::readPixels(
	int x,
	int y,
	int width,
	int height,
	uint8_t *pixels,
	PixelFormat format,
	int dc,
	int dy,
	int pitch) {

}


/// ----------------------------------------------------------------------
/// \brief Realitza un scroll vertical
///
void MemoryDrawSurface::vScroll(
	int x,
	int y,
	int width,
	int height,
    int delta) {

}


/// ----------------------------------------------------------------------
/// \brief Realitza un scroll horitzontal.
///
void MemoryDrawSurface::hScroll(
	int x,
	int y,
	int width,
	int height,
    int delta) {

}

