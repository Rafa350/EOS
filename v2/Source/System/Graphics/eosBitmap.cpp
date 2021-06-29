#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosBitmap.h"
#include "OSAL/osalHeap.h"


using namespace eos;


class Bitmap::Impl {
	private:
    	static MemoryPoolAllocator _allocator;

	public:
		int width;
		int height;
		ColorFormat format;
		bool allocated;
		bool readonly;
		void *pixels;

	public:
    	void* operator new(unsigned size);
    	void operator delete(void*p);
};


MemoryPoolAllocator Bitmap::Impl::_allocator(sizeof(Bitmap::Impl), eosGraphics_MaxBitmaps);


/// ----------------------------------------------------------------------
/// \brief    Operador new
/// \param    size: Tamany del bloc.
/// \return   El bloc.
///
void* Bitmap::Impl::operator new(
	unsigned size) {

	eosAssert(size == sizeof(Bitmap::Impl));

	void* p = Bitmap::Impl::_allocator.allocate();
	eosAssert(p != 0);

	return p;
}


/// ----------------------------------------------------------------------
/// \brief    Operador delete.
/// \param    p: El bloc.
///
void Bitmap::Impl::operator delete(
	void* p) {

	eosAssert(p != nullptr);

	Bitmap::Impl::_allocator.deallocate(p);
}


/// ----------------------------------------------------------------------
/// \brief    Crea un bitmap des d'un recurs.
/// \param    bitmapResource: El recurs.
///
Bitmap::Bitmap(
	const uint8_t *bitmapResource):

	_pImpl(allocate()) {

	_pImpl->allocated =false;
	_pImpl->readonly = true;
	_pImpl->width = (int) (bitmapResource[0] | (bitmapResource[1] << 8));
	_pImpl->height = (int) (bitmapResource[2] | (bitmapResource[3] << 8));
	_pImpl->format = ColorFormat::rgb565;
	_pImpl->pixels = (void*) &bitmapResource[6];
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

		case ColorFormat::l8:
			break;
	}

	// Reserva memoria pel bitmap
	//
	//_pixels = osalHeapAlloc(NULL, numPixels * pixelSize);

	// Crea el contingut del bitmap
	//
	/*switch (format) {
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

		case ColorFormat::l8:
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
