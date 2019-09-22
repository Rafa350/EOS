#ifndef __eosColor__
#define __eosColor__


// EOS includes
//
#include "eos.h"


// Si no esta definit, el format de color del sistema es ARGB8888
#if !defined(EOS_COLOR_ARGB8888) & !defined(EOS_COLOR_RGB888) & !defined(EOS_COLOR_RGB565)
#define EOS_COLOR_ARGB8888
#endif


// Format ARGB8888
#define COLOR_ARGB8888_MASK_A     0xFF000000u
#define COLOR_ARGB8888_MASK_R     0x00FF0000u
#define COLOR_ARGB8888_MASK_G     0x0000FF00u
#define COLOR_ARGB8888_MASK_B     0x000000FFu
#define COLOR_ARGB8888_SHIFT_A    24u
#define COLOR_ARGB8888_SHIFT_R    16u
#define COLOR_ARGB8888_SHIFT_G    8u
#define COLOR_ARGB8888_SHIFT_B    0u
#define COLOR_ARGB8888_TYPE       uint32_t
#define COLOR_ARGB8888_BPP        32

// Format RGB888
#define COLOR_RGB888_MASK_R       0x00FF0000u
#define COLOR_RGB888_MASK_G       0x0000FF00u
#define COLOR_RGB888_MASK_B       0x000000FFu
#define COLOR_RGB888_SHIFT_R      16u
#define COLOR_RGB888_SHIFT_G      8u
#define COLOR_RGB888_SHIFT_B      0u
#define COLOR_RGB888_TYPE         uint32_t
#define COLOR_RGB888_BPP          24

// Format RGB565
#define COLOR_RGB565_MASK_R       0x0000F800u
#define COLOR_RGB565_MASK_G       0x000003E0u
#define COLOR_RGB565_MASK_B       0x0000001Fu
#define COLOR_RGB565_SHIFT_R      11u
#define COLOR_RGB565_SHIFT_G      5u
#define COLOR_RGB565_SHIFT_B      0u
#define COLOR_RGB565_TYPE         uint16_t
#define COLOR_RGB565_BPP          16

// Format nadiu utilitzat internament en la clase Color
#if defined(EOS_COLOR_ARGB8888)
#define COLOR_MASK_A              COLOR_ARGB8888_MASK_A
#define COLOR_MASK_R              COLOR_ARGB8888_MASK_R
#define COLOR_MASK_G              COLOR_ARGB8888_MASK_G
#define COLOR_MASK_B              COLOR_ARGB8888_MASK_B
#define COLOR_SHIFT_A             COLOR_ARGB8888_SHIFT_A
#define COLOR_SHIFT_R             COLOR_ARGB8888_SHIFT_R
#define COLOR_SHIFT_G             COLOR_ARGB8888_SHIFT_G
#define COLOR_SHIFT_B             COLOR_ARGB8888_SHIFT_B
#define COLOR_TYPE                COLOR_ARGB8888_TYPE
#define COLOR_BPP                 COLOR_ARGB8888_BPP
#endif


namespace eos {

	class Color;

	typedef COLOR_TYPE color_t;

	/// \brief Format de color
	enum class ColorFormat: uint8_t {
		argb8888,  // ARGB 8 bit channel
		rgb888,    // RGB 8 bit channel
		rgb565,    // RGB 5 bits Red & Blue channels, 6 bit Green channel
        l8         // Luminance 8 bit or CLUT[256] index
	};

	/// \brief Clase que representa un color.
    class Color {
        private:
            color_t c;

        public :
            inline Color(): c(0) {}
            inline Color(const Color &color): c(color.c) {}
            inline Color(color_t c): c(c) {}

            inline Color(uint8_t r, uint8_t g, uint8_t b): c(COLOR_MASK_A | (r << COLOR_SHIFT_R) | (g << COLOR_SHIFT_G) | (b << COLOR_SHIFT_B)) {}
            inline Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b): c((a << COLOR_SHIFT_A) | (r << COLOR_SHIFT_R) | (g << COLOR_SHIFT_G) | (b << COLOR_SHIFT_B)) {}

            inline uint8_t getA() const { return (c & COLOR_MASK_A) >> COLOR_SHIFT_A; }
            inline uint8_t getR() const { return (c & COLOR_MASK_R) >> COLOR_SHIFT_R; }
            inline uint8_t getG() const { return (c & COLOR_MASK_G) >> COLOR_SHIFT_G; }
            inline uint8_t getB() const { return (c & COLOR_MASK_B) >> COLOR_SHIFT_B; }

            static inline Color fromARGB8888(uint32_t c) { return Color(c); }
            static inline Color fromRGB888(uint32_t c) { return Color(c & ~COLOR_MASK_A); }
            static inline Color fromRGB565(uint16_t c) { return Color((c & 0xF800u) >> 11u, (c & 0x03E0u) >> 5u, c & 0x001Fu); }

            inline uint32_t toARGB8888() const { return c; }
            inline uint32_t toRGB888() const { return c | 0xFF000000u; }
            inline uint16_t toRGB565() const { return ((c & 0x00F80000u) >> 8u) | ((c & 0x0000FC00u) >> 5u) | ((c & 0x000000F8u) >> 3u); };

            inline uint8_t getOpacity() const { return (c & COLOR_MASK_A) >> COLOR_SHIFT_A; }
            inline bool isOpaque() const { return getOpacity() == 0xFF; }
            inline bool isTransparent() const { return getOpacity() == 0x00; }

            inline Color &operator = (const Color &color) { c = color.c; return *this;}

            inline bool operator == (const Color &color) { return c == color.c; }
            inline bool operator != (const Color &color) { return c != color.c; }

            inline operator color_t() const { return c; }
    };


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
