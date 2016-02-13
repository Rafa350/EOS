#ifndef __EOS_FONT_HPP
#define __EOS_FONT_HPP


#include "eos.hpp"


namespace eos {
    
    struct FontInfo {             // Informacio del font
        int height;               // -Alçada
        int ascent;               // -Ascendent
        int descent;              // -Descendent
        char firstChar;           // -Primer caracter definit en el font
        char lastChar;            // -Ultim caracter definit en el font
    };

    struct CharInfo {             // Informacio del caracter
        int width;                // -Amplada del bitmap
        int height;               // -Alçada del bitmap
        int left;                 // -Offset horitzontal del bitmap
        int top;                  // -Offset vertical del bitmap
        int advance;              // -Offset fins al origen del seguent bitmap
        const uint8_t *bitmap;    // -Punter al primer byte del caracter
    };

    class Font {
        private:
            const uint8_t *font;
            
        public:
            Font(const uint8_t *fontResource);
            void getFontInfo(FontInfo &fi) const;
            void getCharInfo(char ch, CharInfo &ci) const;
    };
}


#endif

