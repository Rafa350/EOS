#ifndef __eosFont__
#define __eosFont__


// EOS includes
//
#include "eos.h"


namespace eos {

    enum class FontStyle {
        Regular,
        Bold,
        Italic,
        BoldItalic
    };

    struct FontInfo {             // Informacio del font
        int16_t height;           // -Al�ada
        int16_t ascent;           // -Ascendent
        int16_t descent;          // -Descendent
        char firstChar;           // -Primer caracter definit en el font
        char lastChar;            // -Ultim caracter definit en el font
    };

    struct CharInfo {             // Informacio del caracter
        int16_t width;            // -Amplada del bitmap
        int16_t height;           // -Al�ada del bitmap
        int16_t left;             // -Offset horitzontal del bitmap
        int16_t top;              // -Offset vertical del bitmap
        int16_t advance;          // -Offset fins al origen del seguent bitmap
        const uint8_t *bitmap;    // -Punter al primer byte del caracter
    };

    class String;

    class Font {
        private:
            char chCache;
            CharInfo ciCache;
            const uint8_t *fontResource;

        public:
            Font(const String &fontName, int height, FontStyle style);
            Font(const unsigned char *fontResource);
            void getFontInfo(FontInfo &fi) const;
            void getCharInfo(char ch, CharInfo &ci);
            inline int getFontHeight() const { return fontResource[1]; }
            int getCharAdvance(char ch);

        private:
            void updateCache(char ch);
    };
}


#endif // __eosFont__

