#ifndef __eosColor__
#define __eosColor__


// EOS includes
//
#include "eos.h"


#ifndef EOS_COLOR_FORMAT
#define EOS_COLOR_FORMAT ColorFormat::argb8888
#endif


namespace eos {

	/// \brief Format de color
	///
	enum class ColorFormat: uint8_t {
		argb8888,  ///< ARGB 8 bit channel
		rgb888,    ///< RGB 8 bit channel
		rgb666,    ///< RGB 6 bit channel
		rgb565,    ///< RGB 5 bits Red & Blue channels, 6 bit Green channel
		l8         ///< Luminancia 8 bits
	};


	/// \brief Informacio sobre els formats de color
	///
	template <ColorFormat FORMAT>
	struct ColorInfo {
	};

	template <>
	struct ColorInfo<ColorFormat::argb8888> {
		typedef uint32_t color_t;
		constexpr static ColorFormat format = ColorFormat::argb8888;
		constexpr static const int bits = 32;
		constexpr static const int bytes = (bits + 7) / 8;
		constexpr static const bool isColor = true;
		constexpr static const bool isIndex = false;
		constexpr static const bool hasAlpha = true;
		constexpr static const unsigned maskA = 0xFF000000;
		constexpr static const unsigned maskR = 0x00FF0000;
		constexpr static const unsigned maskG = 0x0000FF00;
		constexpr static const unsigned maskB = 0x000000FF;
		constexpr static const unsigned shiftA = 24;
		constexpr static const unsigned shiftR = 16;
		constexpr static const unsigned shiftG = 8;
		constexpr static const unsigned shiftB = 0;
		constexpr static const unsigned adjA = 0;
		constexpr static const unsigned adjR = 0;
		constexpr static const unsigned adjG = 0;
		constexpr static const unsigned adjB = 0;
	};

	template <>
	struct ColorInfo<ColorFormat::rgb888> {
		typedef uint32_t color_t;
		constexpr static ColorFormat format = ColorFormat::rgb888;
		constexpr static const int bits = 24;
		constexpr static const int bytes = (bits + 7) / 8;
		constexpr static const bool isColor = true;
		constexpr static const bool isIndex = false;
		constexpr static const bool hasAlpha = false;
		constexpr static const unsigned maskA = 0x000000;
		constexpr static const unsigned maskR = 0xFF0000;
		constexpr static const unsigned maskG = 0x00FF00;
		constexpr static const unsigned maskB = 0x0000FF;
		constexpr static const unsigned shiftA = 8 * sizeof(color_t);
		constexpr static const unsigned shiftR = 16;
		constexpr static const unsigned shiftG = 8;
		constexpr static const unsigned shiftB = 0;
		constexpr static const unsigned adjA = 0;
		constexpr static const unsigned adjR = 0;
		constexpr static const unsigned adjG = 0;
		constexpr static const unsigned adjB = 0;
	};

	template <>
	struct ColorInfo<ColorFormat::rgb666> {
		typedef uint32_t color_t;
		constexpr static ColorFormat format = ColorFormat::rgb666;
		constexpr static const int bits = 18;
		constexpr static const int bytes = (bits + 7) / 8;
		constexpr static const bool isColor = true;
		constexpr static const bool isIndex = false;
		constexpr static const bool hasAlpha = false;
		constexpr static const unsigned maskA = 0x00000000;
		constexpr static const unsigned maskR = 0x0003F000;
		constexpr static const unsigned maskG = 0x00000FC0;
		constexpr static const unsigned maskB = 0x0000003F;
		constexpr static const unsigned shiftA = 8 * sizeof(color_t);
		constexpr static const unsigned shiftR = 13;
		constexpr static const unsigned shiftG = 6;
		constexpr static const unsigned shiftB = 0;
		constexpr static const unsigned adjA = 0;
		constexpr static const unsigned adjR = 2;
		constexpr static const unsigned adjG = 2;
		constexpr static const unsigned adjB = 2;
	};

	template <>
	struct ColorInfo<ColorFormat::rgb565> {
		typedef uint16_t color_t;
		constexpr static ColorFormat format = ColorFormat::rgb565;
		constexpr static const int bits = 16;
		constexpr static const int bytes = (bits + 7) / 8;
		constexpr static const bool isColor = true;
		constexpr static const bool isIndex = false;
		constexpr static const bool hasAlpha = false;
		constexpr static const unsigned maskA = 0x0000;
		constexpr static const unsigned maskR = 0xF800;
		constexpr static const unsigned maskG = 0x07E0;
		constexpr static const unsigned maskB = 0x001F;
		constexpr static const unsigned shiftA = 8 * sizeof(color_t);
		constexpr static const unsigned shiftR = 11;
		constexpr static const unsigned shiftG = 5;
		constexpr static const unsigned shiftB = 0;
		constexpr static const unsigned adjA = 0;
		constexpr static const unsigned adjR = 3;
		constexpr static const unsigned adjG = 2;
		constexpr static const unsigned adjB = 3;
	};


	/// \brief Clase que representa un color en el format especificat
	///
	template <ColorFormat FORMAT>
	class ColorBase {
		public:
			typedef ColorInfo<FORMAT> CI;
			typedef typename CI::color_t color_t;

		private:
			color_t _c;

		public:
			/// \brief Constructor per defecte
			///
			inline ColorBase():
				_c(0) {
			}

			/// \brief Constructor de copia
			///
			inline ColorBase(const ColorBase& color):
				_c(color._c) {
			}

			/// \brief Constructor.
			/// \param c: El color en format intern
			///
			inline ColorBase(color_t c):
				_c(c) {
			}

			/// \brief Constructor per compopnents RGB
			/// \param R: Component r
			/// \param G: Component g
			/// \param B: Component b
			///
			inline ColorBase(uint8_t r, uint8_t g, uint8_t b):
				_c((((color_t)r >> CI::adjR << CI::shiftR) & CI::maskR) |
				   (((color_t)g >> CI::adjG << CI::shiftG) & CI::maskG) |
				   (((color_t)b >> CI::adjB << CI::shiftB) & CI::maskB)) {
				if constexpr (CI::hasAlpha)
					_c |= 0xFF >> CI::adjA << CI::shiftA;
			}

			/// \brief Constructor per compopnents ARGB
			/// \param R: Component a
			/// \param R: Component r
			/// \param G: Component g
			/// \param B: Component b
			///
			inline ColorBase(uint8_t a, uint8_t r, uint8_t g, uint8_t b):
				_c(((color_t)r >> CI::adjR << CI::shiftR) |
				   ((color_t)g >> CI::adjG << CI::shiftG) |
				   ((color_t)b >> CI::adjB << CI::shiftB)) {
				if constexpr (CI::hasAlpha)
					_c |= (color_t)a >> CI::adjA << CI::shiftA;
			}

			/// \brief Obte el component A
			/// \return El valor del component A
			///
			inline uint8_t getA() const {
				if constexpr (CI::hasAlpha)
					return (_c & CI::maskA) >> CI::shiftA << CI::adjA;
				else
					return 0xFF;
			}

			/// \brief Obte el component R
			/// \return El valor del component R
			///
			inline uint8_t getR() const {
				return (_c & CI::maskR) >> CI::shiftR << CI::adjR;
			}

			/// \brief Obte el component G
			/// \return El valor del component G
			///
			inline uint8_t getG() const {
				return (_c & CI::maskG) >> CI::shiftG << CI::adjG;
			}

			/// \brief Obte el component B
			/// \return El valor del component B
			///
			inline uint8_t getB() const {
				return (_c & CI::maskB) >> CI::shiftB << CI::adjB;
			}

			/// \brief Obte l'opacitat
			/// \return El valor de la opacitat
			///
            inline uint8_t getOpacity() const {
            	return getA();
            }

            /// \brief Indica si el color es opac
            /// \return True si es opac.

            inline bool isOpaque() const {
            	return getOpacity() == 0xFF;
            }

            /// \brief Indica si el color es transparent
            /// \return True si es transparent
            ///
            inline bool isTransparent() const {
            	return getOpacity() == 0x00;
            }

            inline ColorBase &operator = (const ColorBase &color) {
            	_c = color._c;
            	return *this;
            }

            inline bool operator == (const ColorBase &color) const {
            	return _c == color._c;
            }

            inline bool operator != (const ColorBase &color) const {
            	return _c != color._c;
            }

            inline operator color_t() const {
            	return _c;
            }

            constexpr static ColorFormat getFormat() {
            	return FORMAT;
            }
	};


	/// \brief Color basic del sistema
	///
	typedef ColorBase<EOS_COLOR_FORMAT> Color;
	typedef ColorBase<ColorFormat::argb8888> ColorARGB8888;
	typedef ColorBase<ColorFormat::rgb888> ColorRGB888;
	typedef ColorBase<ColorFormat::rgb666> ColorRGB666;
	typedef ColorBase<ColorFormat::rgb565> ColorRGB565;


	/// \brief Conversio de formats de color
	///
	template <ColorFormat FORMAT>
	inline ColorBase<FORMAT> ConvertTo(Color color) {
		if constexpr (Color::CI::format == FORMAT)
			return color;
		else
			return ColorBase<FORMAT>(color.getA(), color.getR(), color.getG(), color.getB());
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
