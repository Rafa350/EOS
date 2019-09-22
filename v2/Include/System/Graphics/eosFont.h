#ifndef __eosFont__
#define __eosFont__


// EOS includes
//
#include "eos.h"


namespace eos {

    enum class FontStyle {
        regular,
        bold,
        italic,
        boldItalic
    };

    struct FontTableEntry {       // Entrada de la taula de fonts
        const char *name;         // -Nom del font
        int16_t height;           // -Alçada
        FontStyle style;          // -Estil
        const uint8_t *resource;  // -Taula d'informacio del font
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

    class String;

    class Font {
        private:
            char chCache;
            CharInfo ciCache;
            const uint8_t *fontResource;

        private:
            Font(const Font& other) = delete;

            void updateCache(char ch);

        public:
            Font(const uint8_t *fontResource);

            void getFontInfo(FontInfo &fi) const;
            void getCharInfo(char ch, CharInfo &ci);
            inline int getFontHeight() const { return fontResource[1]; }
            int getCharAdvance(char ch);

            static const uint8_t * getFontResource(const String& name, int height, FontStyle style);
    };
}


#endif // __eosFont__

