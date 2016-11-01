#ifndef __EOS_COLOR_HPP
#define __EOS_COLOR_HPP


#include <stdint.h>


#define ARGB(a, r, g, b)     ((((uint32_t)a) << 24) | (((uint32_t)r) << 16) | (((uint32_t)g) << 8) | ((uint32_t)b))
#define RGB(r, g, b)         ARGB(255, r, g, b)

// Basic colors
//
#define COLOR_Black          RGB(0, 0, 0)
#define COLOR_White          RGB(255, 255, 255)
#define COLOR_Blue           RGB(0, 0, 255)
#define COLOR_Cyan           RGB(0, 255, 255)
#define COLOR_Magenta        RGB(255, 0, 255)
#define COLOR_Silver         RGB(192, 192, 192)
#define COLOR_Gray           RGB(128, 128, 128)
#define COLOR_Maroon         RGB(128, 0, 0)
#define COLOR_Purple         RGB(128, 0, 128)
#define COLOR_Teal           RGB(0, 128, 128)
#define COLOR_Navy           RGB(0, 0, 128)

// HTML red colors
//
#define COLOR_LightSalmon    RGB(255, 160, 122)
#define COLOR_Salmon         RGB(250, 128, 114)
#define COLOR_DarkSalmon     RGB(233, 150, 122)
#define COLOR_LightCoral     RGB(240, 128, 128)
#define COLOR_IndianRed      RGB(205, 92, 92)
#define COLOR_Crimson        RGB(220, 20, 60)
#define COLOR_FireBrick      RGB(178, 34, 34)
#define COLOR_Red            RGB(255, 0, 0)
#define COLOR_DarkRed        RGB(139, 0, 0)

// HTML orange colors
//
#define COLOR_Coral          RGB(255, 127, 80)
#define COLOR_Tomato         RGB(255, 99, 71)
#define COLOR_OrangeRed      RGB(255, 69, 0)
#define COLOR_Gold           RGB(255, 215, 0)
#define COLOR_Orange         RGB(255, 165, 0)
#define COLOR_DarkOrange     RGB(255, 140, 0)

// HTML yellow colors
//
#define COLOR_LightYellow    RGB(255, 255, 224)
#define COLOR_LemonChiffon   RGB(255, 250, 205)
#define COLOR_LightGoldenrodYellow     RGB(250, 250, 210)
#define COLOR_PapayaWhip     RGB(255, 239, 213)
#define COLOR_Moccasin       RGB(225, 228, 181)
#define COLOR_PeachPuff      RGB(255, 218, 185)
#define COLOR_PaleGoldenrod  RGB(238, 232, 170)
#define COLOR_Khaki          RGB(240, 230, 140)
#define COLOR_DarkKhaki      RGB(189, 183, 107)
#define COLOR_Yellow         RGB(255, 255, 0)

// HTML green colors
//
#define COLOR_LawnGreen      RGB(124, 252, 0)
#define COLOR_Chartreuse     RGB(127, 255, 0)
#define COLOR_LimeGreen      RGB(50, 205, 50)
#define COLOR_Lime           RGB(0, 255, 0)
#define COLOR_ForestGreen    RGB(34, 139, 34)
#define COLOR_Green          RGB(0, 128, 0)
#define COLOR_DarkGreen      RGB(0, 100, 0)
#define COLOR_GreenYellow    RGB(173, 255, 47)
#define COLOR_YellowGreen    RGB(154, 205, 50)
#define COLOR_SpringGreen    RGB(0, 255, 127)
#define COLOR_MediumSpreingGreen       RGB(0, 250, 154)
#define COLOR_LightGreen     RGB(144, 238, 144)
#define COLOR_PaleGreen      RGB(152, 251, 152)
#define COLOR_DarkSeaGreen   RGB(143, 188, 143)
#define COLOR_MediumSeaGreen RGB(60, 179, 113)
#define COLOR_SeaGreen       RGB(46, 139, 87)
#define COLOR_Olive          RGB(128, 128, 0)
#define COLOR_DarkOliveGreen RGB(85, 107, 47)
#define COLOR_OliveDrab      RGB(107, 142, 35)

// HTML cyan colors
//

// HTML blue colors
//
#define COLOR_PowderBlue     RGB(176, 224, 230)
#define COLOR_LightBlue      RGB(173, 216, 230)
#define COLOR_LightSkyBlue   RGB(135, 206, 250)
#define COLOR_SkyBlue        RGB(135, 206, 235)
#define COLOR_DeepSkyBlue    RGB(0, 191, 255)
#define COLOR_LightSteelBlue RGB(176, 196, 222)
#define COLOR_DodgerBlue     RGB(30, 144, 255)
#define COLOR_CornflowerBlue RGB(100, 149, 237)
#define COLOR_SteelBlue      RGB(70, 130, 180)
#define COLOR_RoyalBlue      RGB(65, 105, 225)
#define COLOR_Blue           RGB(0, 0, 255)
#define COLOR_MediumBlue     RGB(0, 0, 205)
#define COLOR_DarkBlue       RGB(0, 0, 139)
#define COLOR_Navy           RGB(0, 0, 128)
#define COLOR_MidnightBlue   RGB(25, 25, 112)
#define COLOR_MediumSlateBlue          RGB(123, 104, 238)
#define COLOR_SlateBlue      RGB(106, 90, 205)
#define COLOR_DarkSlateBlue  RGB(72, 61, 139)


namespace eos {
      
    union Color {
        struct __attribute__((packed)) {
            uint8_t a;
            uint8_t r;
            uint8_t g;
            uint8_t b;
        };
        uint32_t c;
        
        inline Color(): c(0) {}
        inline Color(const Color &other): c(other.c) {}
        inline Color(uint32_t c): c(c) {}
        inline Color(uint8_t r, uint8_t g, uint8_t b): a(0), r(r), g(g), b(b) {}
        inline Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b): a(a), r(r), g(g), b(b) {}
        
        Color mix(Color c, uint8_t mix);
        
        uint32_t to565() const;
        uint32_t to666() const;
        
        static uint32_t to565(Color color) { return color.to565(); }
        static uint32_t to666(Color color) { return color.to666(); }
        static Color from565(uint32_t c);
        static Color from666(uint32_t c);
        
        inline operator int32_t() const { return c; }
    };
    
}


#endif