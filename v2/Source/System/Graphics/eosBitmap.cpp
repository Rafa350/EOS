#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosBitmap.h"
#include "OSAL/osalHeap.h"


using namespace eos;


class Bitmap::Impl: public PoolAllocatable<Bitmap::Impl, eosGraphics_MaxBitmaps> {
	public:
		int width;
		int height;
		ColorFormat format;
		bool allocated;
		bool readonly;
		void *pixels;
};


/// ----------------------------------------------------------------------
/// \brief    Crea un bitmap des d'un recurs.
/// \param    bitmapResource: El recurs.
///
Bitmap::Bitmap(
	const void *bitmapResource):

	_pImpl(allocate()) {

	uint8_t *r = (uint8_t*) bitmapResource;

	_pImpl->allocated = false;
	_pImpl->readonly = true;
	_pImpl->width = (int) (r[0] | (r[1] << 8));
	_pImpl->height = (int) (r[2] | (r[3] << 8));
	_pImpl->format = ColorFormat::rgb565; // TODO: Corregir aixo
	_pImpl->pixels = (void*) &r[6];
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

	_pImpl(allocate()) {

	_pImpl->width = width;
	_pImpl->height= height;
	_pImpl->format= format;
	_pImpl->allocated = true;
	_pImpl->readonly = false;
	_pImpl->pixels = nullptr;

	// Calcula el numero de pixels
	//
	int numPixels = width * height;
	eosAssert(numPixels > 0);

	// Calcula el tamany de cada pixel
	//
	int pixelSize = 0;
	switch (format) {
		case ColorFormat::rgb565:
			pixelSize = ColorInfo<ColorFormat::rgb565>::bytes;
			break;

		case ColorFormat::rgb888:
			pixelSize = ColorInfo<ColorFormat::rgb888>::bytes;
			break;

		default:
		case ColorFormat::argb8888:
			pixelSize = ColorInfo<ColorFormat::argb8888>::bytes;
			break;

		case ColorFormat::l8:
			pixelSize = ColorInfo<ColorFormat::l8>::bytes;
			break;
	}
	eosAssert(pixelSize != 0);

	// Reserva memoria pel bitmap
	//
	_pImpl->pixels = osalHeapAlloc(NULL, numPixels * pixelSize);
	eosAssert(_pixels != nullptr);

	// Crea el contingut del bitmap
	//
	switch (format) {
		case ColorFormat::rgb888: {
			ColorInfo<ColorFormat::rgb888>::color_t c = color.convertTo<ColorFormat::rgb888>();
			for (int i = 0; i < numPixels; i++)
				((ColorInfo<ColorFormat::rgb888>::color_t*)_pImpl->pixels)[i] = c;
		}
		break;

		case ColorFormat::rgb565: {
			ColorInfo<ColorFormat::rgb565>::color_t c = color.convertTo<ColorFormat::rgb565>();
			for (int i = 0; i < numPixels; i++)
				((ColorInfo<ColorFormat::rgb565>::color_t*)_pImpl->pixels)[i] = c;
		}
		break;

		default:
		case ColorFormat::argb8888: {
			ColorInfo<ColorFormat::argb8888>::color_t c = color.convertTo<ColorFormat::argb8888>();
			for (int i = 0; i < numPixels; i++)
				((ColorInfo<ColorFormat::argb8888>::color_t*)_pImpl->pixels)[i] = c;
		}
		break;

		case ColorFormat::l8: {
			ColorInfo<ColorFormat::l8>::color_t c = color.convertTo<ColorFormat::l8>();
			for (int i = 0; i < numPixels; i++)
				((ColorInfo<ColorFormat::l8>::color_t*)_pixels)[i] = c;
		}
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

	_pImpl(allocate()) {

	_pImpl->width = width;
	_pImpl->height = height;
	_pImpl->format = format;
	_pImpl->allocated = false;
	_pImpl->readonly = false;
	_pImpl->pixels = pixels;
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

	_pImpl(allocate()) {

	_pImpl->width = width;
	_pImpl->height = height;
	_pImpl->format = format;
	_pImpl->allocated = false;
	_pImpl->readonly = true;
	_pImpl->pixels = (void*) pixels;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia
/// \param    bitmap: L'altre objecte per copiar.
///
Bitmap::Bitmap(
	const Bitmap& bitmap):

	_pImpl(bitmap._pImpl) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte
///
Bitmap::~Bitmap() {

	if (_pImpl->allocated && (_pImpl->pixels != nullptr))
		osalHeapFree(NULL, _pImpl->pixels);
}


/// ----------------------------------------------------------------------
/// \brief    Crea l'estructura interna de dades.
/// \param    Punter a l'estructura.
///
Bitmap::PImpl Bitmap::allocate() {

	return PImpl(new Impl);
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'assignacio.
/// \param    bitmap: L'objecte a asignar.
/// \return   El propi objecte.
///
Bitmap& Bitmap::operator = (
	const Bitmap& bitmap) {

	_pImpl = bitmap._pImpl;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de bytes per pixel.
/// \return   El valor.
///
int Bitmap::getBytesPerPixel() const {

	switch (_pImpl->format) {
		default:
		case ColorFormat::rgb888:
		case ColorFormat::argb8888:
			return sizeof(uint32_t);

		case ColorFormat::rgb565:
			return sizeof(uint16_t);

		case ColorFormat::l8:
			return sizeof(uint8_t);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de bytes per linia.
/// \return   El valor.
///
int Bitmap::getBytesPerLine() const {

	return ((_pImpl->width * getBytesPerPixel()) + 3) & ~0b11;
}
