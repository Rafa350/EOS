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

#define ARGB(a, r, g, b)          makeColor<EOS_COLOR_FORMAT>(a, r, g, b)
#define RGB(r, g, b)              makeColor<EOS_COLOR_FORMAT>(r, g, b)
#define PAL(l)                    makeColor<EOS_COLOR_FORMAT>(l);


namespace eos {

	/// \brief Format de color
	///
	enum class ColorFormat: uint8_t {
		argb8888,  ///< A8 + R8 + G8 + B8   (32 bits ARGB)
		rgb888,    ///< R8 + G8 + B8        (24 bits RGB)
		argb4444,  ///< A4 + R4 + G4 + B4   (16 bits ARGB)
		rgb565,    ///< R5 + G6 + B5        (16 bits RGB)
		al88,      ///< A8 + L8             (16 bits AL/A+CLUD)
		al44,      ///< A4 + L4             (8 bits AL/A+CLUD)
		l8,        ///< L8                  (8 bits L/CLUD)
		l1         ///< L1                  (1 bit)
	};


	/// \brief Informacio sobre els formats de color
	///
	template <ColorFormat FORMAT>
	struct ColorTrait {
	};

	template <>
	struct ColorTrait<ColorFormat::argb8888> {
		using color_t = uint32_t;
		static constexpr ColorFormat format = ColorFormat::argb8888;
		static constexpr int bits = 32;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = true;
		static constexpr bool hasAlpha = true;
		static constexpr unsigned maskA = 0xFF000000;
		static constexpr unsigned maskR = 0x00FF0000;
		static constexpr unsigned maskG = 0x0000FF00;
		static constexpr unsigned maskB = 0x000000FF;
		static constexpr unsigned shiftA = 24;
		static constexpr unsigned shiftR = 16;
		static constexpr unsigned shiftG = 8;
		static constexpr unsigned shiftB = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjR = 0;
		static constexpr unsigned adjG = 0;
		static constexpr unsigned adjB = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::argb4444> {
		using color_t = uint32_t;
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
	struct ColorTrait<ColorFormat::rgb888> {
		using color_t = uint32_t;
		static constexpr ColorFormat format = ColorFormat::rgb888;
		static constexpr int bits = 24;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = true;
		static constexpr bool hasAlpha = false;
		static constexpr unsigned maskA = 0x000000;
		static constexpr unsigned maskR = 0xFF0000;
		static constexpr unsigned maskG = 0x00FF00;
		static constexpr unsigned maskB = 0x0000FF;
		static constexpr unsigned shiftA = 0;
		static constexpr unsigned shiftR = 16;
		static constexpr unsigned shiftG = 8;
		static constexpr unsigned shiftB = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjR = 0;
		static constexpr unsigned adjG = 0;
		static constexpr unsigned adjB = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::rgb565> {
		using color_t = uint16_t;
		static constexpr ColorFormat format = ColorFormat::rgb565;
		static constexpr int bits = 16;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = true;
		static constexpr bool hasAlpha = false;
		static constexpr unsigned maskA = 0x0000;
		static constexpr unsigned maskR = 0xF800;
		static constexpr unsigned maskG = 0x07E0;
		static constexpr unsigned maskB = 0x001F;
		static constexpr unsigned shiftA = 0;
		static constexpr unsigned shiftR = 11;
		static constexpr unsigned shiftG = 5;
		static constexpr unsigned shiftB = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjR = 3;
		static constexpr unsigned adjG = 2;
		static constexpr unsigned adjB = 3;
	};

	template <>
	struct ColorTrait<ColorFormat::al88> {
		using color_t = uint16_t;
		static constexpr ColorFormat format = ColorFormat::al88;
		static constexpr int bits = 16;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = false;
		static constexpr bool hasAlpha = true;
		static constexpr unsigned maskA = 0xFF00;
		static constexpr unsigned maskL = 0x00FF;
		static constexpr unsigned shiftA = 8;
		static constexpr unsigned shiftL = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjL = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::al44> {
		using color_t = uint16_t;
		static constexpr ColorFormat format = ColorFormat::al44;
		static constexpr int bits = 8;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = false;
		static constexpr bool hasAlpha = true;
		static constexpr unsigned maskA = 0xF0;
		static constexpr unsigned maskL = 0x0F;
		static constexpr unsigned shiftA = 4;
		static constexpr unsigned shiftL = 0;
		static constexpr unsigned adjA = 0;
		static constexpr unsigned adjL = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::l8> {
		using color_t = uint8_t;
		static constexpr ColorFormat format = ColorFormat::l8;
		static constexpr int bits = 8;
		static constexpr int bytes = (bits + 7) / 8;
		static constexpr bool isColor = false;
		static constexpr bool hasAlpha = false;
		static constexpr unsigned maskL = 0;
		static constexpr unsigned shiftL = 0;
		static constexpr unsigned adjL = 0;
	};

	template <>
	struct ColorTrait<ColorFormat::l1> {
		using color_t = uint8_t;
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
			using Trait = ColorTrait<format_>;
			using color_t = typename Trait::color_t;

			static constexpr unsigned _maskA = Trait::maskA;
			static constexpr unsigned _maskR = Trait::maskR;
			static constexpr unsigned _maskG = Trait::maskG;
			static constexpr unsigned _maskB = Trait::maskB;
			static constexpr unsigned _maskL = Trait::maskL;
			static constexpr unsigned _shiftA = Trait::shiftA;
			static constexpr unsigned _shiftR = Trait::shiftR;
			static constexpr unsigned _shiftG = Trait::shiftG;
			static constexpr unsigned _shiftB = Trait::shiftB;
			static constexpr unsigned _shiftL = Trait::shiftL;
			static constexpr unsigned _adjA = Trait::adjA;
			static constexpr unsigned _adjR = Trait::adjR;
			static constexpr unsigned _adjG = Trait::adjG;
			static constexpr unsigned _adjB = Trait::adjB;
			static constexpr unsigned _adjL = Trait::adjL;

		public:
			static constexpr ColorFormat format = format_;
			static constexpr int bits = Trait::bits;
			static constexpr int bytes = Trait::bytes;
			static constexpr bool hasAlpha = Trait::hasAlpha;
			static constexpr bool isColor = Trait::isColor;
			static constexpr bool isIndex = !Trait::isColor;

		private:
			color_t _c;

		private:
			/// \brief Constructor
			/// \param c: Color en format nadiu.
			///
			inline Color_x(
				color_t c) :

				_c(c) {
			}

		public:

			/// \brief Constructor copia.
			/// \param color: L'objecte a copiar
			///
			inline Color_x(
				const Color_x &color):

				_c(color._c) {
			}

			static Color_x fromARGB(
				uint8_t a,
				uint8_t r,
				uint8_t g,
				uint8_t b) {

				if constexpr (isColor) {
					if constexpr (hasAlpha)
						return Color_x(
							((color_t)a >> _adjA << _shiftA) |
							((color_t)r >> _adjR << _shiftR) |
							((color_t)g >> _adjG << _shiftG) |
							((color_t)b >> _adjB << _shiftB));
					else
						return Color_x(
							((color_t)r >> _adjR << _shiftR) |
							((color_t)g >> _adjG << _shiftG) |
							((color_t)b >> _adjB << _shiftB));
				}
				else {
					uint32_t l = (r + g + b) / 3;
					if constexpr (hasAlpha)
						return Color_x(
							((color_t)a >> _adjA << _shiftA) |
							((color_t)l >> _adjL << _shiftL));

					else
						return Color_x(
							(color_t)l >> _adjL << _shiftL);
				}
			}

			inline static Color_x fromRGB(
				uint8_t r,
				uint8_t g,
				uint8_t b) {

				return fromARGB(0xFF, r, g, b);
			}

			static Color_x fromAL(
				uint8_t a,
				uint8_t l) {

				if constexpr (isColor) {
					if constexpr (hasAlpha)
						return Color_x(
							((color_t)a >> _adjA << _shiftA) |
							((color_t)l >> _adjR << _shiftR) |
							((color_t)l >> _adjG << _shiftG) |
							((color_t)l >> _adjB << _shiftB));
					else
						return Color_x(
							((color_t)l >> _adjR << _shiftR) |
							((color_t)l >> _adjG << _shiftG) |
							((color_t)l >> _adjB << _shiftB));
				}
				else {
					if constexpr (hasAlpha)
						return Color_x(
							((color_t)a >> _adjA << _shiftA) |
							((color_t)l >> _adjL << _shiftL));
					else
						return Color_x(
							(color_t)l >> _adjL << _shiftL);
				}
			}

			inline static Color_x fromL(
				uint8_t l) {

				return fromAL(0xFF, l);
			}

			inline Color_x &operator = (
				const Color_x &color) {

            	_c = color._c;
            	return *this;
            }

            inline bool operator == (
            	const Color_x color) const {

            	return _c == color._c;
            }

            inline bool operator != (
            	const Color_x color) const {

            	return _c != color._c;
            }

            inline operator color_t() const {

            	return _c;
            }

            inline uint8_t getL() const {

            	if constexpr (isIndex)
        			return (_c & _maskL) >> _shiftL << _adjL;
            	else
            		return 0;
            }

            inline uint8_t getA() const {

            	if constexpr (hasAlpha)
            		return (_c & _maskA) >> _shiftA << _adjA;
            	else
            		return 0xFF;

            }

            inline uint8_t getR() const {

            	if constexpr (isColor)
            		return (_c & _maskR) >> _shiftR << _adjR;
            	else
            		return getL();
            }

            inline uint8_t getG() const {

            	if constexpr (isColor)
            		return (_c & _maskG) >> _shiftG << _adjG;
            	else
            		return getL();
            }

            inline uint8_t getB() const {

            	if constexpr (isColor)
            		return (_c & _maskB) >> _shiftB << _adjB;
            	else
            		return getL();
            }

            inline uint8_t getOpacity() const {

            	return getA();
            }

            inline bool isTransparent() const {

            	return getA() == 0;
            }

            inline bool isOpaque() const {

            	return getA() == 0xFF;
            }

            template <ColorFormat newFormat_>
            Color_x<newFormat_> convert() {

            	using NewTrait = ColorTrait<newFormat_>;
            	using NewColor = Color_x<newFormat_>;

            	if constexpr (NewTrait::isColor) {
            		if constexpr (NewTrait::hasAlpha)
            			return NewColor::fromARGB(getA(), getR(), getG(), getB());
            		else
            			return NewColor::fromRGB(getR(), getG(), getB());
            	}
            	else {
            		if constexpr (NewTrait::hasAlpha)
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
	using Color = Color_x<EOS_COLOR_FORMAT>;


	template <ColorFormat format_>
	Color_x<format_> makeColor(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {

		return Color_x<format_>::fromARGB(a, r, g, b);
	}

	template <ColorFormat format_>
	Color_x<format_> makeColor(uint8_t r, uint8_t g, uint8_t b) {

		return Color_x<format_>::fromRGB(r, g, b);
	}

	template <ColorFormat format_>
	Color_x<format_> makeColor(uint8_t l) {

		return Color_x<format_>::fromL(l);
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
