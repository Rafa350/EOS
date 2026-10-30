module Eos.System.Graphics.Canvas;

import Eos.System.Graphics.Color;
import Eos.System.Core.HeapAllocator;
import Eos.Types;


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Crea un bitmap des d'un recurs.
/// \param    bitmapResource: El recurs.
///
Bitmap::Bitmap(
	const void *bitmapResource):

	_impl(makeImpl()) {

	auto r = (UInt8*) bitmapResource;

	_impl->allocated = false;
	_impl->readonly = true;
	_impl->width = (Int16) (r[0] | (r[1] << 8));
	_impl->height = (Int16) (r[2] | (r[3] << 8));
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
	Int16 width,
	Int16 height,
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
	Int32 numPixels = width * height; // Warning!!!!

	// Calcula el tamany de cada pixel
	//
	Int16 pixelSize = 0;
	switch (format) {
		case ColorFormat::rgb565:
			pixelSize = ColorTraits<ColorFormat::rgb565>::bytes;
			break;

		case ColorFormat::rgb888:
			pixelSize = ColorTraits<ColorFormat::rgb888>::bytes;
			break;

		default:
		case ColorFormat::argb8888:
			pixelSize = ColorTraits<ColorFormat::argb8888>::bytes;
			break;

		case ColorFormat::l8:
			pixelSize = ColorTraits<ColorFormat::l8>::bytes;
			break;
	}

	// Reserva memoria pel bitmap
	//
	_impl->pixels = eos::HeapAllocator::allocate(numPixels * pixelSize);

	// Crea el contingut del bitmap
	//
/*	switch (format) {
		case ColorFormat::rgb888: {
			ColorInfo<ColorFormat::rgb888>::color_t c = color.convertTo<ColorFormat::rgb888>();
			for (Int16 i = 0; i < numPixels; i++)
				((ColorInfo<ColorFormat::rgb888>::color_t*)_impl->pixels)[i] = c;
		}
		break;

		case ColorFormat::rgb565: {
			ColorInfo<ColorFormat::rgb565>::color_t c = color.convertTo<ColorFormat::rgb565>();
			for (Int16 i = 0; i < numPixels; i++)
				((ColorInfo<ColorFormat::rgb565>::color_t*)_impl->pixels)[i] = c;
		}
		break;

		default:
		case ColorFormat::argb8888: {
			ColorInfo<ColorFormat::argb8888>::color_t c = color.convertTo<ColorFormat::argb8888>();
			for (Int16 i = 0; i < numPixels; i++)
				((ColorInfo<ColorFormat::argb8888>::color_t*)_impl->pixels)[i] = c;
		}
		break;

		case ColorFormat::l8: {
			ColorInfo<ColorFormat::l8>::color_t c = color.convertTo<ColorFormat::l8>();
			for (Int16 i = 0; i < numPixels; i++)
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
eos::Bitmap::Bitmap(
	Int16 width,
	Int16 height,
	ColorFormat format,
	void *pixels):

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
eos::Bitmap::Bitmap(
	Int16 width,
	Int16 height,
	ColorFormat format,
	const void *pixels):

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
eos::Bitmap::Bitmap(
	const Bitmap &bitmap):

	_impl(bitmap._impl) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte
///
eos::Bitmap::~Bitmap() {

	if (_impl->allocated && (_impl->pixels != nullptr))
		eos::HeapAllocator::deallocate(_impl->pixels);
}


/// ----------------------------------------------------------------------
/// \brief    Crea l'estructura interna de dades.
/// \param    Punter a l'estructura.
///
eos::Bitmap::ImplPtr eos::Bitmap::makeImpl() {

	return ImplPtr(new Impl);
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'assignacio.
/// \param    bitmap: L'objecte a asignar.
/// \return   El propi objecte.
///
eos::Bitmap& eos::Bitmap::operator = (
	const Bitmap &bitmap) {

	_impl = bitmap._impl;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el format del bitmap.
/// \param    El valor.
///
eos::ColorFormat eos::Bitmap::getFormat() const {

	return _impl->format;
}


Int16 eos::Bitmap::getWidth() const {

	return _impl->width;
}


Int16 eos::Bitmap::getHeight() const {

	return _impl->height;
}


void* eos::Bitmap::getPixels() const {

	return _impl->pixels;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de bytes per pixel.
/// \return   El valor.
///
Int16 eos::Bitmap::getBytesPerPixel() const {

	switch (_impl->format) {
		default:
		case ColorFormat::rgb888:
			return ColorTraits<ColorFormat::rgb888>::bytes;

		case ColorFormat::argb8888:
			return ColorTraits<ColorFormat::argb8888>::bytes;

		case ColorFormat::rgb565:
			return ColorTraits<ColorFormat::rgb565>::bytes;

		case ColorFormat::al44:
			return ColorTraits<ColorFormat::al44>::bytes;

		case ColorFormat::l8:
			return ColorTraits<ColorFormat::l8>::bytes;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de bytes per linia.
/// \return   El valor.
///
Int16 eos::Bitmap::getBytesPerLine() const {

	return ((_impl->width * getBytesPerPixel()) + 3) & ~0b11;
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa el bitmap
/// \param    graphics: L'objecte grafics per dibuixar.
/// \param    position: La posicio.
///
void eos::Bitmap::draw(
	const Graphics *graphics,
	const Point &position) const {

}
