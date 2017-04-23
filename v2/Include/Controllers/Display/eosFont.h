#ifndef __EOS_FONT_HPP
#define __EOS_FONT_HPP


#include "eos.hpp"

#include <stdint.h>


namespace eos {
    
    enum class FontStyle {
        Regular,
        Bold,
        Italic,
        BoldItalic
    };
    
    struct FontInfo {             // Informacio del font
        int16_t height;           // -Alçada
        int16_t ascent;           // -Ascendent
        int16_t descent;          // -Descendent
        char firstChar;           // -Primer caracter definit en el font
        char lastChar;            // -Ultim caracter definit en el font
    };

    struct CharInfo {             // Informacio del caracter
        int16_t width;            // -Amplada del bitmap
        int16_t height;           // -Alçada del bitmap
        int16_t left;             // -Offset horitzontal del bitmap
        int16_t top;              // -Offset vertical del bitmap
        int16_t advance;          // -Offset fins al origen del seguent bitmap
        const uint8_t *bitmap;    // -Punter al primer byte del caracter
    };

    class Font {
        private:
            char chCache;
            CharInfo ciCache;
            const uint8_t *fontResource;
            
        public:
            Font(const char *fontName, int16_t height, FontStyle style);
            Font(const uint8_t *fontResource);
            void getFontInfo(FontInfo &fi) const;
            void getCharInfo(char ch, CharInfo &ci);
            inline int16_t getFontHeight() const { return fontResource[1]; }
            int16_t getCharAdvance(char ch);
            
        private:
            void updateCache(char ch);
    };
}


#endif

