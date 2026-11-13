export module Eos.Controllers.Display.Buffers.ColorDMA2D;


import Eos.Controllers.Display;
import Eos.Hardware.DMA2D;
import Eos.System.Graphics.Color;
import Eos.Types;


using namespace eos;
using namespace eos::hardware::dma2d;


export namespace eos {

	/// @brief Superficie de dibuix basada en memoria ram
	///
	class DisplayBuffer_ColorDMA2D final: public DisplayBuffer {
	    private:
			DMA2DDevice * const _devDMA2D;
			Color::Pixel * const _buffer;
			Int16 const _framePitch;

		private:
			inline Color::Pixel *getPixelPtr(Int16 x, Int16 y) const { return &_buffer[(y * _framePitch) + x]; }

		protected:
			void put(Int16 x, Int16 y, Color color) override;
            void fill(Int16 x, Int16 y, Int16 width, Int16 height, Color color) override;
            void copy(Int16 x, Int16 y, Int16 width, Int16 height, const Color *colors, Int16 colorPitch) override;
            void copy(Int16 x, Int16 y, Int16 width, Int16 height, const void *colors, ColorFormat colorFormat, Int16 colorPitch) override;

		public:
			DisplayBuffer_ColorDMA2D(Int16 width, Int16 height, Int16 pitch, Orientation orientation, void *buffer);
            UInt8 *getBuffer() const override;
	};
}


/// --------------------------------------------------------------------------------
/// @brief    Combina dos pixels amb opacitat.
/// @param    fg: El pixel a combinar.
/// @param    bg: El pixel de fons.
/// @param    opascity: Opacitat del pixel fg.
/// @return   El pixel combinat.
///
static Color::Pixel combinePixels(
	Color::Pixel fg,
	Color::Pixel bg,
	UInt8 opacity) {

	using CT = ColorTraits<Color::format>;

	UInt32 fgR = (fg & CT::maskR) >> CT::shiftR;
	UInt32 fgG = (fg & CT::maskG) >> CT::shiftG;
	UInt32 fgB = (fg & CT::maskB) >> CT::shiftB;

	UInt32 bgR = (bg & CT::maskR) >> CT::shiftR;
	UInt32 bgG = (bg & CT::maskG) >> CT::shiftG;
	UInt32 bgB = (bg & CT::maskB) >> CT::shiftB;

	Color::Pixel c =
		((((fgR * opacity) + (bgR * (255 - opacity))) >> 8) << CT::shiftR) |
		((((fgG * opacity) + (bgG * (255 - opacity))) >> 8) << CT::shiftG) |
		((((fgB * opacity) + (bgB * (255 - opacity))) >> 8) << CT::shiftB);

	if constexpr (CT::hasAlpha)
		c |= 0xFF << CT::shiftA;

	return c;
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el format de color es suportat pel DMA2D
/// @param    format: El format de color.
/// @return   True si esta suportat.
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


/// ---------------------------------------------------------------------------
/// @brief    Obte l modus de color de sortida pel DMA2D.
/// @param    format: El format de color.
/// @return   El modus de color.
///
static constexpr DMA2DDevice::OutputColorMode getOutputColorMode(
	ColorFormat format) {

	switch (format) {
		default:
		case ColorFormat::argb8888:
			return DMA2DDevice::OutputColorMode::argb8888;

		case ColorFormat::argb4444:
			return DMA2DDevice::OutputColorMode::argb4444;

		case ColorFormat::argb1555:
			return DMA2DDevice::OutputColorMode::argb1555;

		case ColorFormat::rgb888:
			return DMA2DDevice::OutputColorMode::rgb888;

		case ColorFormat::rgb565:
			return DMA2DDevice::OutputColorMode::rgb565;
	}
}


static constexpr DMA2DDevice::InputColorMode getInputColorMode(
	ColorFormat format) {

	switch (format) {
		default:
		case ColorFormat::argb8888:
			return DMA2DDevice::InputColorMode::argb8888;

		case ColorFormat::argb4444:
			return DMA2DDevice::InputColorMode::argb4444;

		case ColorFormat::argb1555:
			return DMA2DDevice::InputColorMode::argb1555;

		case ColorFormat::rgb888:
			return DMA2DDevice::InputColorMode::rgb888;

		case ColorFormat::rgb565:
			return DMA2DDevice::InputColorMode::rgb565;

		case ColorFormat::al88:
			return DMA2DDevice::InputColorMode::al88;

		case ColorFormat::al44:
			return DMA2DDevice::InputColorMode::al44;

		case ColorFormat::l8:
			return DMA2DDevice::InputColorMode::l8;
	}
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor del objecte.
/// @param    frameWidth: Amplada.
/// @param    frameHeight: Alçada.
/// @param    framePitch: Pitch.
/// @param    orientation: Orientacio.
/// @param    color: Color inicial.
/// @param    buffer: Buffer.
///
DisplayBuffer_ColorDMA2D::DisplayBuffer_ColorDMA2D(
	Int16 frameWidth,
	Int16 frameHeight,
	Int16 framePitch,
	Orientation orientation,
	void *buffer):

	DisplayBuffer(frameWidth, frameHeight, orientation),
	_devDMA2D {DMA2DDevice::pInst},
	_buffer {reinterpret_cast<Color::Pixel*>(buffer)},
	_framePitch {framePitch} {

    _devDMA2D->initialize();
}


/// ---------------------------------------------------------------------------
/// @brief    Obter l'adresa del buffer d'imatge.
/// @return   L'adressa.
///
UInt8 *DisplayBuffer_ColorDMA2D::getBuffer() const {

	return (UInt8*) _buffer;
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna un color a un pixel de la pantalla.
/// @param    x: Coordinada x del pixel.
/// @param    y: Coordinada y del pixel.
/// @param    color: Color.
/// @remarks  No es fa cap tipus de verificacio dels parametres.
///
void DisplayBuffer_ColorDMA2D::put(
	Int16 x,
	Int16 y,
	Color color) {

	// Color amb opacitat (Canal alpha)
	//
	if constexpr (Color::hasAlpha) {

		// Nomes el pinta si no es transparent
		//
		UInt8 opacity = color.getOpacity();
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


/// ---------------------------------------------------------------------------
/// @brief    Ompla amb un color, una regio de la pantalla.
/// @param    x: Coordinada x de la regio.
/// @param    y: Coordinada y de la regio.
/// @param    width: Amplada de la regio.
/// @param    height: Alçada de la regio.
/// @param    color: Color.
///
void DisplayBuffer_ColorDMA2D::fill(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	Color color) {

	UInt8 opacity = color.getOpacity();

	// Comprova si es un color solid
	//
	if (opacity == 0xFF) {

		// Si esta suportat, utilitza el DMA2D
		//
		if constexpr (isOutputColorSupported(Color::format)) {
			Color::Pixel *ptr = getPixelPtr(x, y);
			auto dstColorMode = getOutputColorMode(Color::format);
			Color::Pixel c = color;
			_devDMA2D->startFill(ptr, width, height, _framePitch, dstColorMode, c);
			_devDMA2D->waitForFinish();
		}

		// En cas contrari realitza una transferencia per software
		//
		else {
			Color::Pixel c = color;
			for (Int16 yy = y; yy < height + y; yy++) {
				Color::Pixel *ptr = getPixelPtr(x, yy);
				for (Int16 xx = x; xx < width + x; xx++)
					*ptr++ = c;
			}
		}
	}

	// En cas contrari, relitza una transferencia per software.
	//
	else if (opacity != 0) {

		Color::Pixel c = color;

		for (Int16 yy = y; yy < height + y; yy++) {
			Color::Pixel *ptr = getPixelPtr(x, yy);
			for (Int16 xx = x; xx < width + x; xx++) {
				*ptr = combinePixels(c, *ptr, opacity);
				ptr++;
			}
		}
	}
}


/// ---------------------------------------------------------------------------
/// @brief    Copia una llista de colors a una regio de la pantalla.
/// @param    x: Coordinada x de la regio.
/// @param    y: Coordinada y de la regio.
/// @param    width: Amplada de la regio.
/// @param    height: Alçada de la regio.
/// @param    colors: Llista de colors.
/// @param    colorPitch: Pitch de la llista de colors.
///
void DisplayBuffer_ColorDMA2D::copy(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	const Color *colors,
	Int16 colorPitch) {

	// Si es un color solid i suportat pel modul DMA2D, realitza la transferencia
	// per hardware.
	//
	if (isOutputColorSupported(Color::format)) {

		Color::Pixel *ptr = getPixelPtr(x, y);

		// Rellena la regio amb el valor de color dels pixels. Aquesta funcio
		// Converteix el format de pixels gracies als parametres DFMT i SFMT de
		// les opcions.
		//
		auto dstColorMode = getOutputColorMode(Color::format);
		auto srcColorMode = getInputColorMode(Color::format);
		_devDMA2D->startCopy(ptr, width, height, _framePitch, dstColorMode, colors, colorPitch, srcColorMode);
		_devDMA2D->waitForFinish();
	}

	// En cas contrari realitza la transferencia per software.
	//
	else {
	}
}


/// ---------------------------------------------------------------------------
/// @brief    Copia una llista de colors a una regio de la pantalla.
/// @param    x: Coordinada x de la regio.
/// @param    y: Coordinada y de la regio.
/// @param    width: Amplada de la regio.
/// @param    height: Alçada de la regio.
/// @param    colors: Llista de colors.
/// @param    colorFormat: Format de la llista de colors.
/// @param    colorPitch: Pitch de la llista de colors.
///
void DisplayBuffer_ColorDMA2D::copy(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	const void *colors,
	ColorFormat colorFormat,
	Int16 colorPitch) {

	// Si es un color solid i suportat pel modul DMA2D, realitza la transferencia
	// per hardware.
	//
	if (isOutputColorSupported(Color::format)) {

		Color::Pixel *ptr = getPixelPtr(x, y);

		// Rellena la regio amb el valor de color dels pixels. Aquesta funcio
		// Converteix el format de pixels gracies als parametres DFMT i SFMT de
		// les opcions. No cal cridar a 'toPixel()'
		//
		auto dstColorMode = getOutputColorMode(Color::format);
		auto srcColorMode = getInputColorMode(colorFormat);
		_devDMA2D->startCopy(ptr, width, height, _framePitch, dstColorMode, colors, colorPitch, srcColorMode);
		_devDMA2D->waitForFinish();
	}
}
