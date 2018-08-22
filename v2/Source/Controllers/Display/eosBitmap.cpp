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
	pixels(nullptr) {

	pixels = (Color*) osalMemoryAlloc(width * height * sizeof(Color));
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
	pixels(pixels) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte
///
Bitmap::~Bitmap() {

	if (pixels != nullptr)
		osalMemoryFree(pixels);
}
