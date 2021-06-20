#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosBitmap.h"
#include "OSAL/osalHeap.h"


using namespace eos;



/// ----------------------------------------------------------------------
/// \brief    Crea un bitmap des d'un recurs.
/// \param    bitmapResource: El recurs.
///
Bitmap::Bitmap(
	const uint8_t *bitmapResource):

	_allocated(false),
	_readonly(true) {

	_width = (int) (bitmapResource[0] | (bitmapResource[1] << 8));
	_height = (int) (bitmapResource[2] | (bitmapResource[3] << 8));
	_format = ColorFormat::rgb565;
	_pixels = (void*) &bitmapResource[6];
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    width: Amplada en pixels.
/// \param    height: Alçada en pixels.
/// \param    color: Color inicial
///
Bitmap::Bitmap(
	int width,
	int height,
	ColorFormat format,
	Color color):

	_width(width),
	_height(height),
	_format(format),
	_allocated(true),
	_readonly(false),
	_pixels(nullptr) {

	// Calcula el numero de pixels
	//
	int numPixels = width * height;

	// Calcula el tamany de cada pixel
	//
	int pixelSize;
	switch (format) {
		default:
		case ColorFormat::rgb565:
			pixelSize = ColorInfo<ColorFormat::rgb565>::bytes;
			break;

		case ColorFormat::rgb888:
			pixelSize = ColorInfo<ColorFormat::rgb888>::bytes;
			break;

		case ColorFormat::argb8888:
			pixelSize = ColorInfo<ColorFormat::argb8888>::bytes;
			break;
	}

	// Reserva memoria pel bitmap
	//
	_pixels = osalHeapAlloc(NULL, numPixels * pixelSize);

	// Crea el contingut del bitmap
	//
	switch (format) {
		case ColorFormat::rgb888:
			for (int i = 0; i < numPixels; i++)
				((uint32_t*)_pixels)[i] = ConvertTo<ColorFormat::rgb888>(color);
		break;

		case ColorFormat::rgb565:
			for (int i = 0; i < numPixels; i++)
				((uint16_t*)_pixels)[i] = ConvertTo<ColorFormat::rgb565>(color);
		break;

		default:
		case ColorFormat::argb8888:
			for (int i = 0; i < numPixels; i++)
				((uint32_t*)_pixels)[i] = ConvertTo<ColorFormat::argb8888>(color);
		break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    width: Amplada en pixels.
/// \param    height: Al�ada en pixels.
/// \param    format: Format de pixels
/// \param    pixels: Llista de pixels
///
Bitmap::Bitmap(
	int width,
	int height,
	ColorFormat format,
	void *pixels):

	_width(width),
	_height(height),
	_format(format),
	_allocated(false),
	_readonly(false),
	_pixels(pixels) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte bitmap no modificable.
/// \param    width: Amplada en pixels.
/// \param    height: Al�ada en pixels.
/// \param    format: Format de pixels
/// \param    pixels: Llista de pixels nomes de lectura.
///
Bitmap::Bitmap(
	int width,
	int height,
	ColorFormat format,
	const void *pixels):

	_width(width),
	_height(height),
	_format(format),
	_allocated(false),
	_readonly(true),
	_pixels((void*) pixels) {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte
///
Bitmap::~Bitmap() {

	if (_allocated && (_pixels != nullptr))
		osalHeapFree(NULL, _pixels);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de bytes per pixel.
/// \return   El valor.
///
int Bitmap::getBytesPerPixel() const {

	switch (_format) {
		default:
		case ColorFormat::rgb888:
		case ColorFormat::argb8888:
			return sizeof(uint32_t);

		case ColorFormat::rgb565:
			return sizeof(uint16_t);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de bytes per linia.
/// \return   El valor.
///
int Bitmap::getBytesPerLine() const {

	return ((_width * getBytesPerPixel()) + 3) & ~0b11;
}
