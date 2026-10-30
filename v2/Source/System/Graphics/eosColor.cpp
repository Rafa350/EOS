export module Eos.System.Graphics.Color;

import Eos.Types;


export namespace eos {

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
		l4,        ///> L4                  (4 bits L)
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
	template <ColorFormat format_>
	struct ColorTraits {
	};

	template <>
	struct ColorTraits<ColorFormat::argb8888> {
		using Pixel = UInt32;
		static constexpr ColorFormat format = ColorFormat::argb8888;
		static constexpr ColorType type = ColorType::rgb;
		static constexpr UInt32 bits = 32;
		static constexpr UInt32 bytes = (bits + 7) / 8;
		static constexpr bool hasAlpha = true;
		static constexpr UInt32 maskA = 0xFF000000;
		static constexpr UInt32 maskR = 0x00FF0000;
		static constexpr UInt32 maskG = 0x0000FF00;
		static constexpr UInt32 maskB = 0x000000FF;
		static constexpr UInt32 maskL = 0x00000000;
		static constexpr UInt32 shiftA = 24;
		static constexpr UInt32 shiftR = 16;
		static constexpr UInt32 shiftG = 8;
		static constexpr UInt32 shiftB = 0;
		static constexpr UInt32 shiftL = 0;
		static constexpr UInt32 adjA = 0;
		static constexpr UInt32 adjR = 0;
		static constexpr UInt32 adjG = 0;
		static constexpr UInt32 adjB = 0;
		static constexpr UInt32 adjL = 0;
	};

	template <>
	struct ColorTraits<ColorFormat::argb4444> {
		using Pixel = UInt16;
		static constexpr ColorFormat format = ColorFormat::argb4444;
		static constexpr ColorType type = ColorType::rgb;
		static constexpr UInt32 bits = 16;
		static constexpr UInt32 bytes = (bits + 7) / 8;
		static constexpr bool hasAlpha = true;
		static constexpr UInt32 maskA = 0xF000;
		static constexpr UInt32 maskR = 0x0F00;
		static constexpr UInt32 maskG = 0x00F0;
		static constexpr UInt32 maskB = 0x000F;
		static constexpr UInt32 shiftA = 12;
		static constexpr UInt32 shiftR = 8;
		static constexpr UInt32 shiftG = 4;
		static constexpr UInt32 shiftB = 0;
		static constexpr UInt32 adjA = 0;
		static constexpr UInt32 adjR = 0;
		static constexpr UInt32 adjG = 0;
		static constexpr UInt32 adjB = 0;
	};

	template <>
	struct ColorTraits<ColorFormat::argb1555> {
		using Pixel = UInt16;
		static constexpr ColorFormat format = ColorFormat::argb1555;
		static constexpr UInt32 bits = 16;
		static constexpr UInt32 bytes = (bits + 7) / 8;
		static constexpr bool hasAlpha = true;
		static constexpr UInt32 maskA = 0x8000;
		static constexpr UInt32 maskR = 0x7C00;
		static constexpr UInt32 maskG = 0x03E0;
		static constexpr UInt32 maskB = 0x001F;
		static constexpr UInt32 shiftA = 15;
		static constexpr UInt32 shiftR = 10;
		static constexpr UInt32 shiftG = 5;
		static constexpr UInt32 shiftB = 0;
		static constexpr UInt32 adjA = 0;
		static constexpr UInt32 adjR = 0;
		static constexpr UInt32 adjG = 0;
		static constexpr UInt32 adjB = 0;
	};

	template <>
	struct ColorTraits<ColorFormat::rgb888> {
		using Pixel = UInt32;
		static constexpr ColorFormat format = ColorFormat::rgb888;
		static constexpr ColorType type = ColorType::rgb;
		static constexpr UInt32 bits = 24;
		static constexpr UInt32 bytes = (bits + 7) / 8;
		static constexpr bool hasAlpha = false;
		static constexpr UInt32 maskA = 0x000000;
		static constexpr UInt32 maskR = 0xFF0000;
		static constexpr UInt32 maskG = 0x00FF00;
		static constexpr UInt32 maskB = 0x0000FF;
		static constexpr UInt32 maskL = 0x000000;
		static constexpr UInt32 shiftA = 0;
		static constexpr UInt32 shiftR = 16;
		static constexpr UInt32 shiftG = 8;
		static constexpr UInt32 shiftB = 0;
		static constexpr UInt32 shiftL = 0;
		static constexpr UInt32 adjA = 0;
		static constexpr UInt32 adjR = 0;
		static constexpr UInt32 adjG = 0;
		static constexpr UInt32 adjB = 0;
		static constexpr UInt32 adjL = 0;
	};

	template <>
	struct ColorTraits<ColorFormat::rgb565> {
		using Pixel = UInt16;
		static constexpr ColorFormat format = ColorFormat::rgb565;
		static constexpr ColorType type = ColorType::rgb;
		static constexpr UInt32 bits = 16;
		static constexpr UInt32 bytes = (bits + 7) / 8;
		static constexpr bool hasAlpha = false;
		static constexpr UInt16 maskA = 0x0000;
		static constexpr UInt16 maskR = 0xF800;
		static constexpr UInt16 maskG = 0x07E0;
		static constexpr UInt16 maskB = 0x001F;
		static constexpr UInt16 maskL = 0x0000;
		static constexpr UInt32 shiftA = 0;
		static constexpr UInt32 shiftR = 11;
		static constexpr UInt32 shiftG = 5;
		static constexpr UInt32 shiftB = 0;
		static constexpr UInt32 shiftL = 0;
		static constexpr UInt32 adjA = 0;
		static constexpr UInt32 adjR = 3;
		static constexpr UInt32 adjG = 2;
		static constexpr UInt32 adjB = 3;
		static constexpr UInt32 adjL = 0;
	};

	template <>
	struct ColorTraits<ColorFormat::al88> {
		using Pixel = UInt16;
		static constexpr ColorFormat format = ColorFormat::al88;
		static constexpr ColorType type = ColorType::grayscale;
		static constexpr UInt32 bits = 16;
		static constexpr UInt32 bytes = (bits + 7) / 8;
		static constexpr bool hasAlpha = true;
		static constexpr UInt16 maskA = 0xFF00;
		static constexpr UInt16 maskR = 0x0000;
		static constexpr UInt16 maskG = 0x0000;
		static constexpr UInt16 maskB = 0x0000;
		static constexpr UInt16 maskL = 0x00FF;
		static constexpr UInt32 shiftA = 8;
		static constexpr UInt32 shiftR = 0;
		static constexpr UInt32 shiftG = 0;
		static constexpr UInt32 shiftB = 0;
		static constexpr UInt32 shiftL = 0;
		static constexpr UInt32 adjA = 0;
		static constexpr UInt32 adjR = 0;
		static constexpr UInt32 adjG = 0;
		static constexpr UInt32 adjB = 0;
		static constexpr UInt32 adjL = 0;
	};

	template <>
	struct ColorTraits<ColorFormat::al44> {
		using Pixel = UInt8;
		static constexpr ColorFormat format = ColorFormat::al44;
		static constexpr ColorType type = ColorType::grayscale;
		static constexpr UInt32 bits = 8;
		static constexpr UInt32 bytes = (bits + 7) / 8;
		static constexpr bool hasAlpha = true;
		static constexpr UInt8 maskA = 0xF0;
		static constexpr UInt8 maskL = 0x0F;
		static constexpr UInt32 shiftA = 4;
		static constexpr UInt32 shiftL = 0;
		static constexpr UInt32 adjA = 0;
		static constexpr UInt32 adjL = 0;
	};

	template <>
	struct ColorTraits<ColorFormat::l8> {
		using Pixel = UInt8;
		static constexpr ColorFormat format = ColorFormat::l8;
		static constexpr ColorType type = ColorType::grayscale;
		static constexpr UInt32 bits = 8;
		static constexpr UInt32 bytes = (bits + 7) / 8;
		static constexpr bool hasAlpha = false;
		static constexpr UInt8 maskL = 0xFF;
		static constexpr UInt32 shiftL = 0;
		static constexpr UInt32 adjL = 0;
	};

	template <>
	struct ColorTraits<ColorFormat::l4> {
		using Pixel = UInt8;
		static constexpr ColorFormat format = ColorFormat::l4;
		static constexpr ColorType type = ColorType::grayscale;
		static constexpr UInt32 bits = 4;
		static constexpr UInt32 bytes = (bits + 7) / 8;
		static constexpr bool hasAlpha = false;
		static constexpr UInt8 maskL = 0x0F;
		static constexpr UInt32 shiftL = 0;
		static constexpr UInt32 adjL = 0;
	};

	template <>
	struct ColorTraits<ColorFormat::l1> {
		using Pixel = UInt8;
		static constexpr ColorFormat format = ColorFormat::l1;
		static constexpr ColorType type = ColorType::grayscale;
		static constexpr UInt32 bits = 1;
		static constexpr UInt32 bytes = (bits + 7) / 8;
		static constexpr bool hasAlpha = false;
		static constexpr UInt8 maskL = 0x01;
		static constexpr UInt32 shiftL = 0;
		static constexpr UInt32 adjL = 0;
	};

	template <ColorFormat format_>
	class Color_x {
		private:
			using Traits = ColorTraits<format_>;

		public:
			using Pixel = typename Traits::Pixel;

			static constexpr ColorFormat format = format_;
			static constexpr ColorType type = Traits::type;
			static constexpr auto bits = Traits::bits;
			static constexpr auto bytes = Traits::bytes;
			static constexpr int colors = Traits::colors;
			static constexpr bool hasAlpha = Traits::hasAlpha;

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
				UInt8 a,
				UInt8 r,
				UInt8 g,
				UInt8 b) {

				if constexpr (type == ColorType::rgb) {
					if constexpr (hasAlpha)
						return Color_x<format_>(
							((Pixel)a >> Traits::adjA << Traits::shiftA) |
							((Pixel)r >> Traits::adjR << Traits::shiftR) |
							((Pixel)g >> Traits::adjG << Traits::shiftG) |
							((Pixel)b >> Traits::adjB << Traits::shiftB));
					else
						return Color_x<format_>(
							((Pixel)r >> Traits::adjR << Traits::shiftR) |
							((Pixel)g >> Traits::adjG << Traits::shiftG) |
							((Pixel)b >> Traits::adjB << Traits::shiftB));
				}
				else {
					UInt32 rr = (UInt32)r * 612;   // 0.299 * 2048
					UInt32 gg = (UInt32)g * 1202;  // 0.587 * 2048
					UInt32 bb = (UInt32)b * 294;   // 0.144 * 2048
					UInt32 l = (rr + gg + bb) >> 11;  // Divideix per 2048
					if (l > 0x00FF)
						l = 255;
					if constexpr (hasAlpha)
						return Color_x<format_>(
							((Pixel)a >> Traits::adjA << Traits::shiftA) |
							((Pixel)l >> Traits::adjL << Traits::shiftL));
					else
						return Color_x<format_>(
							(Pixel)l >> Traits::adjL << Traits::shiftL);
				}
			}

			/// \brief Construeix un color a partir dels components RGB
			/// \param r: Component R.
			/// \param g: Component G.
			/// \param b: Component B.
			/// \return El color.
			///
			static constexpr Color_x<format_> fromRGB(
				UInt8 r,
				UInt8 g,
				UInt8 b) {

				return fromARGB(0xFF, r, g, b);
			}

			/// \brief Construeix un color a partir dels components AL
			/// \param a: Component ALPHA.
			/// \param l: Component L
			/// \return El color.
			///
			static constexpr Color_x<format_> fromAL(
				UInt8 a,
				UInt8 l) {

				if constexpr (type == ColorType::rgb) {
					UInt32 x = l / 3;
					if constexpr (hasAlpha)
						return Color_x<format_>(
							((Pixel)a >> Traits::adjA << Traits::shiftA) |
							((Pixel)x >> Traits::adjR << Traits::shiftR) |
							((Pixel)x >> Traits::adjG << Traits::shiftG) |
							((Pixel)x >> Traits::adjB << Traits::shiftB));
					else
						return Color_x<format_>(
							((Pixel)x >> Traits::adjR << Traits::shiftR) |
							((Pixel)x >> Traits::adjG << Traits::shiftG) |
							((Pixel)x >> Traits::adjB << Traits::shiftB));
				}

				else {
					if constexpr (hasAlpha)
						return Color_x<format_>(
							((Pixel)a >> Traits::adjA << Traits::shiftA) |
							((Pixel)l >> Traits::adjL << Traits::shiftL));
					else
						return Color_x<format_>(
							(Pixel)l >> Traits::adjL << Traits::shiftL);
				}
			};

			/// \brief Construeix un color a partir dels components L
			/// \param l: Component L
			/// \return El color.
			///
			static constexpr Color_x<format_> fromL(
				UInt8 l) {

				return fromAL(0xFF, l);
			}

			/// \brief Converteix un color a un altre format.
			/// \param color: El color a convertir.
			/// \return El nou color.
			///
		    template <ColorFormat newFormat_>
		    constexpr Color_x<newFormat_> convert() {

		    	using NewCT = ColorTraits<newFormat_>;

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
            inline UInt8 getA() const {

            	if constexpr (hasAlpha)
            		return (_pixel & Traits::maskA) >> Traits::shiftA << Traits::adjA;
            	else
            		return 0xFF;
            }

            /// \brief Obte el valor del canal L.
            /// \return El valor.
            ///
            inline UInt8 getL() const {

            	static_assert(type == ColorType::grayscale, "Invalid.");

           		return (_pixel & Traits::maskL) >> Traits::shiftL << Traits::adjL;
            }

            /// \brief Obte el valor del canal R
            /// \return El valor.
            ///
            inline UInt8 getR() const {

            	static_assert(type == ColorType::rgb, "Invalid.");

      			return (_pixel & Traits::maskR) >> Traits::shiftR << Traits::adjR;
            }

            /// \brief Obte el valor del canal G
            /// \return El valor.
            ///
            inline UInt8 getG() const {

            	static_assert(type == ColorType::rgb, "Invalid.");

           		return (_pixel & Traits::maskG) >> Traits::shiftG << Traits::adjG;
            }

            /// \brief Obte el valor del canal B
            /// \return El valor.
            ///
            inline UInt8 getB() const {

            	static_assert(type == ColorType::rgb, "Invalid.");

           		return (_pixel & Traits::maskB) >> Traits::shiftB << Traits::adjB;
            }

            /// \brief Obte el valor de la opacitat.
            /// \return El valor.
            ///
            inline UInt8 getOpacity() const {

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
	using ColorL4 = Color_x<ColorFormat::l4>;
	using ColorL1 = Color_x<ColorFormat::l1>;

	#ifdef EOS_COLOR_FORMAT
	constexpr ColorFormat currentColorFormat = ColorFormat::EOS_COLOR_FORMAT;
	#else
	#error "Undefined color format"
	#endif

	using Color = Color_x<currentColorFormat>;

	/// \brief Clase que representa la paleta de colors.
    ///
    class ColorPalette {
        private:
            Color colorTable[256];

        public:
            ColorPalette();

            inline Color getColor(UInt8 index) const {
            	return colorTable[index];
            }

            inline const Color* getTable() const {
            	return colorTable;
            }

            void setColor(UInt8 index, Color color);
    };

}


/*
/// ----------------------------------------------------------------------
/// \brief Contructor.
/// \param size: Tamany del buffer.
///
ColorBuffer::ColorBuffer(
    int size) {

#if defined(DISPLAY_COLOR_ARGB) || defined(DISPLAY_COLOR_RGB)
    buffer = new UInt32[size];
#elif defined(DISPLAY_COLOR_565)
    buffer = new UInt16[size];
#endif
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
ColorBuffer::~ColorBuffer() {

    delete buffer;
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
ColorPalette::ColorPalette() {

    colorTable[COLOR_PAL_Black] = Color(COLOR_Black);
    colorTable[COLOR_PAL_White] = Color(COLOR_White);
    colorTable[COLOR_PAL_Blue] = Color(COLOR_Blue);
    colorTable[COLOR_PAL_Cyan] = Color(COLOR_Cyan);
    colorTable[COLOR_PAL_Magenta] = Color(COLOR_Magenta);
    colorTable[COLOR_PAL_Silver] = Color(COLOR_Silver);
    colorTable[COLOR_PAL_Gray] = Color(COLOR_Gray);
    colorTable[COLOR_PAL_Maroon] = Color(COLOR_Maroon);
    colorTable[COLOR_PAL_Purple] = Color(COLOR_Purple);
    colorTable[COLOR_PAL_Teal] = Color(COLOR_Teal);
    colorTable[COLOR_PAL_Navy] = Color(COLOR_Navy);
}


/// ----------------------------------------------------------------------
/// \brief Assigna un color a la paleta.
/// \param index: Index del color.
/// \param color: El color a asignar.
///
void ColorPalette::setColor(
    UInt8 index,
    Color color) {

    if ((index >= 20) & (index <= 255))
        colorTable[index] = color;
}
*/
