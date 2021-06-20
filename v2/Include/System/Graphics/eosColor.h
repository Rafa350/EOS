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
		argb8888,  // ARGB 8 bit channel
		rgb888,    // RGB 8 bit channel
		rgb565,    // RGB 5 bits Red & Blue channels, 6 bit Green channel
		l8         // Luminancia 8 bits
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
		constexpr static const int bytes = bits / 8;
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
		constexpr static const int bytes = bits / 8;
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
	struct ColorInfo<ColorFormat::rgb565> {
		typedef uint16_t color_t;
		constexpr static ColorFormat format = ColorFormat::rgb565;
		constexpr static const int bits = 16;
		constexpr static const int bytes = bits / 8;
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
			typedef typename ColorInfo<FORMAT>::color_t color_t;
		private:
			color_t _c;
		public:
			inline ColorBase(): _c(0) {}
			inline ColorBase(const ColorBase& color): _c(color._c) {}
			inline ColorBase(color_t c): _c(c) {}

			inline ColorBase(uint8_t r, uint8_t g, uint8_t b): _c(CI::maskA | (((color_t)r >> CI::adjR << CI::shiftR) & CI::maskR) | (((color_t)g >> CI::adjG << CI::shiftG) & CI::maskG) | (((color_t)b >> CI::adjB << CI::shiftB) & CI::maskB)) {}
			inline ColorBase(uint8_t a, uint8_t r, uint8_t g, uint8_t b): _c((CI::hasAlpha ? ((color_t)a >> CI::adjA << CI::shiftA) : 0) | ((color_t)r >> CI::adjR << CI::shiftR) | ((color_t)g >> CI::adjG << CI::shiftG) | ((color_t)b >> CI::adjB << CI::shiftB)) {}

			inline uint8_t getA() const { return (_c & CI::maskA) >> CI::shiftA << CI::adjA; }
            inline uint8_t getR() const { return (_c & CI::maskR) >> CI::shiftR << CI::adjR; }
            inline uint8_t getG() const { return (_c & CI::maskG) >> CI::shiftG << CI::adjG; }
            inline uint8_t getB() const { return (_c & CI::maskB) >> CI::shiftB << CI::adjB; }

            inline uint8_t getOpacity() const { return CI::hasAlpha ? getA() : 0xFF; }
            inline bool isOpaque() const { return getOpacity() == 0xFF; }
            inline bool isTransparent() const { return getOpacity() == 0x00; }

            inline ColorBase &operator = (const ColorBase &color) { _c = color._c; return *this;}

            inline bool operator == (const ColorBase &color) { return _c == color._c; }
            inline bool operator != (const ColorBase &color) { return _c != color._c; }

            inline operator color_t() const { return _c; }

            constexpr static ColorFormat getFormat() { return FORMAT; }
	};


	/// \brief Crea un color amb el format especificat a partir dels seus components
	///
	template <ColorFormat FORMAT>
	struct ColorBuilder {
	};

	template <>
    struct ColorBuilder<ColorFormat::rgb565> {
		static ColorBase<ColorFormat::rgb565> Build(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
			return ColorBase<ColorFormat::rgb565>(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3));
		}
	};

	template <>
    struct ColorBuilder<ColorFormat::rgb888> {
		static ColorBase<ColorFormat::rgb888> Build(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
			return ColorBase<ColorFormat::rgb888>((r << 16) | (g << 8) | b);
		}
	};

	template <>
    struct ColorBuilder<ColorFormat::argb8888> {
		static ColorBase<ColorFormat::argb8888> Build(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
			typedef ColorBase<ColorFormat::argb8888>::color_t color_t;
			color_t c =
				(((color_t)a) << 24) |
				(((color_t)r) << 16) |
				(((color_t)g) << 8) |
				((color_t)b);
 			return ColorBase<ColorFormat::argb8888>(c);
		}
	};


	/// \brief Color basic del sistema
	///
	typedef ColorBase<EOS_COLOR_FORMAT> Color;


	/// \brief Conversio de formats de color
	///
	template <ColorFormat FORMAT>
	inline ColorBase<FORMAT> ConvertTo(Color src) {
		//return ColorBase<FORMAT>(src.getA(), src.getR(), src.getG(), src.getB());
		return ColorBuilder<FORMAT>::Build(src.getA(), src.getR(), src.getG(), src.getB());
	}


	/// \brief Clase que representa la paleta de colors.
    ///
    class ColorPalette {
        private:
            Color colorTable[256];

        public:
            ColorPalette();
            inline const Color& getColor(uint8_t index) const { return colorTable[index]; }
            inline const Color* getTable() const { return colorTable; }
            void setColor(uint8_t index, const Color &color);
    };
}


#endif // __eosColor__
