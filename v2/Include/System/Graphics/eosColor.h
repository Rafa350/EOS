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

#define ARGB(a, r, g, b)          Color::fromARGB(a, r, g, b)
#define RGB(r, g, b)              Color::fromRGB(r, g, b)
#define AL(a, l)                  Color::fromAL(a, l)
#define PAL(l)                    Color::fromL(l);


namespace eos {

	/// \brief Format de color
	/// \remarks Hi han dos opcions de color RGB o Luminancia
	///
	enum class ColorFormat {
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

	/// \brief Tipus de color.
	///
	enum class ColorType {
		rgb,
		grayscale,
		palette
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
		static constexpr ColorType type = ColorType::rgb;
		static constexpr int bits = 32;
		static constexpr int bytes = (bits + 7) / 8;
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
		static constexpr ColorType type = ColorType::rgb;
		static constexpr int bits = 16;
		static constexpr int bytes = (bits + 7) / 8;
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
		static constexpr ColorType type = ColorType::rgb;
		static constexpr int bits = 24;
		static constexpr int bytes = (bits + 7) / 8;
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
		static constexpr ColorType type = ColorType::rgb;
		static constexpr int bits = 16;
		static constexpr int bytes = (bits + 7) / 8;
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
		static constexpr ColorType type = ColorType::grayscale;
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
		static constexpr ColorType type = ColorType::grayscale;
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
		static constexpr ColorType type = ColorType::palette;
		static constexpr int bits = 1;
		static constexpr int bytes = (bits + 7) / 8;
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
			static constexpr ColorType type = CT::type;
			static constexpr int bits = CT::bits;
			static constexpr int bytes = CT::bytes;
			static constexpr int colors = CT::colors;
			static constexpr bool hasAlpha = CT::hasAlpha;

		private:
			Pixel _pixel;

		public:
			/// \brief Construeix un color a partir dels components ARGB
			/// \param a: Component ALPHA.
			/// \param r: Component R.
			/// \param g: Component G.
			/// \param b: Component B.
			/// \return El color.
			///
			static constexpr Color_x fromARGB(
				uint8_t a,
				uint8_t r,
				uint8_t g,
				uint8_t b) {

				if constexpr (type == ColorType::rgb) {
					if constexpr (hasAlpha)
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
				else {
					uint32_t rr = (uint32_t)r * 612;   // 0.299 * 2048
					uint32_t gg = (uint32_t)g * 1202;  // 0.587 * 2048
					uint32_t bb = (uint32_t)b * 294;   // 0.144 * 2048
					uint32_t l = (rr + gg + bb) >> 11;  // Divideix per 2048
					if (l > 0x00FF)
						l = 255;
					if constexpr (hasAlpha)
						return Color_x<format_>(
							((Pixel)a >> CT::adjA << CT::shiftA) |
							((Pixel)l >> CT::adjL << CT::shiftL));
					else
						return Color_x<format_>(
							(Pixel)l >> CT::adjL << CT::shiftL);
				}
			}

			/// \brief Construeix un color a partir dels components RGB
			/// \param r: Component R.
			/// \param g: Component G.
			/// \param b: Component B.
			/// \return El color.
			///
			static constexpr Color_x<format_> fromRGB(
				uint8_t r,
				uint8_t g,
				uint8_t b) {

				return fromARGB(0xFF, r, g, b);
			}

			/// \brief Construeix un color a partir dels components AL
			/// \param a: Component ALPHA.
			/// \param l: Component L
			/// \return El color.
			///
			static constexpr Color_x<format_> fromAL(
				uint8_t a,
				uint8_t l) {

				if constexpr (type == ColorType::rgb) {
					uint32_t x = l / 3;
					if constexpr (hasAlpha)
						return Color_x<format_>(
							((Pixel)a >> CT::adjA << CT::shiftA) |
							((Pixel)x >> CT::adjR << CT::shiftR) |
							((Pixel)x >> CT::adjG << CT::shiftG) |
							((Pixel)x >> CT::adjB << CT::shiftB));
					else
						return Color_x<format_>(
							((Pixel)x >> CT::adjR << CT::shiftR) |
							((Pixel)x >> CT::adjG << CT::shiftG) |
							((Pixel)x >> CT::adjB << CT::shiftB));
				}

				else {
					if constexpr (hasAlpha)
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
			static constexpr Color_x<format_> fromL(
				uint8_t l) {

				return fromAL(0xFF, l);
			}

			/// \brief Converteix un color a un altre format.
			/// \param color: El color a convertir.
			/// \return El nou color.
			///
		    template <ColorFormat newFormat_>
		    constexpr Color_x<newFormat_> convert() {

		    	using NewCT = ColorTrait<newFormat_>;

		    	if constexpr (NewCT::type == ColorType::rgb) {
		    		if constexpr (NewCT::hasAlpha)
		    			return Color_x<newFormat_>::fromARGB(getA(), getR(), getG(), getB());
		    		else
		    			return Color_x<newFormat_>::fromRGB(getR(), getG(), getB());
		    	}
		    	else {
		    		if constexpr (NewCT::hasAlpha)
		    			return Color_x<newFormat_>::fromAL(getA(), getL());
		    		else
		    			return Color_x<newFormat_>::fromL(getL());
		    	}
		    }

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

            	if constexpr (hasAlpha)
            		return (_pixel & CT::maskA) >> CT::shiftA << CT::adjA;
            	else
            		return 0xFF;
            }

            /// \brief Obte el valor del canal L.
            /// \return El valor.
            ///
            inline uint8_t getL() const {

            	static_assert(type == ColorType::grayscale, "Invalid.");

           		return (_pixel & CT::maskL) >> CT::shiftL << CT::adjL;
            }

            /// \brief Obte el valor del canal R
            /// \return El valor.
            ///
            inline uint8_t getR() const {

            	static_assert(type == ColorType::rgb, "Invalid.");

      			return (_pixel & CT::maskR) >> CT::shiftR << CT::adjR;
            }

            /// \brief Obte el valor del canal G
            /// \return El valor.
            ///
            inline uint8_t getG() const {

            	static_assert(type == ColorType::rgb, "Invalid.");

           		return (_pixel & CT::maskG) >> CT::shiftG << CT::adjG;
            }

            /// \brief Obte el valor del canal B
            /// \return El valor.
            ///
            inline uint8_t getB() const {

            	static_assert(type == ColorType::rgb, "Invalid.");

           		return (_pixel & CT::maskB) >> CT::shiftB << CT::adjB;
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
	};

	using ColorARGB8888 = Color_x<ColorFormat::argb8888>;
	using ColorRGB888 = Color_x<ColorFormat::rgb888>;
	using ColorRGB565 = Color_x<ColorFormat::rgb565>;
	using ColorL8 = Color_x<ColorFormat::l8>;
	using ColorL1 = Color_x<ColorFormat::l1>;
	using Color = Color_x<EOS_COLOR_FORMAT>;

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
