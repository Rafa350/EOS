#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosBitmap.h"
#include "OSAL/osalMemory.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param width: Amplada en pixels.
/// \param height: Alçada en pixels.
/// \param color: Color inicial
///
Bitmap::Bitmap(
	int width,
	int height,
	PixelFormat format,
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
		case PixelFormat::rgb565:
			pixelSize = sizeof(uint16_t);
			break;

		default:
		case PixelFormat::rgb888:
		case PixelFormat::argb8888:
			pixelSize = sizeof(uint32_t);
			break;
	}

	// Reserva memorial pel bitmap
	//
	pixels = (uint8_t*) osalMemoryAlloc(numPixels * pixelSize);

	// Crea el contingut del bitmap
	//
	switch (format) {
		case PixelFormat::rgb888:
			for (int i = 0; i < numPixels; i++)
				((uint32_t*)pixels)[i] = color.toRGB888();
		break;

		case PixelFormat::rgb565:
			for (int i = 0; i < numPixels; i++)
				((uint16_t*)pixels)[i] = color.toRGB565();
		break;

		default:
		case PixelFormat::argb8888:
			for (int i = 0; i < numPixels; i++)
				((uint32_t*)pixels)[i] = color.toARGB8888();
		break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param width: Amplada en pixels.
/// \param height: Alçada en pixels.
/// \param format: Format de pixels
/// \param pixels: Llista de pixels
///
Bitmap::Bitmap(
	int width,
	int height,
	PixelFormat format,
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
/// \param height: Alçada en pixels.
/// \param format: Format de pixels
/// \param pixels: Llista de pixels nomes de lectura.
///
Bitmap::Bitmap(
	int width,
	int height,
	PixelFormat format,
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

	if (allocated & (pixels != nullptr))
		osalMemoryFree(pixels);
}
