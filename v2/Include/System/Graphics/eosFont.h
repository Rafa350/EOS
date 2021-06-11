#ifndef __eosFont__
#define __eosFont__


// EOS includes
//
#include "eos.h"
#include "System/eosPointers.h"


#ifndef eosGraphics_MaxFonts
#define eosGraphics_MaxFonts 10
#endif


namespace eos {

    enum class FontStyle: uint8_t {
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
    		struct Impl;
    		typedef SharedPtr<Impl> PImpl;

    	private:
    		PImpl _pImpl;

        private:
            PImpl allocate();
            void updateCache(char ch) const;

        public:
            Font();
            Font(const uint8_t *fontResource);
            Font(const Font& font);
            ~Font();

            Font& operator = (const Font& font);

            void getFontInfo(FontInfo &fi) const;
            void getCharInfo(char ch, CharInfo &ci) const;
            int getFontHeight() const;
            int getCharAdvance(char ch) const;

            static const uint8_t * getFontResource(const String& name, int height, FontStyle style);
    };
}


#endif // __eosFont__

