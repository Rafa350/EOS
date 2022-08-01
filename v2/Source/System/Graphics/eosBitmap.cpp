#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosGraphics.h"
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
	const void* bitmapResource):

	_impl(makeImpl()) {

	uint8_t* r = (uint8_t*) bitmapResource;

	_impl->allocated = false;
	_impl->readonly = true;
	_impl->width = (int) (r[0] | (r[1] << 8));
	_impl->height = (int) (r[2] | (r[3] << 8));
	_impl->format = ColorFormat::rgb565; // TODO: Corregir aixo
	_impl->pixels = (void*) &r[6];
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

	_impl(makeImpl()) {

	_impl->width = width;
	_impl->height= height;
	_impl->format= format;
	_impl->allocated = true;
	_impl->readonly = false;
	_impl->pixels = nullptr;

	// Calcula el numero de pixels
	//
	int numPixels = width * height;
	eosAssert(numPixels > 0);

	// Calcula el tamany de cada pixel
	//
	int pixelSize = 0;
	switch (format) {
		case ColorFormat::rgb565:
			pixelSize = ColorTrait<ColorFormat::rgb565>::bytes;
			break;

		case ColorFormat::rgb888:
			pixelSize = ColorTrait<ColorFormat::rgb888>::bytes;
			break;

		default:
		case ColorFormat::argb8888:
			pixelSize = ColorTrait<ColorFormat::argb8888>::bytes;
			break;

		case ColorFormat::l8:
			pixelSize = ColorTrait<ColorFormat::l8>::bytes;
			break;
	}
	eosAssert(pixelSize != 0);

	// Reserva memoria pel bitmap
	//
	_impl->pixels = osalHeapAlloc(NULL, numPixels * pixelSize);
	eosAssert(_impl->pixels != nullptr);

	// Crea el contingut del bitmap
	//
/*	switch (format) {
		case ColorFormat::rgb888: {
			ColorInfo<ColorFormat::rgb888>::color_t c = color.convertTo<ColorFormat::rgb888>();
			for (int i = 0; i < numPixels; i++)
				((ColorInfo<ColorFormat::rgb888>::color_t*)_impl->pixels)[i] = c;
		}
		break;

		case ColorFormat::rgb565: {
			ColorInfo<ColorFormat::rgb565>::color_t c = color.convertTo<ColorFormat::rgb565>();
			for (int i = 0; i < numPixels; i++)
				((ColorInfo<ColorFormat::rgb565>::color_t*)_impl->pixels)[i] = c;
		}
		break;

		default:
		case ColorFormat::argb8888: {
			ColorInfo<ColorFormat::argb8888>::color_t c = color.convertTo<ColorFormat::argb8888>();
			for (int i = 0; i < numPixels; i++)
				((ColorInfo<ColorFormat::argb8888>::color_t*)_impl->pixels)[i] = c;
		}
		break;

		case ColorFormat::l8: {
			ColorInfo<ColorFormat::l8>::color_t c = color.convertTo<ColorFormat::l8>();
			for (int i = 0; i < numPixels; i++)
				((ColorInfo<ColorFormat::l8>::color_t*)_impl->pixels)[i] = c;
		}
		break;

	}*/
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
	void* pixels):

	_impl(makeImpl()) {

	_impl->width = width;
	_impl->height = height;
	_impl->format = format;
	_impl->allocated = false;
	_impl->readonly = false;
	_impl->pixels = pixels;
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
	const void* pixels):

	_impl(makeImpl()) {

	_impl->width = width;
	_impl->height = height;
	_impl->format = format;
	_impl->allocated = false;
	_impl->readonly = true;
	_impl->pixels = (void*) pixels;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia
/// \param    bitmap: L'altre objecte per copiar.
///
Bitmap::Bitmap(
	const Bitmap& bitmap):

	_impl(bitmap._impl) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte
///
Bitmap::~Bitmap() {

	if (_impl->allocated && (_impl->pixels != nullptr))
		osalHeapFree(NULL, _impl->pixels);
}


/// ----------------------------------------------------------------------
/// \brief    Crea l'estructura interna de dades.
/// \param    Punter a l'estructura.
///
Bitmap::ImplPtr Bitmap::makeImpl() {

	return ImplPtr(new Impl);
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'assignacio.
/// \param    bitmap: L'objecte a asignar.
/// \return   El propi objecte.
///
Bitmap& Bitmap::operator = (
	const Bitmap& bitmap) {

	_impl = bitmap._impl;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el format del bitmap.
/// \param    El valor.
///
ColorFormat Bitmap::getFormat() const {

	return _impl->format;
}


int Bitmap::getWidth() const {

	return _impl->width;
}


int Bitmap::getHeight() const {

	return _impl->height;
}


void* Bitmap::getPixels() const {

	return _impl->pixels;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de bytes per pixel.
/// \return   El valor.
///
int Bitmap::getBytesPerPixel() const {

	switch (_impl->format) {
		default:
		case ColorFormat::rgb888:
			return ColorTrait<ColorFormat::rgb888>::bytes;

		case ColorFormat::argb8888:
			return ColorTrait<ColorFormat::argb8888>::bytes;

		case ColorFormat::rgb565:
			return ColorTrait<ColorFormat::rgb565>::bytes;

		case ColorFormat::al44:
			return ColorTrait<ColorFormat::al44>::bytes;

		case ColorFormat::l8:
			return ColorTrait<ColorFormat::l8>::bytes;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de bytes per linia.
/// \return   El valor.
///
int Bitmap::getBytesPerLine() const {

	return ((_impl->width * getBytesPerPixel()) + 3) & ~0b11;
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa el bitmap
/// \param    graphics: L'objecte grafics per dibuixar.
/// \param    position: La posicio.
///
void Bitmap::draw(
	const Graphics* graphics,
	const Point& position) const {

}

