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
		argb8888,  ///< RGB 8 bit channel + Alpha 8 bits
		rgb888,    ///< RGB 8 bit channel
		rgb666,    ///< RGB 6 bit channel
		rgb565,    ///< RGB 5 bits Red & Blue channels, 6 bit Green channel
		AL88,      ///< Luminancia/CLUD 8 bits + Alpha 8 bits
		l8         ///< Luminancia/CLUD 8 bits
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
	struct ColorInfo<ColorFormat::rgb666> {
		typedef uint32_t color_t;
		constexpr static ColorFormat format = ColorFormat::rgb666;
		constexpr static const int bits = 18;
		constexpr static const int bytes = (bits + 7) / 8;
		constexpr static const bool isColor = true;
		constexpr static const bool isIndex = false;
		constexpr static const bool hasAlpha = false;
		constexpr static const unsigned maskR = 0x0003F000;
		constexpr static const unsigned maskG = 0x00000FC0;
		constexpr static const unsigned maskB = 0x0000003F;
		constexpr static const unsigned shiftR = 13;
		constexpr static const unsigned shiftG = 6;
		constexpr static const unsigned shiftB = 0;
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


	/// \brief Clase que representa un color en formar ARGB8888
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

	/// \brief Clase que representa un color en formar RGB888
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

	/// \brief Clase que representa un color en formar RGB666
	///
	class ColorRGB666 {
		public:
			typedef ColorInfo<ColorFormat::rgb666> CI;
			typedef CI::color_t color_t;

		private:
			color_t _c;

		public:
			/// \brief Constructor per defecte
			///
			inline ColorRGB666() :
				_c(0) {
			}

			/// \brief Constructor per compopnents ARGB
			/// \param R: Component r
			/// \param G: Component g
			/// \param B: Component b
			///
			inline ColorRGB666(uint8_t r, uint8_t g, uint8_t b):
				_c(((color_t)r >> CI::adjR << CI::shiftR) |
				   ((color_t)g >> CI::adjG << CI::shiftG) |
				   ((color_t)b >> CI::adjB << CI::shiftB)) {
			}

			inline ColorRGB666(const ColorRGB666& color) {
				_c = color._c;
			}

			inline ColorRGB666 &operator = (const ColorRGB666 &color) {
            	_c = color._c;
            	return *this;
            }

            inline bool operator == (const ColorRGB666 color) const {
            	return _c == color._c;
            }

            inline bool operator != (const ColorRGB666 color) const {
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

	/// \brief Clase que representa un color en formar RGB565
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

			inline ColorRGB565 &operator = (const ColorRGB565 &color) {
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

	template <ColorFormat FORMAT>
	class ColorBase {
	};

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

			template <ColorFormat FORMAT>
			inline ColorBase<FORMAT> convertTo() {
				//if constexpr (ColorInfo<FORMAT>::isColor) {
					if constexpr (ColorInfo<FORMAT>::hasAlpha)
						return ColorBase<FORMAT>(getA(), getR(), getG(), getB());
					else
						return ColorBase<FORMAT>(getR(), getG(), getB());
				//}
			}
	};

	template <>
	class ColorBase<ColorFormat::rgb888> : public ColorRGB888 {

	};

	template <>
	class ColorBase<ColorFormat::rgb666> : public ColorRGB666 {

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

			inline ColorBase<ColorFormat::rgb565>(uint8_t a, uint8_t r, uint8_t g, uint8_t b):
				ColorRGB565(r, g, b) {
			}

			template <ColorFormat FORMAT>
			inline ColorBase<FORMAT> convertTo() {
				return ColorBase<FORMAT>(getR(), getG(), getB());
			}
	};

	/// \brief Color basic del sistema
	///
	typedef ColorBase<EOS_COLOR_FORMAT> Color;


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
