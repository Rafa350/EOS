#pragma once


// EOS includes
//
#include "eos.h"


#ifndef eosGraphics_DefFontName
	#define eosGraphics_DefFontName "Tahoma"
	#define eosGraphics_DefFontHeight 12
	#define eosGraphics_DefFontStyle FontStyle::regular
	#define eosGraphics_DefFontResource fontTahoma12pt
#endif

#ifndef EOS_FONT_FORMAT
	#define EOS_FONT_FORMAT ColorFormat::al44
#endif


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

    class Font final {
    	private:
    		const uint8_t *_fontResource;

        public:
            Font();
            Font(const char *name, int height, FontStyle style);
            Font(const Font &font);

            Font& operator = (const Font &font);
            bool operator == (const Font &font) const;
            inline bool operator != (const Font &font) const { return !(*this == font); }

            void getFontInfo(FontInfo &fi) const;
            void getCharInfo(char ch, CharInfo &ci) const;
            int getFontHeight() const;
            int getFontAscent() const;
            int getFontDescent() const;
            int getCharAdvance(char ch) const;

            static const uint8_t* getFontResource(const char *name, int height, FontStyle style);
    };
}

