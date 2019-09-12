#ifndef __eosColor__
#define __eosColor__


// EOS includes
//
#include "eos.h"


// Format nadiu utilitzat internament en la clase Color
#define COLOR_MASK_A              0xFF000000u
#define COLOR_MASK_R              0x00FF0000u
#define COLOR_MASK_G              0x0000FF00u
#define COLOR_MASK_B              0x000000FFu

#define COLOR_SHIFT_A             24u
#define COLOR_SHIFT_R             16u
#define COLOR_SHIFT_G             8u
#define COLOR_SHIFT_B             0u

// Format ARGB8888
#define COLOR_ARGB8888_MASK_A     0xFF000000u
#define COLOR_ARGB8888_MASK_R     0x00FF0000u
#define COLOR_ARGB8888_MASK_G     0x0000FF00u
#define COLOR_ARGB8888_MASK_B     0x000000FFu

#define COLOR_ARGB8888_SHIFT_A    24u
#define COLOR_ARGB8888_SHIFT_R    16u
#define COLOR_ARGB8888_SHIFT_G    8u
#define COLOR_ARGB8888_SHIFT_B    0u

// Format RGB565
#define COLOR_RGB565_MASK_R       0x0000F800u
#define COLOR_RGB565_MASK_G       0x000003E0u
#define COLOR_RGB565_MASK_B       0x0000001Fu

#define COLOR_RGB565_SHIFT_R      11u
#define COLOR_RGB565_SHIFT_G      5u
#define COLOR_RGB565_SHIFT_B      0u


namespace eos {

	class Color;

	/// \brief Format de color
	enum class PixelFormat: uint8_t {
		argb8888,
		rgb888,
		rgb565
	};

	/// \brief Clase que representa un color (Color en format ARGB8888)
    class Color {
        private:
            uint32_t c;

        public :
            inline Color(): c(0) {}
            inline Color(const Color &color): c(color.c) {}
            inline Color(uint32_t c): c(c) {}
            inline Color(uint8_t r, uint8_t g, uint8_t b): c(0xFF000000 | (r << COLOR_SHIFT_R) | (g << COLOR_SHIFT_G) | (b << COLOR_SHIFT_B)) {}
            inline Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b): c((a << COLOR_SHIFT_A) | (r << COLOR_SHIFT_R) | (g << COLOR_SHIFT_G) | (b << COLOR_SHIFT_B)) {}

            inline uint8_t getA() const { return (c & COLOR_MASK_A) >> COLOR_SHIFT_A; }
            inline uint8_t getR() const { return (c & COLOR_MASK_R) >> COLOR_SHIFT_R; }
            inline uint8_t getG() const { return (c & COLOR_MASK_G) >> COLOR_SHIFT_G; }
            inline uint8_t getB() const { return (c & COLOR_MASK_B) >> COLOR_SHIFT_B; }

            static inline Color fromARGB8888(uint32_t c) { return Color(c); }
            static inline Color fromRGB888(uint32_t c) { return Color(c | 0xFF000000u); }
            static inline Color fromRGB565(uint16_t c) { return Color((c & 0xF800u) >> 11u, (c & 0x03E0u) >> 5u, c & 0x001Fu); }

            inline uint32_t toARGB8888() const { return c; }
            inline uint32_t toRGB888() const { return c | 0xFF000000u; }
            inline uint16_t toRGB565() const { return ((c & 0x00F80000u) >> 8u) | ((c & 0x0000FC00u) >> 5u) | ((c & 0x000000F8u) >> 3u); };

            inline uint8_t getOpacity() const { return c >> COLOR_SHIFT_A; }
            inline bool isOpaque() const { return getOpacity() == 0xFF; }
            inline bool isTransparent() const { return getOpacity() == 0x00; }

            inline Color &operator = (const Color &color) { c = color.c; return *this;}

            inline bool operator == (const Color &color) { return c == color.c; }
            inline bool operator != (const Color &color) { return c != color.c; }

            inline operator uint32_t() const { return c; }
    };

/*
    class ColorBuffer {
        private:
#if defined(DISPLAY_COLOR_ARGB) || defined(DISPLAY_COLOR_RGB)
            uint32_t *buffer;
#elif defined(DISPLAY_COLOR_565)
            uint16_t *buffer;
#endif

        public:
            ColorBuffer(int size);
            ~ColorBuffer();

#if defined(DISPLAY_COLOR_ARGB) || defined(DISPLAY_COLOR_RGB)
            void set(int offset, uint32_t nc);
            uint32_t get(int offset);
#elif defined(DISPLAY_COLOR_565)
            inline void set(int offset, uint16_t nc) { buffer[offset] = nc; }
            inline uint16_t get(int offset) { return buffer[offset]; }
#endif

            inline void setColor(int offset, Color color) { buffer[offset] = color; }
            inline Color getColor(int offset) const { return buffer[offset]; }
    };


    class ColorPalette {
        private:
            Color colorTable[256];

        public:
            ColorPalette();
            inline Color getColor(uint8_t index) { return colorTable[index]; }
            void setColor(uint8_t index, Color color);
    };
    */
}


#endif // __eosColor__
