#ifndef __eosColor__
#define __eosColor__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColorMath.h"


// Defineix el color del sistema
//
#ifndef EOS_COLOR_FORMAT
#define EOS_COLOR_FORMAT ColorFormat::argb8888
#endif

#define ARGB(a, r, g, b)          fromARGB<EOS_COLOR_FORMAT>(a, r, g, b)
#define RGB(r, g, b)              fromRGB<EOS_COLOR_FORMAT>(r, g, b)
#define AL(a, l)                  fromAL<EOS_COLOR_FORMAT>(a, l)
#define PAL(l)                    fromL<EOS_COLOR_FORMAT>(l);


namespace eos {

	/// \brief Format de color
	/// \remarks Hi han dos opcions de color RGB o Luminancia
	///
	enum class ColorFormat: uint8_t {
		argb8888,  ///< A8 + R8 + G8 + B8   (32 bits ARGB)
		rgb888,    ///< R8 + G8 + B8        (24 bits RGB)
		argb4444,  ///< A4 + R4 + G4 + B4   (16 bits ARGB)
		argb1555,  ///< A1 + R5 + G5 + B5   (16 bits ARGB)
		rgb565,    ///< R5 + G6 + B5        (16 bits RGB)
		al88,      ///< A8 + L8             (16 bits AL)
		al44,      ///< A4 + L4             (8 bits AL)
		l8,        ///< L8                  (8 bits L)
		l1         ///< L1                  (1 bit L)
	};


	/// \brief Informacio sobre els formats de color
	///
	template <ColorFormat FORMAT>
	struct ColorTrait {
	};

	template <>
	struct ColorTrait<ColorFormat::argb8888> {
		using Pixel = uint32_t;
		static constexpr ColorFormat format = ColorFormat::argb8888;
		static constexpr int bits = 32;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = true;
		static constexpr bool hasAlpha = true;
		static constexpr unsigned maskA = 0xFF000000;
		static constexpr unsigned maskR = 0x00FF0000;
		static constexpr unsigned maskG = 0x0000FF00;
		static constexpr unsigned maskB = 0x000000FF;
		static constexpr unsigned maskL = 0x00000000;
		static constexpr unsigned shiftA = 24;
		static constexpr unsigned shiftR = 16;
		static constexpr unsigned shiftG = 8;
		static constexpr unsigned shiftB = 0;
		static constexpr unsigned shiftL = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjR = 0;
		static constexpr unsigned adjG = 0;
		static constexpr unsigned adjB = 0;
		static constexpr unsigned adjL = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::argb4444> {
		using Pixel = uint16_t;
		static constexpr ColorFormat format = ColorFormat::argb4444;
		static constexpr int bits = 16;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = true;
		static constexpr bool hasAlpha = true;
		static constexpr unsigned maskA = 0xF000;
		static constexpr unsigned maskR = 0x0F00;
		static constexpr unsigned maskG = 0x00F0;
		static constexpr unsigned maskB = 0x000F;
		static constexpr unsigned shiftA = 12;
		static constexpr unsigned shiftR = 8;
		static constexpr unsigned shiftG = 4;
		static constexpr unsigned shiftB = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjR = 0;
		static constexpr unsigned adjG = 0;
		static constexpr unsigned adjB = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::argb1555> {
		using Pixel = uint16_t;
		static constexpr ColorFormat format = ColorFormat::argb1555;
		static constexpr int bits = 16;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = true;
		static constexpr bool hasAlpha = true;
		static constexpr unsigned maskA = 0x8000;
		static constexpr unsigned maskR = 0x7C00;
		static constexpr unsigned maskG = 0x03E0;
		static constexpr unsigned maskB = 0x001F;
		static constexpr unsigned shiftA = 15;
		static constexpr unsigned shiftR = 10;
		static constexpr unsigned shiftG = 5;
		static constexpr unsigned shiftB = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjR = 0;
		static constexpr unsigned adjG = 0;
		static constexpr unsigned adjB = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::rgb888> {
		using Pixel = uint32_t;
		static constexpr ColorFormat format = ColorFormat::rgb888;
		static constexpr int bits = 24;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = true;
		static constexpr bool hasAlpha = false;
		static constexpr unsigned maskA = 0x000000;
		static constexpr unsigned maskR = 0xFF0000;
		static constexpr unsigned maskG = 0x00FF00;
		static constexpr unsigned maskB = 0x0000FF;
		static constexpr unsigned maskL = 0x000000;
		static constexpr unsigned shiftA = 0;
		static constexpr unsigned shiftR = 16;
		static constexpr unsigned shiftG = 8;
		static constexpr unsigned shiftB = 0;
		static constexpr unsigned shiftL = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjR = 0;
		static constexpr unsigned adjG = 0;
		static constexpr unsigned adjB = 0;
		static constexpr unsigned adjL = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::rgb565> {
		using Pixel = uint16_t;
		static constexpr ColorFormat format = ColorFormat::rgb565;
		static constexpr int bits = 16;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = true;
		static constexpr bool hasAlpha = false;
		static constexpr unsigned maskA = 0x0000;
		static constexpr unsigned maskR = 0xF800;
		static constexpr unsigned maskG = 0x07E0;
		static constexpr unsigned maskB = 0x001F;
		static constexpr unsigned maskL = 0x0000;
		static constexpr unsigned shiftA = 0;
		static constexpr unsigned shiftR = 11;
		static constexpr unsigned shiftG = 5;
		static constexpr unsigned shiftB = 0;
		static constexpr unsigned shiftL = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjR = 3;
		static constexpr unsigned adjG = 2;
		static constexpr unsigned adjB = 3;
		static constexpr unsigned adjL = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::al88> {
		using Pixel = uint16_t;
		static constexpr ColorFormat format = ColorFormat::al88;
		static constexpr int bits = 16;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = false;
		static constexpr bool hasAlpha = true;
		static constexpr unsigned maskA = 0xFF00;
		static constexpr unsigned maskR = 0x0000;
		static constexpr unsigned maskG = 0x0000;
		static constexpr unsigned maskB = 0x0000;
		static constexpr unsigned maskL = 0x00FF;
		static constexpr unsigned shiftA = 8;
		static constexpr unsigned shiftR = 0;
		static constexpr unsigned shiftG = 0;
		static constexpr unsigned shiftB = 0;
		static constexpr unsigned shiftL = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjR = 0;
		static constexpr unsigned adjG = 0;
		static constexpr unsigned adjB = 0;
		static constexpr unsigned adjL = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::al44> {
		using Pixel = uint8_t;
		static constexpr ColorFormat format = ColorFormat::al44;
		static constexpr int bits = 8;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = false;
		static constexpr bool hasAlpha = true;
		static constexpr unsigned maskA = 0xF0;
		static constexpr unsigned maskR = 0x00;
		static constexpr unsigned maskG = 0x00;
		static constexpr unsigned maskB = 0x00;
		static constexpr unsigned maskL = 0x0F;
		static constexpr unsigned shiftA = 4;
		static constexpr unsigned shiftR = 0;
		static constexpr unsigned shiftG = 0;
		static constexpr unsigned shiftB = 0;
		static constexpr unsigned shiftL = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjR = 0;
		static constexpr unsigned adjG = 0;
		static constexpr unsigned adjB = 0;
		static constexpr unsigned adjL = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::l8> {
		using Pixel = uint8_t;
		static constexpr ColorFormat format = ColorFormat::l8;
		static constexpr int bits = 8;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = false;
		static constexpr bool hasAlpha = false;
		static constexpr unsigned maskA = 0x00;
		static constexpr unsigned maskR = 0x00;
		static constexpr unsigned maskG = 0x00;
		static constexpr unsigned maskB = 0x00;
		static constexpr unsigned maskL = 0xFF;
		static constexpr unsigned shiftA = 0;
		static constexpr unsigned shiftR = 0;
		static constexpr unsigned shiftG = 0;
		static constexpr unsigned shiftB = 0;
		static constexpr unsigned shiftL = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjR = 0;
		static constexpr unsigned adjG = 0;
		static constexpr unsigned adjB = 0;
		static constexpr unsigned adjL = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::l1> {
		using Pixel = uint8_t;
		static constexpr ColorFormat format = ColorFormat::l1;
		static constexpr int bits = 1;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = false;
		static constexpr bool hasAlpha = false;
		static constexpr unsigned maskL = 0;
		static constexpr unsigned shiftL = 0;
		static constexpr unsigned adjL = 0;
	};

	template <ColorFormat format_>
	class Color_x {
		private:
			using CT = ColorTrait<format_>;

		public:
			using Pixel = typename CT::Pixel;

			static constexpr ColorFormat format = format_;
			static constexpr int bits = CT::bits;
			static constexpr int bytes = CT::bytes;
			static constexpr int colors = CT::colors;
			static constexpr bool hasAlpha = CT::hasAlpha;
			static constexpr bool isColor = CT::isColor;
			static constexpr bool isIndex = !CT::isColor;

		private:
			Pixel _pixel;

		public:
			// \brief Contructor.
			// \remarks Defineix color negre amb 0% d'opacitat.
			//
			inline constexpr Color_x() :
				_pixel(0) {
			}

			/// \brief Constructor
			/// \param c: Color en format nadiu.
			///
			inline constexpr Color_x(
				Pixel pixel) :

				_pixel(pixel) {
			}

			/// \brief Constructor copia
			/// \param color: la instancia a copiar.
			///
			inline constexpr Color_x(
				const Color_x &color):
				_pixel(color._pixel) {
			}

			/// \brief Operador d'asignacio.
			/// \param color: El color a asignar.
			///
			inline Color_x &operator = (
				const Color_x &color) {

            	_pixel = color._pixel;
            	return *this;
            }

			/// \brief Operador ==
			/// \param color: El color a comparar.
			///
            inline bool operator == (
            	const Color_x color) const {

            	return _pixel == color._pixel;
            }

            /// \brief Operador !=
            /// \param colcor: El colcor a comparar.
            ///
            inline bool operator != (
            	const Color_x color) const {

            	return _pixel != color._pixel;
            }

            /// \brief Operador de canvi de tipus.
            /// \return El valor convertit a tipus Pixel
            ///
            inline operator Pixel() const {

            	return _pixel;
            }

            /// \brief Obte el valor del canal ALPHA
            /// \return El valor.
            ///
            inline uint8_t getA() const {

            	if constexpr (CT::hasAlpha)
            		return (_pixel & CT::maskA) >> CT::shiftA << CT::adjA;
            	else
            		return 0xFF;
            }

            /// \brief Obte el valor del index de color.
            /// \return El valor.
            ///
            inline uint8_t getL() const {

            	if constexpr (CT::isColor)
            		return 0xFF;
            	else
            		return (_pixel & CT::maskL) >> CT::shiftL << CT::adjL;
            }

            /// \brief Obte el valor del canal R
            /// \return El valor.
            ///
            inline uint8_t getR() const {

            	if constexpr (CT::isColor)
           			return (_pixel & CT::maskR) >> CT::shiftR << CT::adjR;
            	else
            		return getL();
            }

            /// \brief Obte el valor del canal G
            /// \return El valor.
            ///
            inline uint8_t getG() const {

            	if constexpr (CT::isColor)
            		return (_pixel & CT::maskG) >> CT::shiftG << CT::adjG;
            	else
            		return getL();
            }

            /// \brief Obte el valor del canal B
            /// \return El valor.
            ///
            inline uint8_t getB() const {

            	if constexpr (CT::isColor)
            		return (_pixel & CT::maskB) >> CT::shiftB << CT::adjB;
            	else
            		return getL();
            }

            /// \brief Obte el valor de la opacitat.
            /// \return El valor.
            ///
            inline uint8_t getOpacity() const {

            	return getA();
            }

            /// \brief Indica si es transparent.
            /// \return True si es transparent.
            ///
            inline bool isTransparent() const {

            	return getA() == 0;
            }

            /// \brief Indica si es opac.
            /// \param True si es opac.
            ///
            inline bool isOpaque() const {

            	return getA() == 0xFF;
            }

            template <ColorFormat newFormat_>
            Color_x<newFormat_> convert() {

            	using NewCT = ColorTrait<newFormat_>;
            	using NewColor = Color_x<newFormat_>;

            	if constexpr (NewCT::isColor) {
            		if constexpr (NewCT::hasAlpha)
            			return NewColor::fromARGB(getA(), getR(), getG(), getB());
            		else
            			return NewColor::fromRGB(getR(), getG(), getB());
            	}
            	else {
            		if constexpr (NewCT::hasAlpha)
            			return NewColor::fromAL(getA(), getL());
            		else
            			return NewColor::fromL(getL());
            	}
            }
	};

	using ColorARGB8888 = Color_x<ColorFormat::argb8888>;
	using ColorRGB888 = Color_x<ColorFormat::rgb888>;
	using ColorRGB565 = Color_x<ColorFormat::rgb565>;
	using ColorL8 = Color_x<ColorFormat::l8>;
	using ColorL1 = Color_x<ColorFormat::l1>;
	using Color = Color_x<EOS_COLOR_FORMAT>;

	template <ColorFormat format_>
	constexpr Color_x<format_> fromAL(uint8_t, uint8_t);

	/// \brief Construeix un color a partir dels components ARGB
	/// \param a: Component ALPHA.
	/// \param r: Component R.
	/// \param g: Component G.
	/// \param b: Component B.
	/// \return El color.
	///
	template <ColorFormat format_>
	constexpr Color_x<format_> fromARGB(
		uint8_t a,
		uint8_t r,
		uint8_t g,
		uint8_t b) {

		using CT = ColorTrait<format_>;
		using Pixel = typename CT::Pixel;

		if constexpr (CT::isColor) {
			if constexpr (CT::hasAlpha)
				return Color_x<format_>(
					((Pixel)a >> CT::adjA << CT::shiftA) |
					((Pixel)r >> CT::adjR << CT::shiftR) |
					((Pixel)g >> CT::adjG << CT::shiftG) |
					((Pixel)b >> CT::adjB << CT::shiftB));
			else
				return Color_x<format_>(
					((Pixel)r >> CT::adjR << CT::shiftR) |
					((Pixel)g >> CT::adjG << CT::shiftG) |
					((Pixel)b >> CT::adjB << CT::shiftB));
		}
		else
			fromAL<format_>(a, 0);
	}

	/// \brief Construeix un color a partir dels components RGB
	/// \param r: Component R.
	/// \param g: Component G.
	/// \param b: Component B.
	/// \return El color.
	///
	template <ColorFormat format_>
	constexpr Color_x<format_> fromRGB(
		uint8_t r,
		uint8_t g,
		uint8_t b) {

		return fromARGB<format_>(0xFF, r, g, b);
	}

	/// \brief Construeix un color a partir dels components AL
	/// \param a: Component ALPHA.
	/// \param l: Component L
	/// \return El color.
	///
	template <ColorFormat format_>
	constexpr Color_x<format_> fromAL(
		uint8_t a,
		uint8_t l) {

		using CT = ColorTrait<format_>;
		using Pixel = typename CT::Pixel;

		if constexpr (CT::isColor)
			return fromARGB<format_>(a, l, l, l);
		else {
			if constexpr (CT::hasAlpha)
				return Color_x<format_>(
					((Pixel)a >> CT::adjA << CT::shiftA) |
					((Pixel)l >> CT::adjL << CT::shiftL));
			else
				return Color_x<format_>(
					(Pixel)l >> CT::adjL << CT::shiftL);
		}
	};

	/// \brief Construeix un color a partir dels components L
	/// \param l: Component L
	/// \return El color.
	///
	template <ColorFormat format_>
	constexpr Color_x<format_> fromL(
		uint8_t l) {

		return fromAL<format_>(0xFF, l);
	}

	/// \brief Clase que representa la paleta de colors.
    ///
    class ColorPalette {
        private:
            Color colorTable[256];

        public:
            ColorPalette();

            inline Color getColor(uint8_t index) const {
            	return colorTable[index];
            }

            inline const Color* getTable() const {
            	return colorTable;
            }

            void setColor(uint8_t index, Color color);
    };
}


#endif // __eosColor__
