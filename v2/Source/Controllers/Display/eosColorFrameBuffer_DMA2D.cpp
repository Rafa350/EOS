#include "eos.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HTL/STM32/htlDMA2D.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorMath.h"


#ifndef HTL_DMA2D_EXIST
#error "DMA2D hardware unavailable"
#endif


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Combina dos pixels amb opacitat.
/// \param    fg: El pixel a combinar.
/// \param    bg: El pixel de fons.
/// \param    opascity: Opacitat del pixel fg.
/// \return   El pixel combinat.
///
static Color::Pixel combinePixels(
	Color::Pixel fg,
	Color::Pixel bg,
	uint8_t opacity) {

	using CT = ColorTrait<Color::format>;

	uint32_t fgR = (fg & CT::maskR) >> CT::shiftR;
	uint32_t fgG = (fg & CT::maskG) >> CT::shiftG;
	uint32_t fgB = (fg & CT::maskB) >> CT::shiftB;

	uint32_t bgR = (bg & CT::maskR) >> CT::shiftR;
	uint32_t bgG = (bg & CT::maskG) >> CT::shiftG;
	uint32_t bgB = (bg & CT::maskB) >> CT::shiftB;

	Color::Pixel c =
		((((fgR * opacity) + (bgR * (255 - opacity))) >> 8) << CT::shiftR) |
		((((fgG * opacity) + (bgG * (255 - opacity))) >> 8) << CT::shiftG) |
		((((fgB * opacity) + (bgB * (255 - opacity))) >> 8) << CT::shiftB);

	if constexpr (CT::hasAlpha)
		c |= 0xFF << CT::shiftA;

	return c;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el format de color es suportat pel DMA2D
/// \param    format: El format de color.
/// \return   True si esta suportat.
///
static constexpr bool isOutputColorSupported(
	ColorFormat format) {

	return
		(format == ColorFormat::argb8888) ||
		(format == ColorFormat::argb4444) ||
		(format == ColorFormat::argb1555) ||
		(format == ColorFormat::rgb888) ||
		(format == ColorFormat::rgb565);
}


/// ----------------------------------------------------------------------
/// \brief    Obte l modus de color de sortida pel DMA2D.
/// \param    format: El format de color.
/// \return   El modus de color.
///
static constexpr dma2d::OutputColorMode getOutputColorMode(
	ColorFormat format) {

	switch (format) {
		default:
		case ColorFormat::argb8888:
			return dma2d::OutputColorMode::argb8888;

		case ColorFormat::argb4444:
			return dma2d::OutputColorMode::argb4444;

		case ColorFormat::argb1555:
			return dma2d::OutputColorMode::argb1555;

		case ColorFormat::rgb888:
			return dma2d::OutputColorMode::rgb888;

		case ColorFormat::rgb565:
			return dma2d::OutputColorMode::rgb565;
	}
}


static constexpr dma2d::InputColorMode getInputColorMode(
	ColorFormat format) {

	switch (format) {
		default:
		case ColorFormat::argb8888:
			return dma2d::InputColorMode::argb8888;

		case ColorFormat::argb4444:
			return dma2d::InputColorMode::argb4444;

		case ColorFormat::argb1555:
			return dma2d::InputColorMode::argb1555;

		case ColorFormat::rgb888:
			return dma2d::InputColorMode::rgb888;

		case ColorFormat::rgb565:
			return dma2d::InputColorMode::rgb565;

		case ColorFormat::al88:
			return dma2d::InputColorMode::al88;

		case ColorFormat::al44:
			return dma2d::InputColorMode::al44;

		case ColorFormat::l8:
			return dma2d::InputColorMode::l8;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    pitch: Pitch.
/// \param    orientation: Orientacio.
/// \param    color: Color inicial.
/// \param    buffer: Buffer.
///
ColorFrameBuffer_DMA2D::ColorFrameBuffer_DMA2D(
	int16_t width,
	int16_t height,
	int16_t pitch,
	DisplayOrientation orientation,
	void *buffer):

	FrameBuffer(width, height, orientation),
	_buffer(reinterpret_cast<Color::Pixel*>(buffer)),
	_framePitch(pitch) {

    htl::dma2d::DMA2DDevice::pInst->initialize();
}


/// ----------------------------------------------------------------------
/// \brief    Obter l'adresa del buffer d'imatge.
/// \return   L'adressa.
///
uint8_t *ColorFrameBuffer_DMA2D::getBuffer() const {

	return (uint8_t*) _buffer;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un color a un pixel de la pantalla.
/// \param    x: Coordinada x del pixel.
/// \param    y: Coordinada y del pixel.
/// \param    color: Color.
/// \remarks  No es fa cap tipus de verificacio dels parametres.
///
void ColorFrameBuffer_DMA2D::put(
	int16_t x,
	int16_t y,
	Color color) {

	// Color amb opacitat (Canal alpha)
	//
	if constexpr (Color::hasAlpha) {

		// Nomes el pinta si no es transparent
		//
		uint8_t opacity = color.getOpacity();
		if (opacity != 0) {

			Color::Pixel c = color;
			Color::Pixel *ptr = getPixelPtr(x, y);

			*ptr = opacity == 0xFF ? c : combinePixels(c, *ptr, opacity);
		}
	}

	// Color sense opacitat
	//
	else {

		Color::Pixel c = color;
		Color::Pixel *ptr = getPixelPtr(x, y);

		*ptr = c;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Ompla amb un color, una regio de la pantalla.
/// \param    x: Coordinada x de la regio.
/// \param    y: Coordinada y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    color: Color.
///
void ColorFrameBuffer_DMA2D::fill(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	Color color) {

	uint8_t opacity = color.getOpacity();

	// Comprova si es un color solid
	//
	if (opacity == 0xFF) {

		// Si esta suportat, utilitza el DMA2D
		//
		if constexpr (isOutputColorSupported(Color::format)) {
			Color::Pixel *ptr = getPixelPtr(x, y);
			dma2d::OutputColorMode dstColorMode = getOutputColorMode(Color::format);
			Color::Pixel c = color;
			_devDMA2D->startFill(ptr, width, height, _framePitch, dstColorMode, c);
			_devDMA2D->waitForFinish();
		}

		// En cas contrari realitza una transferencia per software
		//
		else {
			Color::Pixel c = color;
			for (int16_t yy = y; yy < height + y; yy++) {
				Color::Pixel *ptr = getPixelPtr(x, yy);
				for (int16_t xx = x; xx < width + x; xx++)
					*ptr++ = c;
			}
		}
	}

	// En cas contrari, relitza una transferencia per software.
	//
	else if (opacity != 0) {

		Color::Pixel c = color;

		for (int16_t yy = y; yy < height + y; yy++) {
			Color::Pixel *ptr = getPixelPtr(x, yy);
			for (int16_t xx = x; xx < width + x; xx++) {
				*ptr = combinePixels(c, *ptr, opacity);
				ptr++;
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Copia una llista de colors a una regio de la pantalla.
/// \param    x: Coordinada x de la regio.
/// \param    y: Coordinada y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    colors: Llista de colors.
/// \param    colorPitch: Pitch de la llista de colors.
///
void ColorFrameBuffer_DMA2D::copy(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color *colors,
	int16_t colorPitch) {

	// Si es un color solid i suportat pel modul DMA2D, realitza la transferencia
	// per hardware.
	//
	if (isOutputColorSupported(Color::format)) {

		Color::Pixel *ptr = getPixelPtr(x, y);

		// Rellena la regio amb el valor de color dels pixels. Aquesta funcio
		// Converteix el format de pixels gracies als parametres DFMT i SFMT de
		// les opcions.
		//
		dma2d::OutputColorMode dstColorMode = getOutputColorMode(Color::format);
		dma2d::InputColorMode srcColorMode = getInputColorMode(Color::format);
		_devDMA2D->startCopy(ptr, width, height, _framePitch, dstColorMode, colors, colorPitch, srcColorMode);
		_devDMA2D->waitForFinish();
	}

	// En cas contrari realitza la transferencia per software.
	//
	else {
	}
}


/// ----------------------------------------------------------------------
/// \brief    Copia una llista de colors a una regio de la pantalla.
/// \param    x: Coordinada x de la regio.
/// \param    y: Coordinada y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    colors: Llista de colors.
/// \param    colorFormat: Format de la llista de colors.
/// \param    colorPitch: Pitch de la llista de colors.
///
void ColorFrameBuffer_DMA2D::copy(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const void *colors,
	ColorFormat colorFormat,
	int16_t colorPitch) {

	// Si es un color solid i suportat pel modul DMA2D, realitza la transferencia
	// per hardware.
	//
	if (isOutputColorSupported(Color::format)) {

		Color::Pixel *ptr = getPixelPtr(x, y);

		// Rellena la regio amb el valor de color dels pixels. Aquesta funcio
		// Converteix el format de pixels gracies als parametres DFMT i SFMT de
		// les opcions. No cal cridar a 'toPixel()'
		//
		dma2d::OutputColorMode dstColorMode = getOutputColorMode(Color::format);
		dma2d::InputColorMode srcColorMode = getInputColorMode(colorFormat);
		_devDMA2D->startCopy(ptr, width, height, _framePitch, dstColorMode, colors, colorPitch, srcColorMode);
		_devDMA2D->waitForFinish();
	}
}
