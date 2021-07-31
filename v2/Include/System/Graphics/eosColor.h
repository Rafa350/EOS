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
	struct ColorInfo<ColorFormat::argb4444> {
		typedef uint32_t color_t;
		constexpr static ColorFormat format = ColorFormat::argb4444;
		constexpr static const int bits = 16;
		constexpr static const int bytes = (bits + 7) / 8;
		constexpr static const bool isColor = true;
		constexpr static const bool isIndex = false;
		constexpr static const bool hasAlpha = true;
		constexpr static const unsigned maskA = 0xF000;
		constexpr static const unsigned maskR = 0x0F00;
		constexpr static const unsigned maskG = 0x00F0;
		constexpr static const unsigned maskB = 0x000F;
		constexpr static const unsigned shiftA = 12;
		constexpr static const unsigned shiftR = 8;
		constexpr static const unsigned shiftG = 4;
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
		constexpr static const unsigned maskR = 0xFF0000;
		constexpr static const unsigned maskG = 0x00FF00;
		constexpr static const unsigned maskB = 0x0000FF;
		constexpr static const unsigned shiftR = 16;
		constexpr static const unsigned shiftG = 8;
		constexpr static const unsigned shiftB = 0;
		constexpr static const unsigned adjR = 0;
		constexpr static const unsigned adjG = 0;
		constexpr static const unsigned adjB = 0;
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
		constexpr static const unsigned maskR = 0xF800;
		constexpr static const unsigned maskG = 0x07E0;
		constexpr static const unsigned maskB = 0x001F;
		constexpr static const unsigned shiftR = 11;
		constexpr static const unsigned shiftG = 5;
		constexpr static const unsigned shiftB = 0;
		constexpr static const unsigned adjR = 3;
		constexpr static const unsigned adjG = 2;
		constexpr static const unsigned adjB = 3;
	};

	template <>
	struct ColorInfo<ColorFormat::al88> {
		typedef uint16_t color_t;
		constexpr static ColorFormat format = ColorFormat::al88;
		constexpr static const int bits = 16;
		constexpr static const int bytes = (bits + 7) / 8;
		constexpr static const bool isColor = false;
		constexpr static const bool isIndex = true;
		constexpr static const bool hasAlpha = true;
		constexpr static const unsigned maskA = 0xFF00;
		constexpr static const unsigned maskL = 0x00FF;
		constexpr static const unsigned shiftA = 8;
		constexpr static const unsigned shiftL = 0;
		constexpr static const unsigned adjA = 0;
		constexpr static const unsigned adjL = 0;
	};

	template <>
	struct ColorInfo<ColorFormat::al44> {
		typedef uint16_t color_t;
		constexpr static ColorFormat format = ColorFormat::al44;
		constexpr static const int bits = 8;
		constexpr static const int bytes = (bits + 7) / 8;
		constexpr static const bool isColor = false;
		constexpr static const bool isIndex = true;
		constexpr static const bool hasAlpha = true;
		constexpr static const unsigned maskA = 0xF0;
		constexpr static const unsigned maskL = 0x0F;
		constexpr static const unsigned shiftA = 4;
		constexpr static const unsigned shiftL = 0;
		constexpr static const unsigned adjA = 0;
		constexpr static const unsigned adjL = 0;
	};

	template <>
	struct ColorInfo<ColorFormat::l8> {
		typedef uint8_t color_t;
		constexpr static ColorFormat format = ColorFormat::l8;
		constexpr static const int bits = 8;
		constexpr static const int bytes = (bits + 7) / 8;
		constexpr static const bool isColor = false;
		constexpr static const bool isIndex = true;
		constexpr static const bool hasAlpha = false;
		constexpr static const unsigned maskL = 0;
		constexpr static const unsigned shiftL = 0;
		constexpr static const unsigned adjL = 0;
	};

	template <>
	struct ColorInfo<ColorFormat::l1> {
		typedef uint8_t color_t;
		constexpr static ColorFormat format = ColorFormat::l1;
		constexpr static const int bits = 1;
		constexpr static const int bytes = (bits + 7) / 8;
		constexpr static const bool isColor = false;
		constexpr static const bool isIndex = true;
		constexpr static const bool hasAlpha = false;
		constexpr static const unsigned maskL = 0;
		constexpr static const unsigned shiftL = 0;
		constexpr static const unsigned adjL = 0;
	};

	/// \brief Clase que representa un color en format ARGB8888
	///
	class ColorARGB8888 {
		public:
			typedef ColorInfo<ColorFormat::argb8888> CI;
			typedef CI::color_t color_t;

		private:
			color_t _c;

		public:
			/// \brief Constructor per defecte
			///
			inline ColorARGB8888() :
				_c(0) {
			}

			/// \brief Constructor per components RGB
			/// \param R: Component r
			/// \param G: Component g
			/// \param B: Component b
			///
			inline ColorARGB8888(uint8_t r, uint8_t g, uint8_t b):
				_c(((color_t)0xFF >> CI::adjA << CI::shiftA) |
				   ((color_t)r >> CI::adjR << CI::shiftR) |
				   ((color_t)g >> CI::adjG << CI::shiftG) |
				   ((color_t)b >> CI::adjB << CI::shiftB)) {
			}

			/// \brief Constructor per components ARGB
			/// \param R: Component a
			/// \param R: Component r
			/// \param G: Component g
			/// \param B: Component b
			///
			inline ColorARGB8888(uint8_t a, uint8_t r, uint8_t g, uint8_t b):
				_c(((color_t)a >> CI::adjA << CI::shiftA) |
				   ((color_t)r >> CI::adjR << CI::shiftR) |
				   ((color_t)g >> CI::adjG << CI::shiftG) |
				   ((color_t)b >> CI::adjB << CI::shiftB)) {
			}

			inline ColorARGB8888(const ColorARGB8888& color) {
				_c = color._c;
			}

			inline ColorARGB8888 &operator = (const ColorARGB8888 &color) {
            	_c = color._c;
            	return *this;
            }

            inline bool operator == (const ColorARGB8888 color) const {
            	return _c == color._c;
            }

            inline bool operator != (const ColorARGB8888 color) const {
            	return _c != color._c;
            }

            inline operator color_t() const {
            	return _c;
            }

			inline uint8_t getA() const  {
				return (_c & CI::maskA) >> CI::shiftA << CI::adjA;
			}

			inline uint8_t getR() const  {
				return (_c & CI::maskR) >> CI::shiftR << CI::adjR;
			}

			inline uint8_t getG() const  {
				return (_c & CI::maskG) >> CI::shiftG << CI::adjG;
			}

			inline uint8_t getB() const  {
				return (_c & CI::maskB) >> CI::shiftB << CI::adjB;
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
	};

	/// \brief Clase que representa un color en format RGB888
	///
	class ColorRGB888 {
		public:
			typedef ColorInfo<ColorFormat::rgb888> CI;
			typedef CI::color_t color_t;

		private:
			color_t _c;

		public:
			/// \brief Constructor per defecte
			///
			inline ColorRGB888() :
				_c(0) {
			}

			/// \brief Constructor per compopnents RGB
			/// \param R: Component r
			/// \param G: Component g
			/// \param B: Component b
			///
			inline ColorRGB888(uint8_t r, uint8_t g, uint8_t b):
				_c(((color_t)r >> CI::adjR << CI::shiftR) |
				   ((color_t)g >> CI::adjG << CI::shiftG) |
				   ((color_t)b >> CI::adjB << CI::shiftB)) {
			}

			inline ColorRGB888(const ColorRGB888& color) {
				_c = color._c;
			}

			inline ColorRGB888 &operator = (const ColorRGB888 &color) {
            	_c = color._c;
            	return *this;
            }

            inline bool operator == (const ColorRGB888 color) const {
            	return _c == color._c;
            }

            inline bool operator != (const ColorRGB888 color) const {
            	return _c != color._c;
            }

            inline operator color_t() const {
            	return _c;
            }

			inline uint8_t getA() const  {
				return 0xFF;
			}

			inline uint8_t getR() const  {
				return (_c & CI::maskR) >> CI::shiftR << CI::adjR;
			}

			inline uint8_t getG() const  {
				return (_c & CI::maskG) >> CI::shiftG << CI::adjG;
			}

			inline uint8_t getB() const  {
				return (_c & CI::maskB) >> CI::shiftB << CI::adjB;
			}

			inline uint8_t getOpacity() const {
				return 0xFF;
			}

			inline bool isTransparent() const {
				return false;
			}

			inline bool isOpaque() const {
				return true;
			}
	};

	/// \brief Clase que representa un color en format RGB565
	///
	class ColorRGB565 {
		public:
			typedef ColorInfo<ColorFormat::rgb565> CI;
			typedef CI::color_t color_t;

		private:
			color_t _c;

		public:
			/// \brief Constructor per defecte
			///
			inline ColorRGB565() :
				_c(0) {
			}

			/// \brief Constructor per compopnents RGB
			/// \param R: Component r
			/// \param G: Component g
			/// \param B: Component b
			///
			inline ColorRGB565(uint8_t r, uint8_t g, uint8_t b):
				_c(((color_t)r >> CI::adjR << CI::shiftR) |
				   ((color_t)g >> CI::adjG << CI::shiftG) |
				   ((color_t)b >> CI::adjB << CI::shiftB)) {
			}

			inline ColorRGB565(const ColorRGB565& color) {
				_c = color._c;
			}

			inline ColorRGB565 &operator = (const ColorRGB565& color) {
            	_c = color._c;
            	return *this;
            }

            inline bool operator == (const ColorRGB565 color) const {
            	return _c == color._c;
            }

            inline bool operator != (const ColorRGB565 color) const {
            	return _c != color._c;
            }

            inline operator color_t() const {
            	return _c;
            }

            inline uint8_t getA() const {
            	return 0xFF;
            }

			inline uint8_t getR() const  {
				return (_c & CI::maskR) >> CI::shiftR << CI::adjR;
			}

			inline uint8_t getG() const  {
				return (_c & CI::maskG) >> CI::shiftG << CI::adjG;
			}

			inline uint8_t getB() const  {
				return (_c & CI::maskB) >> CI::shiftB << CI::adjB;
			}

			inline uint8_t getOpacity() const {
				return 0xFF;
			}

			inline bool isTransparent() const {
				return false;
			}

			inline bool isOpaque() const {
				return true;
			}
	};

	/// \brief Clase que representa un color en format L8
	///
	class ColorL8 {
		public:
			typedef ColorInfo<ColorFormat::l8> CI;
			typedef CI::color_t color_t;

		private:
			color_t _c;

		public:
			/// \brief Constructor per defecte
			///
			inline ColorL8() :
				_c(0) {
			}

			/// \brief Constructor per compopnents L
			/// \param L: Component L
			///
			inline ColorL8(uint8_t l):
				_c((color_t)l >> CI::adjL << CI::shiftL) {
			}

			inline ColorL8(const ColorL8& color) {
				_c = color._c;
			}

			inline ColorL8 &operator = (const ColorL8& color) {
            	_c = color._c;
            	return *this;
            }

            inline bool operator == (const ColorL8 color) const {
            	return _c == color._c;
            }

            inline bool operator != (const ColorL8 color) const {
            	return _c != color._c;
            }

            inline operator color_t() const {
            	return _c;
            }

            inline uint8_t getA() const {
            	return 0xFF;
            }

			inline uint8_t getL() const  {
				return (_c & CI::maskL) >> CI::shiftL << CI::adjL;
			}

			inline uint8_t getOpacity() const {
				return 0xFF;
			}

			inline bool isTransparent() const {
				return false;
			}

			inline bool isOpaque() const {
				return true;
			}
	};

	/// \brief Clase que representa un color en format L1
	///
	class ColorL1 {
		public:
			typedef ColorInfo<ColorFormat::l1> CI;
			typedef CI::color_t color_t;

		private:
			color_t _c;

		public:
			/// \brief Constructor per defecte
			///
			inline ColorL1() :
				_c(0) {
			}

			/// \brief Constructor per compopnents L
			/// \param L: Component L
			///
			inline ColorL1(uint8_t l):
				_c((color_t)l >> CI::adjL << CI::shiftL) {
			}

			inline ColorL1(const ColorL1& color) {
				_c = color._c;
			}

			inline ColorL1 &operator = (const ColorL1& color) {
            	_c = color._c;
            	return *this;
            }

            inline bool operator == (const ColorL1 color) const {
            	return _c == color._c;
            }

            inline bool operator != (const ColorL1 color) const {
            	return _c != color._c;
            }

            inline operator color_t() const {
            	return _c;
            }

            inline uint8_t getA() const {
            	return 0xFF;
            }

			inline uint8_t getL() const  {
				return (_c & CI::maskL) >> CI::shiftL << CI::adjL;
			}

			inline uint8_t getOpacity() const {
				return 0xFF;
			}

			inline bool isTransparent() const {
				return false;
			}

			inline bool isOpaque() const {
				return true;
			}
	};


	/// \brief Clase generica que representa un color.
	///
	template <ColorFormat FORMAT>
	class ColorBase {
	};

	template <ColorFormat FORMAT>
	ColorBase<FORMAT> makeColor(uint8_t a, uint8_t r, uint8_t g, uint8_t b);

	template <ColorFormat FORMAT>
	ColorBase<FORMAT> makeColor(uint8_t r, uint8_t g, uint8_t b);

	template <>
	class ColorBase<ColorFormat::argb8888> : public ColorARGB8888 {
		public:
			inline ColorBase<ColorFormat::argb8888>():
				ColorARGB8888() {
			}

			inline ColorBase<ColorFormat::argb8888>(uint8_t r, uint8_t g, uint8_t b):
				ColorARGB8888(r, g, b) {
			}

			inline ColorBase<ColorFormat::argb8888>(uint8_t a, uint8_t r, uint8_t g, uint8_t b):
				ColorARGB8888(a, r, g, b) {
			}

			inline ColorBase<ColorFormat::argb8888>(const ColorBase<ColorFormat::argb8888>& color):
				ColorARGB8888(color) {
			}

			template <ColorFormat FORMAT>
			inline ColorBase<FORMAT> convertTo() {
				return makeColor<FORMAT>(getA(), getR(), getG(), getB());
			}
	};

	template <>
	class ColorBase<ColorFormat::rgb888> : public ColorRGB888 {
	public:
		inline ColorBase<ColorFormat::rgb888>():
			ColorRGB888() {
		}

		inline ColorBase<ColorFormat::rgb888>(uint8_t r, uint8_t g, uint8_t b):
			ColorRGB888(r, g, b) {
		}

		inline ColorBase<ColorFormat::rgb888>(const ColorBase<ColorFormat::rgb888>& color):
			ColorRGB888(color) {
		}

		template <ColorFormat FORMAT>
		inline ColorBase<FORMAT> convertTo() const {
			return makeColor<FORMAT>(getR(), getG(), getB());
		}
	};

	template <>
	class ColorBase<ColorFormat::rgb565> : public ColorRGB565 {
		public:
			inline ColorBase<ColorFormat::rgb565>():
				ColorRGB565() {
			}

			inline ColorBase<ColorFormat::rgb565>(uint8_t r, uint8_t g, uint8_t b):
				ColorRGB565(r, g, b) {
			}

			inline ColorBase<ColorFormat::rgb565>(const ColorBase<ColorFormat::rgb565>& color):
				ColorRGB565(color) {
			}

			template <ColorFormat FORMAT>
			inline ColorBase<FORMAT> convertTo() const {
				return makeColor<FORMAT>(getR(), getG(), getB());
			}
	};

	template <>
	class ColorBase<ColorFormat::l8> : public ColorL8 {
		public:
			inline ColorBase<ColorFormat::l8>():
				ColorL8() {
			}

			inline ColorBase<ColorFormat::l8>(uint8_t l):
				ColorL8(l) {
			}

			inline ColorBase<ColorFormat::l8>(const ColorBase<ColorFormat::l8>& color):
				ColorL8(color) {
			}

			template <ColorFormat FORMAT>
			inline ColorBase<FORMAT> convertTo() const {
				return makeColor<FORMAT>(getL());
			}
	};

	template <>
	class ColorBase<ColorFormat::l1> : public ColorL1 {
		public:
			inline ColorBase<ColorFormat::l1>():
				ColorL1() {
			}

			inline ColorBase<ColorFormat::l1>(uint8_t l):
				ColorL1(l) {
			}

			inline ColorBase<ColorFormat::l1>(const ColorBase<ColorFormat::l1>& color):
				ColorL1(color) {
			}

			template <ColorFormat FORMAT>
			inline ColorBase<FORMAT> convertTo() const {
				return makeColor<FORMAT>(getL());
			}
	};


	/// \brief Color base del sistema
	///
	typedef ColorBase<EOS_COLOR_FORMAT> Color;


	/// \brief Funcions de construccio de colors
	///
	template <ColorFormat FORMAT>
	inline ColorBase<FORMAT> makeColor(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
		typedef ColorInfo<FORMAT> CI;
		if constexpr (CI::hasAlpha) {
			if constexpr (CI::isColor)
				return ColorBase<FORMAT>(a, r, g, b);
			else
				return ColorBase<FORMAT>(a, ColorMath::grayWeight(r, g, b));
		}
		else {
			if constexpr (CI::isColor)
				return ColorBase<FORMAT>(r, g, b);
			else
				return ColorBase<FORMAT>(ColorMath::grayWeight(r, g, b));
		}
	}

	template <ColorFormat FORMAT>
	inline ColorBase<FORMAT> makeColor(uint8_t r, uint8_t g, uint8_t b) {
		return makeColor<FORMAT>(0xFF, r, g, b);
	}

	template <ColorFormat FORMAT>
	inline ColorBase<FORMAT> makeColor(uint8_t l) {
		typedef ColorInfo<FORMAT> CI;
		if constexpr (CI::isColor)
			return makeColor<FORMAT>(0xFF, l, l, l);
		else
			return ColorBase<FORMAT>(l);
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
