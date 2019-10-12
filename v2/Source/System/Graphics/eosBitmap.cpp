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

	allocated(false),
	readonly(true) {

	width = (int) (bitmapResource[0] | (bitmapResource[1] << 8));
	height = (int) (bitmapResource[2] | (bitmapResource[3] << 8));
	format = ColorFormat::rgb565;
	pixels = (uint8_t*) &bitmapResource[6];
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param width: Amplada en pixels.
/// \param height: Alçada en pixels.
/// \param color: Color inicial
///
Bitmap::Bitmap(
	int width,
	int height,
	ColorFormat format,
	const Color &color):

	width(width),
	height(height),
	format(format),
	allocated(true),
	readonly(false),
	pixels(nullptr) {

	// Calcula el numero de pixels
	//
	int numPixels = width * height;

	// Calcula el tamany de cada pixel
	//
	int pixelSize;
	switch (format) {
		case ColorFormat::rgb565:
			pixelSize = sizeof(uint16_t);
			break;

		default:
		case ColorFormat::rgb888:
		case ColorFormat::argb8888:
			pixelSize = sizeof(uint32_t);
			break;
	}

	// Reserva memoria pel bitmap
	//
	pixels = (uint8_t*) osalHeapAlloc(NULL, numPixels * pixelSize);

	// Crea el contingut del bitmap
	//
	switch (format) {
		case ColorFormat::rgb888:
			for (int i = 0; i < numPixels; i++)
				((uint32_t*)pixels)[i] = color.toRGB888();
		break;

		case ColorFormat::rgb565:
			for (int i = 0; i < numPixels; i++)
				((uint16_t*)pixels)[i] = color.toRGB565();
		break;

		default:
		case ColorFormat::argb8888:
			for (int i = 0; i < numPixels; i++)
				((uint32_t*)pixels)[i] = color.toARGB8888();
		break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param width: Amplada en pixels.
/// \param height: Al�ada en pixels.
/// \param format: Format de pixels
/// \param pixels: Llista de pixels
///
Bitmap::Bitmap(
	int width,
	int height,
	ColorFormat format,
	uint8_t *pixels):

	width(width),
	height(height),
	format(format),
	allocated(false),
	readonly(false),
	pixels(pixels) {
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte bitmap no modificable.
/// \param width: Amplada en pixels.
/// \param height: Al�ada en pixels.
/// \param format: Format de pixels
/// \param pixels: Llista de pixels nomes de lectura.
///
Bitmap::Bitmap(
	int width,
	int height,
	ColorFormat format,
	const uint8_t *pixels):

	width(width),
	height(height),
	format(format),
	allocated(false),
	readonly(true),
	pixels((uint8_t*)pixels) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte
///
Bitmap::~Bitmap() {

	if (allocated && (pixels != nullptr))
		osalHeapFree(NULL, pixels);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de bytes per pixel.
/// \return   El valor.
///
int Bitmap::getBytesPerPixel() const {

	switch (format) {
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

	return ((width * getBytesPerPixel()) + 3) & ~0b11;
}

