#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosBitmap.h"
#include "OSAL/osalMemory.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param width: Amplada en pixels.
/// \param height: Alçada en pixels.
///
Bitmap::Bitmap(
	int width,
	int height):

	width(width),
	height(height),
	allocated(true),
	pixels(nullptr) {

	int numPixels = width * height;
	pixels = (Color*) osalMemoryAlloc(numPixels * sizeof(Color));
	for (int i = 0; i < numPixels; i++)
		pixels[i] = Color(COLOR_Transparent);
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
	const Color &color):

	width(width),
	height(height),
	allocated(true),
	pixels(nullptr) {

	int numPixels = width * height;
	pixels = (Color*) osalMemoryAlloc(numPixels * sizeof(Color));
	for (int i = 0; i < numPixels; i++)
		pixels[i] = color;
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param width: Amplada en pixels.
/// \param height: Alçada en pixels.
/// \param data: Dades inicial dels bitmap.
///
Bitmap::Bitmap(
	int width,
	int height,
	Color *pixels):

	width(width),
	height(height),
	allocated(false),
	pixels(pixels) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte
///
Bitmap::~Bitmap() {

	if (allocated & (pixels != nullptr))
		osalMemoryFree(pixels);
}
